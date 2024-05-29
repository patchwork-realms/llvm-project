#ifndef LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H
#define LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "DMGGenRegisterInfo.inc"

namespace llvm {

struct DMGRegisterInfo : public DMGGenRegisterInfo {

  DMGRegisterInfo();
  
  const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;
  BitVector getReservedRegs(const MachineFunction &MF) const override;
  bool eliminateFrameIndex(MachineBasicBlock::iterator MI, int SPAdj,
                           unsigned FIOperandNum,
                           RegScavenger *RS = nullptr) const override;
  // TODO: Mark no frame register
  Register getFrameRegister(const MachineFunction &MF) const override;
};

}

#endif // LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H