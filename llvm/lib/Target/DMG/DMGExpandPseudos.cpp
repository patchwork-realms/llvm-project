#include "DMG.h"
#include "DMGInstrInfo.h"
#include "DMGRegisterInfo.h"
#include "DMGSubtarget.h"
#include "MCTargetDesc/DMGInfo.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

#define DEBUG_TYPE "DMG-expand-pseudos"

namespace {
class DMGExpandPseudos : public MachineFunctionPass {
public:
  static char ID;
  DMGExpandPseudos() : MachineFunctionPass(ID) {}

  bool runOnMachineFunction(MachineFunction &Fn) override;

  StringRef getPassName() const override { return "DMG Expand Pseudos"; }

private:
  const DMGInstrInfo *TII;
};

char DMGExpandPseudos::ID = 0;
} // end anonymous namespace

bool DMGExpandPseudos::runOnMachineFunction(MachineFunction &MF) {
    llvm_unreachable("runOnMachineFunction not implemented");
    return false;
}

FunctionPass *llvm::createDMGExpandPseudosPass() {
    return new DMGExpandPseudos();
}