#ifndef LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H
#define LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H

#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGINFO_HEADER
#include "DMGGenRegisterInfo.inc"

namespace llvm {

class TargetInstrInfo;
class DMGSubtarget;

struct DMGRegisterInfo : public DMGGenRegisterInfo {
    const DMGSubtarget &ST;

public:
    DMGRegisterInfo(const DMGSubtarget &);

    const MCPhysReg *getCalleeSavedRegs(const MachineFunction *MF) const override;

    BitVector getReservedRegs(const MachineFunction &MF) const override;

    bool requiresRegisterScavenging(const MachineFunction &MF) const override;

    bool useFPForScavengingIndex(const MachineFunction &MF) const override;

    bool eliminateFrameIndex(MachineBasicBlock::iterator II, int SPAdj,
                             unsigned FIOperandNum,
                             RegScavenger *RS = nullptr) const override;

    const uint32_t *getCallPreservedMask(const MachineFunction &MF,
                                         CallingConv::ID CC) const override;

    // Debug information queries
    Register getFrameRegister(const MachineFunction &MF) const override;

    //! Return whether to emit frame moves
    static bool needsFrameMoves(const MachineFunction &MF);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGREGISTERINFO_H