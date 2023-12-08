#ifndef LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H
#define LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H

#include "DMG.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {

class DMGSubtarget;
class DMGTargetMachine;

namespace DMGISD {

} // end namespace DMGISD

/// TargetLowering implementation

class DMGTargetLowering : public TargetLowering {
private:
    const DMGSubtarget &Subtarget;

public:
    explicit DMGTargetLowering(const TargetMachine &TM,
                               const DMGSubtarget &Subtarget);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H