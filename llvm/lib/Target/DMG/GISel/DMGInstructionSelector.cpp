#include "DMGInstrInfo.h"
#include "DMGRegisterBankInfo.h"
#include "DMGSubtarget.h"
#include "DMGTargetMachine.h"
#include "llvm/CodeGen/GlobalISel/GIMatchTableExecutorImpl.h"
#include "llvm/CodeGen/GlobalISel/InstructionSelector.h"
#include "llvm/CodeGen/GlobalISel/MachineIRBuilder.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/Support/Debug.h"
// #include "llvm/IR/IntrinsicsDMG.h"

#define DEBUG_TYPE "dmg-gisel"

using namespace llvm;

namespace {

#define GET_GLOBALISEL_PREDICATE_BITSET
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATE_BITSET

class DMGInstructionSelector : public InstructionSelector {
public:
  DMGInstructionSelector(const DMGTargetMachine &TM, const DMGSubtarget &STI,
                         const DMGRegisterBankInfo &RBI);

  bool select(MachineInstr &I) override;
  static const char *getName() { return DEBUG_TYPE; }

private:
  bool selectImpl(MachineInstr &I, CodeGenCoverage &CoverageInfo) const;

  const DMGInstrInfo &TII;
  const DMGRegisterInfo &TRI;
  const DMGRegisterBankInfo &RBI;

#define GET_GLOBALISEL_PREDICATES_DECL
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_DECL

#define GET_GLOBALISEL_TEMPORARIES_DECL
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_DECL
};
} // end namespace

#define GET_GLOBALISEL_IMPL
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_IMPL

DMGInstructionSelector::DMGInstructionSelector(const DMGTargetMachine &TM,
                                               const DMGSubtarget &STI,
                                               const DMGRegisterBankInfo &RBI)
    : TII(*STI.getInstrInfo()), TRI(*STI.getRegisterInfo()), RBI(RBI),
#define GET_GLOBALISEL_PREDICATES_INIT
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_PREDICATES_INIT
#define GET_GLOBALISEL_TEMPORARIES_INIT
#include "DMGGenGlobalISel.inc"
#undef GET_GLOBALISEL_TEMPORARIES_INIT
{
}

bool DMGInstructionSelector::select(MachineInstr &I) {
  if (!isPreISelGenericOpcode(I.getOpcode()))
    return true;
  if (selectImpl(I, *CoverageInfo))
    return true;
  return false;
}

namespace llvm {
InstructionSelector *
createDMGInstructionSelector(const DMGTargetMachine &TM,
                             const DMGSubtarget &Subtarget,
                             const DMGRegisterBankInfo &RBI) {
  return new DMGInstructionSelector(TM, Subtarget, RBI);
}
}
