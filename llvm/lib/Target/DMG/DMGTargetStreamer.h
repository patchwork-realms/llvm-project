#ifndef LLVM_LIB_TARGET_DMG_DMGTARGETSTREAMER_H
#define LLVM_LIB_TARGET_DMG_DMGTARGETSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {

class DMGTargetStreamer : public MCTargetStreamer {
public:
    DMGTargetStreamer(MCStreamer &S);
    ~DMGTargetStreamer() override;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGTARGETSTREAMER_H