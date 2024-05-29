#include "DMGRegisterBankInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "dmg-reg-bank-info"

#define GET_TARGET_REGBANK_IMPL
#include "DMGGenRegisterBank.inc"

using namespace llvm;

DMGRegisterBankInfo::DMGRegisterBankInfo(const TargetRegisterInfo &TRI)
    : DMGGenRegisterBankInfo() {}