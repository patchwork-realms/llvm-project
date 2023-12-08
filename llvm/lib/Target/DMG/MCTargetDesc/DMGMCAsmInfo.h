#ifndef LLVM_LIB_TARGET_DMG_DMGMCASMINFO_H
#define LLVM_LIB_TARGET_DMG_DMGMCASMINFO_H

#include "llvm/MC/MCAsmInfoELF.h"

namespace llvm {

class Triple;

class DMGMCAsmInfo : public MCAsmInfoELF {
    void anchor() override;

public:
    explicit DMGMCAsmInfo(const Triple &TT);
};

} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGMCASMINFO_H