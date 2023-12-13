#include "DMGTargetMachine.h"
#include "DMG.h"
#include "DMGMachineFunctionInfo.h"
#include "DMGTargetTransformInfo.h"
#include "TargetInfo/DMGTargetInfo.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/IRPrintingPasses.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/CodeGen.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <optional>

using namespace llvm;

static Reloc::Model getRelocModel(std::optional<Reloc::Model> RM) {
    return RM.value_or(Reloc::Static);
}

/// DMGTargetMachine ctor
DMGTargetMachine::DMGTargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM,
                                   CodeGenOptLevel OL, bool JIT)
        :   LLVMTargetMachine(T,
                              "e-p:16:8-i8:8-i16:16-i32:16-i64:16-f32:8-f64:8-n8-a:8",
                              TT, CPU, FS, Options, getRelocModel(RM),
                              getEffectiveCodeModel(CM, CodeModel::Small), OL),
            TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
            Subtarget(TT, std::string(CPU), std::string(FS), *this) {
    initAsmInfo();
}

DMGTargetMachine::~DMGTargetMachine() = default;

// TODO: Add required passes!
bool DMGTargetMachine::addPassesToEmitFile(PassManagerBase &PM, raw_pwrite_stream &Out,
                                           raw_pwrite_stream *DwoOut, CodeGenFileType FileType,
                                           bool DisableVerify,
                                           MachineModuleInfoWrapperPass *MMIWP) {

    TargetPassConfig *PassConfig = createPassConfig(PM);
    PassConfig->addCodeGenPrepare();

    switch (FileType) {
    case CodeGenFileType::AssemblyFile:
        PM.add(createPrintModulePass(Out, "", true));
        break;
    case CodeGenFileType::ObjectFile:
        if (!MMIWP)
            MMIWP = new MachineModuleInfoWrapperPass(this);
        PM.add(MMIWP);
        if (addAsmPrinter(PM, Out, DwoOut, FileType, MMIWP->getMMI().getContext()))
            return true;
        break;
    case CodeGenFileType::Null:
        break;
    }
    return false;
}

// TODO: Add required passes!
bool DMGTargetMachine::addPassesToEmitMC(PassManagerBase &PM, MCContext *&Ctx,
                                         raw_pwrite_stream &Out, bool DisableVerify) {
return true;
}

namespace {

/// DMG Code Generator Pass Configuration Options
class DMGPassConfig : public TargetPassConfig {
public:
    DMGPassConfig(DMGTargetMachine &TM, PassManagerBase &PM)
        : TargetPassConfig(TM, PM) {}

    DMGTargetMachine &getDMGTargetMachine() const {
        return getTM<DMGTargetMachine>();
    }

    bool addInstSelector() override;
    void addPreEmitPass() override;
    void addPreRegAlloc() override;
};

} // end anonymous namespace

TargetPassConfig *DMGTargetMachine::createPassConfig(PassManagerBase &PM) {
    return new DMGPassConfig(*this, PM);
}

bool DMGPassConfig::addInstSelector() {
    addPass(createDMGISelDag(getDMGTargetMachine(), getOptLevel()));
    return false;
}

void DMGPassConfig::addPreEmitPass() { addPass(createDMGBranchFinalizePass()); }

void DMGPassConfig::addPreRegAlloc() {
    addPass(createDMGExpandPseudosPass());
    // addPass(createDMGOptAddrMode());
}

MachineFunctionInfo *DMGTargetMachine::createMachineFunctionInfo(
    BumpPtrAllocator &Allocator, const Function &F,
    const TargetSubtargetInfo *STI) const {
    return DMGFunctionInfo::create<DMGFunctionInfo>(Allocator, F, STI);
}

// Static initialisation
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGTarget() {
    RegisterTargetMachine<DMGTargetMachine> X(getTheDMGTarget());
    PassRegistry &PR = *PassRegistry::getPassRegistry();
    initializeDMGDAGToDAGISelPass(PR);
}

TargetTransformInfo
DMGTargetMachine::getTargetTransformInfo(const Function &F) const {
    return TargetTransformInfo(DMGTTIImpl(this, F));
}