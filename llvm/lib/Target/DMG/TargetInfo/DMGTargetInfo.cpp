#include "DMGTargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

Target &llvm::getTheDMGTarget() {
    static Target TheDMGTarget;
    return TheDMGTarget;
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGTargetInfo() {
    RegisterTarget<Triple::dmg> X(getTheDMGTarget(), "dmg", "DMG", "DMG");
}