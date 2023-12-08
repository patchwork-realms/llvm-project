#include "DMG.h"
#include "DMGTargetMachine.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/CodeGen/SelectionDAGISel.h"
#include "llvm/CodeGen/TargetLowering.h"
#include "llvm/IR/CallingConv.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Intrinsics.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/Compiler.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "DMG-isel"
#define PASS_NAME "DMG DAG->DAG Pattern Instruction Selection"

namespace {

class DMGDAGToDAGISel : public SelectionDAGISel {
public:
    static char ID;

    DMGDAGToDAGISel() = delete;

    DMGDAGToDAGISel(DMGTargetMachine &TM, CodeGenOptLevel OptLevel)
        : SelectionDAGISel(ID, TM, OptLevel) {}

    void Select(SDNode *N) override;

#include "DMGGenDAGISel.inc"
};

char DMGDAGToDAGISel::ID;

} // end anonymous namespace

INITIALIZE_PASS(DMGDAGToDAGISel, DEBUG_TYPE, PASS_NAME, false, false)

// Convert a legalised DAG into a DMG-specific DAG, ready for scheduling.
FunctionPass *llvm::createDMGISelDag(DMGTargetMachine &TM,
                                     CodeGenOptLevel OptLevel) {
    return new DMGDAGToDAGISel(TM, OptLevel);
}

void DMGDAGToDAGISel::Select(SDNode *N) {
    llvm_unreachable("Select not implemented");
    return;
}