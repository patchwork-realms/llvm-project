#include "DMGLegalizerInfo.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "dmg-legalinfo"

using namespace llvm;
using namespace LegalizeActions;

DMGLegalizerInfo::DMGLegalizerInfo(const DMGSubtarget &ST) {
  getLegacyLegalizerInfo().computeTables();
}