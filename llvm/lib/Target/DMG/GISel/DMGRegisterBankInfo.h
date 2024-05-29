#ifndef LLVM_LIB_TARGET_DMG_GISEL_DMGREGISTERBANKINFO_H
#define LLVM_LIB_TARGET_DMG_GISEL_DMGREGISTERBANKINFO_H

#include "MCTargetDesc/DMGMCTargetDesc.h"
#include "llvm/CodeGen/RegisterBankInfo.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"

#define GET_REGBANK_DECLARATIONS
#include "DMGGenRegisterBank.inc"

namespace llvm {
class TargetRegisterInfo;

class DMGGenRegisterBankInfo : public RegisterBankInfo {
protected:
#define GET_TARGET_REGBANK_CLASS
#include "DMGGenRegisterBank.inc"
};

class DMGRegisterBankInfo final : public DMGGenRegisterBankInfo {
public:
  DMGRegisterBankInfo(const TargetRegisterInfo &TRI);
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_GISEL_DMGREGISTERBANKINFO_H