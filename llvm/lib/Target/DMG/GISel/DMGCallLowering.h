#ifndef LLVM_LIB_TARGET_DMG_GISEL_DMGCALLOWERING_H
#define LLVM_LIB_TARGET_DMG_GISEL_DMGCALLOWERING_H

#include "DMGISelLowering.h"
#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/IR/CallingConv.h"

namespace llvm {

class DMGTargetLowering;

class DMGCallLowering : public CallLowering {
public:
  DMGCallLowering(const DMGTargetLowering &TLI);
  bool lowerReturn(MachineIRBuilder &MIRBuilder, const Value *Val,
                   ArrayRef<Register> VRegs, FunctionLoweringInfo &FLI,
                   Register SwiftErrorVReg) const override;
  bool lowerFormalArguments(MachineIRBuilder &MIRBuilder, const Function &F,
                            ArrayRef<ArrayRef<Register>> VRegs,
                            FunctionLoweringInfo &FLI) const override;
  bool lowerCall(MachineIRBuilder &MIRBuilder,
                 CallLoweringInfo &Info) const override;
};

}

#endif // LLVM_LIB_TARGET_DMG_GISEL_DMGCALLOWERING_H