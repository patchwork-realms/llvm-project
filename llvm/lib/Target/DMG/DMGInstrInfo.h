#ifndef LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H
#define LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H

#include "DMGRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "DMGGenInstrInfo.inc"

namespace llvm {
class DMGInstrInfo : public DMGGenInstrInfo {
  // const DMGRegisterInfo RI;
};
}

#endif // LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H