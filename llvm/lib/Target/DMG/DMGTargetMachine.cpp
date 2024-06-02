#include "DMGTargetMachine.h"
#include "DMG.h"
#include "TargetInfo/DMGTargetInfo.h"
#include "MCTargetDesc/DMGMCAsmInfo.h"

#include "llvm/CodeGen/GlobalISel/IRTranslator.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelect.h"
#include "llvm/CodeGen/GlobalISel/Legalizer.h"
#include "llvm/CodeGen/GlobalISel/RegBankSelect.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/PassManager.h"
#include "llvm/InitializePasses.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/SimplifyCFG.h"
#include "llvm/Transforms/Utils/SimplifyCFGOptions.h"

using namespace llvm;

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGTarget() {
  RegisterTargetMachine<DMGTargetMachine> X(getTheDMGTarget());

  PassRegistry &PR = *PassRegistry::getPassRegistry();
  initializeGlobalISel(PR);
}

static Reloc::Model getEffectiveRelocModel(std::optional<Reloc::Model> RM) {
  return RM.value_or(Reloc::Static);
}

static std::string computeDataLayout(const Triple &TT) {
  return "e-p:16:8-i8:8-i16:16-i32:16-i64:16-f32:8-f64:8-n8-a:8";
}

DMGTargetMachine::DMGTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                                   StringRef FS, const TargetOptions &Options,
                                   std::optional<Reloc::Model> RM,
                                   std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                                   bool JIT) 
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM),
                        getEffectiveCodeModel(CM, CodeModel::Small), OL),
      TLOF(std::make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, std::string(CPU), std::string(FS), *this) {
  
  // initAsmInfo();

  // Might need to use this later to set MAI behaviour?
  // DMGMCAsmInfo *MAI =
  //     static_cast<DMGMCAsmInfo *>(const_cast<MCAsmInfo *>(AsmInfo.get()));
}

namespace {
class DMGPassConfig : public TargetPassConfig {
public:
  DMGPassConfig(DMGTargetMachine &TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  DMGTargetMachine &getDMGTargetMachine() const {
    return getTM<DMGTargetMachine>();
  }

  bool addIRTranslator() override;
  bool addLegalizeMachineIR() override;
  bool addRegBankSelect() override;
  bool addGlobalInstructionSelect() override;
};
}

TargetPassConfig *DMGTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new DMGPassConfig(*this, PM);
}

void DMGTargetMachine::registerPassBuilderCallbacks(
  PassBuilder &PB, bool PopulateClassToPassNames) {
// #define GET_PASS_REGISTRY "DMGPassRegistry.def"
#include "llvm/Passes/TargetPassRegistry.inc"

  // TODO: Check which passbuilder callbacks to register here
}

bool DMGPassConfig::addIRTranslator() {
  addPass(new IRTranslator());
  return false;
}

bool DMGPassConfig::addLegalizeMachineIR() {
  addPass(new Legalizer());
  return false;
}

bool DMGPassConfig::addRegBankSelect() {
  addPass(new RegBankSelect());
  return false;
}

bool DMGPassConfig::addGlobalInstructionSelect() {
  addPass(new InstructionSelect(getOptLevel()));
  return false;
}