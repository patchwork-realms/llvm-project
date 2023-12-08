#ifndef LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H
#define LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H

#include "DMG.h"
#include "llvm/CodeGen/MachineBasicBlock.h" 
#include "llvm/CodeGen/MachineFrameInfo.h" 
#include "llvm/CodeGen/TargetFrameLowering.h"

namespace llvm {

class MachineFunction;
class DMGSubtarget;
class DMGInstrInfo;

class DMGFrameLowering : public TargetFrameLowering {
public:
    DMGFrameLowering(const DMGSubtarget &st)
            : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, Align(2), 0),
              ST(st) {}

    void emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

    void emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const override;

    bool hasFP(const MachineFunction &MF) const override;
    
private:
    const DMGSubtarget &ST;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGFRAMELOWERING_H