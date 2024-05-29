#ifndef LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H

#include "DMGTargetMachine.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"
#include "llvm/Transforms/Utils/ScalarEvolutionExpander.h"

namespace llvm {
class DMGTTIImpl : public BasicTTIImplBase<DMGTTIImpl> {
  typedef BasicTTIImplBase<DMGTTIImpl> BaseT;
  typedef TargetTransformInfo TTI;
  friend BaseT;

  const DMGSubtarget *ST;
  const DMGTargetLowering *TLI;

  const DMGSubtarget *getST() const { return ST; }
  const DMGTargetLowering *getTLI() const { return TLI; }

public:
  explicit DMGTTIImpl(const DMGTargetMachine *TM, const Function &F)
      : BaseT(TM, F.getParent()->getDataLayout()), ST(TM->getSubtargetImpl(F)),
        TLI(ST->getTargetLowering()) {}

};
} // end namespace llvm
#endif // LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H