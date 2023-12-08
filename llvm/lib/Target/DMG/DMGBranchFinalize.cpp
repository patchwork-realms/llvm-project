#include "DMGInstrInfo.h"
#include "DMGTargetMachine.h"
#include "MCTargetDesc/DMGInfo.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/InitializePasses.h"
#include "llvm/Support/Debug.h"
#include <vector>

#define DEBUG_TYPE "DMG-branch-finalize"

using namespace llvm;

namespace llvm {

void initializeDMGBranchFinalizePass(PassRegistry &Registry);
FunctionPass *createDMGBranchFinalizePass();

} // end namespace llvm

namespace {

class DMGBranchFinalize : public MachineFunctionPass {
public:
    static char ID;

    DMGBranchFinalize() : MachineFunctionPass(ID) {
        initializeDMGBranchFinalizePass(*PassRegistry::getPassRegistry());
    }

    StringRef getPassName() const override {
        return "DMG Branch Finalization Pass";
    }

    bool runOnMachineFunction(MachineFunction &MF) override;

private:
    const DMGInstrInfo *TII{nullptr};
};

char DMGBranchFinalize::ID = 0;

} // end anonymous namespace

INITIALIZE_PASS_BEGIN(DMGBranchFinalize, "dmg-branch-finalize",
                      "Game Boy finalize branches", false, false)
INITIALIZE_PASS_DEPENDENCY(MachineDominatorTree)
INITIALIZE_PASS_END(DMGBranchFinalize, "dmg-branch-finalize",
                      "Game Boy finalize branches", false, false)

bool DMGBranchFinalize::runOnMachineFunction(MachineFunction &MF) {
    llvm_unreachable("BranchFinalize pass not implemented");
    return false;
}

FunctionPass *llvm::createDMGBranchFinalizePass() {
    return new DMGBranchFinalize();
}