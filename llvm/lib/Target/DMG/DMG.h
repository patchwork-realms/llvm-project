#ifndef LLVM_LIB_TARGET_DMG_DMG_H
#define LLVM_LIB_TARGET_DMG_DMG_H

#include "MCTargetDesc/DMGMCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class DMGTargetMachine;
class DMGSubtarget;
class FunctionPass;
class PassRegistry;

// TODO: Add the GlobalISel initializePass functions here.

FunctionPass *createDMGISelDag(DMGTargetMachine &TM, CodeGenOptLevel OptLevel);
FunctionPass *createDMGExpandPseudosPass();
FunctionPass *createDMGOptAddrMode();
FunctionPass *createDMGBranchFinalizePass();
void initializeDMGDAGToDAGISelPass(PassRegistry &);

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMG_H