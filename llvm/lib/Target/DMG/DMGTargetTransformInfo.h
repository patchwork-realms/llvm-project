#ifndef LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H
#define LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H

#include "DMG.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/CodeGen/BasicTTIImpl.h"

namespace llvm {

class DMGSubtarget;
class DMGTargetLowering;
class DMGTargetMachine;

class DMGTTIImpl : public BasicTTIImplBase<DMGTTIImpl> {
    using BaseT = BasicTTIImplBase<DMGTTIImpl>;
    friend BaseT;

    const DMGSubtarget *ST;
    const DMGTargetLowering *TLI;

    const DMGSubtarget *getST() const { return ST; }
    const DMGTargetLowering *getTLI() const { return TLI; }

public:
    explicit DMGTTIImpl(const DMGTargetMachine *TM, const Function &F)
        : BaseT(TM, F.getParent()->getDataLayout()), ST(TM->getSubtargetImpl()),
          TLI(ST->getTargetLowering()) {}

    // Provide value semantics, as MSVC requires that we spell these out. Whatever
    // that means.
    DMGTTIImpl(const DMGTTIImpl &Arg)
        : BaseT(static_cast<const BaseT &>(Arg)), ST(Arg.ST), TLI(Arg.TLI) {}
    DMGTTIImpl(DMGTTIImpl &&Arg)
        : BaseT(std::move(static_cast<BaseT &>(Arg))), ST(std::move(Arg.ST)),
          TLI(std::move(Arg.TLI)) {}
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGTARGETTRANSFORMINFO_H