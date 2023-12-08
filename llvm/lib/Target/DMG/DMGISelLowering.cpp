#include "DMGISelLowering.h"
#include "DMG.h"
#include "DMGMachineFunctionInfo.h"
#include "DMGSubtarget.h"
#include "DMGTargetMachine.h"
#include "MCTargetDesc/DMGInfo.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineJumpTableInfo.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/Support/Debug.h"
#include <algorithm>

#define DEBUG_TYPE "dmg-lower"

using namespace llvm;

static SDValue lowerCallResult(SDValue Chain, SDValue InGlue,
                               const SmallVectorImpl<CCValAssign> &RVLocs,
                               SDLoc dl, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals);

DMGTargetLowering::DMGTargetLowering(const TargetMachine &TM,
                                     const DMGSubtarget &Subtarget)
        : TargetLowering(TM), Subtarget(Subtarget) {

}