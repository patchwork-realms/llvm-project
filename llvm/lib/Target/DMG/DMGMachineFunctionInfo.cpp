#include "DMGMachineFunctionInfo.h"

using namespace llvm;

void DMGFunctionInfo::anchor() {}

MachineFunctionInfo *
DMGFunctionInfo::clone(BumpPtrAllocator &Allocator, MachineFunction &DestMF,
                       const DenseMap<MachineBasicBlock *, MachineBasicBlock *>
                            &Src2DstMBB) const {
    return DestMF.cloneInfo<DMGFunctionInfo>(*this);
}