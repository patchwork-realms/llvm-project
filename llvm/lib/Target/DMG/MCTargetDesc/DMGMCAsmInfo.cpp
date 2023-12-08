#include "DMGMCAsmInfo.h"
using namespace llvm;

void DMGMCAsmInfo::anchor() {}

DMGMCAsmInfo::DMGMCAsmInfo(const Triple &TT) {
    SupportsDebugInformation = true;
}
