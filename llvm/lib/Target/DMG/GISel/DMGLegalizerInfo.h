#ifndef LLVM_LIB_TARGET_DMG_GISEL_DMGMACHINELEGALIZER_H
#define LLVM_LIB_TARGET_DMG_GISEL_DMGMACHINELEGALIZER_H

#include "llvm/CodeGen/GlobalISel/LegalizerInfo.h"

namespace llvm {
class DMGSubtarget;

class DMGLegalizerInfo : public LegalizerInfo {
public:
  DMGLegalizerInfo(const DMGSubtarget &ST);
};
}

#endif // LLVM_LIB_TARGET_DMG_GISEL_DMGMACHINELEGALIZER_H