#ifndef LLVM_LIB_TARGET_DMG_DMG_H
#define LLVM_LIB_TARGET_DMG_DMG_H

#include "MCTargetDesc/DMGMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class DMGRegisterBankInfo;
class DMGSubtarget;
class DMGTargetMachine;
class InstructionSelector;
class FunctionPass;
class PassRegistry;

// TODO: Add the GlobalISel initializePass functions here.
InstructionSelector *createDMGInstructionSelector(const DMGTargetMachine &,
                                                  const DMGSubtarget &,
                                                  const DMGRegisterBankInfo &);

FunctionPass *createDMGISelDag(DMGTargetMachine &TM, CodeGenOptLevel OptLevel);
FunctionPass *createDMGExpandPseudosPass();
FunctionPass *createDMGOptAddrMode();
FunctionPass *createDMGBranchFinalizePass();
void initializeDMGDAGToDAGISelPass(PassRegistry &);

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMG_H