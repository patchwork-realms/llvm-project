#include "DMGRegisterInfo.h"
#include "DMG.h"
#include "DMGSubtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "DMGGenRegisterInfo.inc"
using namespace llvm;

DMGRegisterInfo::DMGRegisterInfo()
    : DMGGenRegisterInfo(DMG::RA) {}

const MCPhysReg *
llvm::DMGRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

BitVector
llvm::DMGRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  return BitVector(getNumRegs());
}

bool llvm::DMGRegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator MI,
                                                int SPAdj,
                                                unsigned FIOperandNum,
                                                RegScavenger *RS) const {
  // TODO: Implement!
  llvm_unreachable("DMGRegisterInfo::eliminateFrameIndex - unimplemented!");
  return false;
}

Register
llvm::DMGRegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  return DMG::SP;
}
