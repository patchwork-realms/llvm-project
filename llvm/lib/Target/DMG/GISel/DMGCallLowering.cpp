#include "DMGCallLowering.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "dmg-call-lowering"

using namespace llvm;

DMGCallLowering::DMGCallLowering(const DMGTargetLowering &TLI)
    : CallLowering(&TLI) {}

// TODO: Replace with actual RET instruction
bool DMGCallLowering::lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs, FunctionLoweringInfo &FLI,
                   Register SwiftErrorVReg) const {
  MIRBuilder.buildInstr(DMG::RET);
  return true;
}

bool DMGCallLowering::lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                            ArrayRef<ArrayRef<Register>> VRegs,
                            FunctionLoweringInfo &FLI) const {
  return VRegs.empty();
}

bool DMGCallLowering::lowerCall(MachineIRBuilder &MIRBuilder,
              CallLoweringInfo &Info) const {
  return false;
}