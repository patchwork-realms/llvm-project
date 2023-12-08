#include "DMGInstrInfo.h"
#include "DMG.h"
#include "DMGMachineFunctionInfo.h"
#include "DMGSubtarget.h"
#include "MCTargetDesc/DMGInfo.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineMemOperand.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/Debug.h"

using namespace llvm;

#define GET_INSTRINFO_CTOR_DTOR
#include "DMGGenInstrInfo.inc"

#define DEBUG_TYPE "dmg-inst-info"

// Pin the whole vtable to this file.
void DMGInstrInfo::anchor() {}

DMGInstrInfo::DMGInstrInfo(const DMGSubtarget &ST)
    : DMGGenInstrInfo(), RI(ST) {}
