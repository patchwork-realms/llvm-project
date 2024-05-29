#include "DMGISelLowering.h"
#include "DMG.h"
#include "DMGSubtarget.h"
#include "DMGTargetMachine.h"
#include "llvm/CodeGen/CallingConvLower.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/CodeGen/ValueTypes.h"
#include "llvm/IR/DiagnosticInfo.h"
#include "llvm/IR/DiagnosticPrinter.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "dmg-lower"

// Calling convention
// #include "DMGGenCallingConv.inc"

DMGTargetLowering::DMGTargetLowering(const TargetMachine &TM,
                                     const DMGSubtarget &STI)
    : TargetLowering(TM) {

}
