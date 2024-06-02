#ifndef LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H
#define LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H

#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {
class DMGSubtarget;

class DMGFrameLowering : public TargetFrameLowering {
public:
  explicit DMGFrameLowering(const DMGSubtarget &sti)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(8), 0) {}

  void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override {}
  bool hasFP(const MachineFunction &MF) const override { return false; }
};
}

#endif // LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H