#include "DMGSubtarget.h"
#include "DMG.h"
#include "DMGTargetMachine.h"
#include "GISel/DMGCallLowering.h"
#include "GISel/DMGLegalizerInfo.h"
#include "GISel/DMGRegisterBankInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Host.h"

using namespace llvm;

#define DEBUG_TYPE "dmg-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "DMGGenSubtargetInfo.inc"

void DMGSubtarget::anchor() {}

DMGSubtarget::DMGSubtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const TargetMachine &TM)
    : DMGGenSubtargetInfo(TT, CPU, CPU, FS), 
      FrameLowering(initializeSubtargetDependencies(CPU, FS)),
      TLInfo(TM, *this) {

  CallLoweringInfo.reset(new DMGCallLowering(*getTargetLowering())); 
  Legalizer.reset(new DMGLegalizerInfo(*this));
  auto *RBI = new DMGRegisterBankInfo(*getRegisterInfo());
  RegBankInfo.reset(RBI);

  InstSelector.reset(createDMGInstructionSelector(
    *static_cast<const DMGTargetMachine *>(&TM), *this, *RBI));
}

DMGSubtarget &DMGSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                            StringRef FS) {
  return *this;
}