#ifndef LLVM_LIB_TARGET_DMG_DMGTARGETMACHINE_H
#define LLVM_LIB_TARGET_DMG_DMGTARGETMACHINE_H

#include "DMGSubtarget.h"
#include "llvm/Target/TargetMachine.h"
#include <optional>

namespace llvm {

class TargetPassConfig;

class DMGTargetMachine : public LLVMTargetMachine {
    std::unique_ptr<TargetLoweringObjectFile> TLOF;
    DMGSubtarget Subtarget;

public:
    DMGTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     std::optional<Reloc::Model> RM,
                     std::optional<CodeModel::Model> CM, CodeGenOptLevel OL,
                     bool JIT);
    ~DMGTargetMachine() override;

    const DMGSubtarget *getSubtargetImpl() const { return &Subtarget; }
    const DMGSubtarget *getSubtargetImpl(const Function &) const override {
        return &Subtarget; 
    }

    bool addPassesToEmitFile(PassManagerBase &PM, raw_pwrite_stream &Out,
                           raw_pwrite_stream *DwoOut, CodeGenFileType FileType,
                           bool DisableVerify,
                           MachineModuleInfoWrapperPass *MMIWP) override;

    bool addPassesToEmitMC(PassManagerBase &PM, MCContext *&Ctx,
                            raw_pwrite_stream &Out, bool DisableVerify) override;

    // Pass Pipeline Configuration
    TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

    TargetTransformInfo getTargetTransformInfo(const Function &F) const override;
    TargetLoweringObjectFile *getObjFileLowering() const override {
        return TLOF.get();
    }

    MachineFunctionInfo *
    createMachineFunctionInfo(BumpPtrAllocator &Allocator, const Function &F,
                              const TargetSubtargetInfo *STI) const override;

};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGTARGETMACHINE_H