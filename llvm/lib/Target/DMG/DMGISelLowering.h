#ifndef LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H
#define LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H

#include "DMG.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/TargetLowering.h"

namespace llvm {


class DMGTargetLowering : public TargetLowering {
public:
  explicit DMGTargetLowering(const TargetMachine &TM, const DMGSubtarget &STI);
  
  // TODO: Only added so that there is a method implemented here
  DMGTargetLowering::ConstraintType
  getConstraintType(StringRef Constraint) const override {
    return TargetLowering::getConstraintType(Constraint);
  }
};

} // end namespace llvm
#endif // LLVM_LIB_TARGET_DMG_DMGISELLOWERING_H