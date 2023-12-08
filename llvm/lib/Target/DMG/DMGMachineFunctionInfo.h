#ifndef LLVM_LIB_TARGET_DMG_DMGMACHINEFUNCTIONINFO_H
#define LLVM_LIB_TARGET_DMG_DMGMACHINEFUNCTIONINFO_H

#include "llvm/CodeGen/MachineFunction.h"
#include <vector>

namespace llvm {

class DMGFunctionInfo : public MachineFunctionInfo {
    virtual void anchor();
    bool ReturnStackOffsetSet;
    int VarArgsFrameIndex;
    unsigned ReturnStackOffset;

public:
    explicit DMGFunctionInfo(const Function &F, const TargetSubtargetInfo *STI)
        : ReturnStackOffsetSet(false), VarArgsFrameIndex(0),
          ReturnStackOffset(-1U), MaxCallStackReq(0) {}
    ~DMGFunctionInfo() {}

    MachineFunctionInfo *
    clone(BumpPtrAllocator &Allocator, MachineFunction &DestMF,
          const DenseMap<MachineBasicBlock *, MachineBasicBlock *> &Src2DstMBB)
        const override;

    void setVarArgsFrameIndex(int off) { VarArgsFrameIndex = off; }
    int getVarArgsFrameIndex() const { return VarArgsFrameIndex; }

    void setReturnStackOffset(unsigned value) {
        assert(!ReturnStackOffsetSet && "Return stack offset set twice");
        ReturnStackOffset = value;
        ReturnStackOffsetSet = true;
    }

    unsigned getReturnStackOffset() const {
        assert(ReturnStackOffsetSet && "Return stack offset not set");
        return ReturnStackOffset;
    }

    unsigned MaxCallStackReq;
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGMACHINEFUNCTIONINFO_H