#include "DMGRegisterInfo.h"
#include "DMG.h"
#include "DMGInstrInfo.h"
#include "DMGMachineFunctionInfo.h"
#include "DMGSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;

#define DEBUG_TYPE "dmg-reg-info"

#define GET_REGINFO_TARGET_DESC
#include "DMGGenRegisterInfo.inc"

DMGRegisterInfo::DMGRegisterInfo(const DMGSubtarget &ST)
    : DMGGenRegisterInfo(0), ST(ST) {}

bool DMGRegisterInfo::needsFrameMoves(const MachineFunction &MF) {
    return MF.needsFrameMoves();
}

const MCPhysReg *
DMGRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
    return CSR_DMG_SaveList;
}

BitVector DMGRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
    BitVector Reserved(getNumRegs());
    return Reserved;
}

bool DMGRegisterInfo::requiresRegisterScavenging(
        const MachineFunction &MF) const {
    return true;
}

bool DMGRegisterInfo::useFPForScavengingIndex(const MachineFunction &MF) const {
    return true;
}

bool DMGRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                          int SPAdj, unsigned FIOperandNum,
                                          RegScavenger *RS) const {
    return true;
}

Register DMGRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
    return DMG::RA;
}

const uint32_t *
DMGRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                      CallingConv::ID CC) const {
    return CSR_DMG_RegMask;
}