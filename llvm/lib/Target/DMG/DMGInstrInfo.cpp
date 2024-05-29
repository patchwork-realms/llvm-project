#include "DMGInstrInfo.h"
#include "DMG.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/CodeGen/MachineBasicBlock.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/DebugLoc.h"
#include "llvm/Support/ErrorHandling.h"
#include <cassert>
#include <iterator>

#define GET_INSTRINFO_CTOR_DTOR
#include "DMGGenInstrInfo.inc"

using namespace llvm;

DMGInstrInfo::DMGInstrInfo()
    : DMGGenInstrInfo() {}

void llvm::DMGInstrInfo::copyPhysReg(MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator I,
                                     const DebugLoc &DL, MCRegister DestReg,
                                     MCRegister SrcReg, bool KillSrc) const {
  llvm_unreachable("copyPhysReg: not completed!");
}
