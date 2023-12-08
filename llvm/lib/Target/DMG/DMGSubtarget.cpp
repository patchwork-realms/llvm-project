#include "DMGSubtarget.h"
#include "DMG.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE = "dmg-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "DMGGenSubtargetInfo.inc"

void DMGSubtarget::anchor() {}

DMGSubtarget::DMGSubtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
        : DMGGenSubtargetInfo(TT, CPU, /*TuneCPU=*/ CPU, FS), InstrInfo(*this),
          FrameLowering(*this), TLInfo(TM, *this) {}