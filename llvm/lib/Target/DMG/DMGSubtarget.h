#ifndef LLVM_LIB_TARGET_DMG_DMGSUBTARGET_H
#define LLVM_LIB_TARGET_DMG_DMGSUBTARGET_H

#include "DMGInstrInfo.h"
#include "DMGFrameLowering.h"

#include "llvm/CodeGen/GlobalISel/CallLowering.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/CodeGen/TargetSubtargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"

#define GET_SUBTARGETINFO_HEADER
#include "DMGGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class DMGSubtarget : public DMGGenSubtargetInfo {
  virtual void anchor();
  DMGInstrInfo InstrInfo;
  DMGFrameLowering FrameLowering;

protected:
  std::unique_ptr<CallLowering> CallLoweringInfo;
  std::unique_ptr<InstructionSelector> InstSelector;
  std::unique_ptr<LegalizerInfo> Legalizer;
  std::unique_ptr<RegisterBankInfo> RegBankInfo;

public:
  DMGSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const TargetMachine &TM);

  DMGSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

  void ParseSubtargetFeatures(StringRef CPU, StringRef TuneCPU, StringRef FS);
  bool isLittleEndian() const { return true; }

  const CallLowering *getCallLowering() const override {
    return CallLoweringInfo.get();
  }

  InstructionSelector *getInstructionSelector() const override {
    return InstSelector.get();
  }

  const LegalizerInfo *getLegalizerInfo() const override {
    return Legalizer.get();
  }

  const RegisterBankInfo *getRegBankInfo() const override {
    return RegBankInfo.get();
  }

};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGSUBTARGET_H