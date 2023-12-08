#ifndef LLVM_LIB_TARGET_DMG_DMGMCTARGETDESC_H
#define LLVM_LIB_TARGET_DMG_DMGMCTARGETDESC_H

#include "llvm/Support/DataTypes.h"

namespace llvm {

class Target;

} // end namespace llvm

// Define symbolic names for DMG registers. This is a mapping from
// register names to register numbers.
#define GET_REGINFO_ENUM
#include "DMGGenRegisterInfo.inc"

// Define symbolic names for the DMG Instructions
#define GET_INSTRINFO_ENUM
#define GET_INSTRINFO_MC_HELPER_DECLS
#include "DMGGenInstrInfo.inc"

#define GET_SUBTARGETINFO_ENUM
#include "DMGGenSubtargetInfo.inc"

#endif // LLVM_LIB_TARGET_DMG_DMGMCTARGETDESC_H