#ifndef LLVM_LIB_TARGET_DMG_MCTARGETDESC_DMGASMINFO_H
#define LLVM_LIB_TARGET_DMG_MCTARGETDESC_DMGASMINFO_H

#include "llvm/MC/MCAsmInfo.h"
#include "llvm/TargetParser/Triple.h"

namespace llvm {

class DMGMCAsmInfo : public MCAsmInfo {
public:
  explicit DMGMCAsmInfo(const Triple &TT, const MCTargetOptions &Options) {
    if (TT.getArch() == Triple::dmg)
      IsLittleEndian = true;
    
    // TODO: Add more AsmInfo here
  }
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_MCTARGETDESC_DMGASMINFO_H