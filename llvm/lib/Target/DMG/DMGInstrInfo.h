#ifndef LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H
#define LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H

#include "DMGRegisterInfo.h"
#include "llvm/CodeGen/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "DMGGenInstrInfo.inc"

namespace llvm {

class DMGSubtarget;

class DMGInstrInfo : public DMGGenInstrInfo {
    const DMGRegisterInfo RI;
    virtual void anchor();

public:
    DMGInstrInfo(const DMGSubtarget &);

    const DMGRegisterInfo &getRegisterInfo() const { return RI; }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGINSTRINFO_H