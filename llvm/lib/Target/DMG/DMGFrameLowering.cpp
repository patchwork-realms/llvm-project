#include "DMGFrameLowering.h"

#include "DMGMachineFunctionInfo.h"
#include "DMGSubtarget.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetRegisterInfo.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/Debug.h"

#define DEBUG_TYPE "dmg-frame-lowering"

using namespace llvm;

void DMGFrameLowering::emitPrologue(MachineFunction &MF, MachineBasicBlock &MBB) const {

}

void DMGFrameLowering::emitEpilogue(MachineFunction &MF, MachineBasicBlock &MBB) const {

}

bool DMGFrameLowering::hasFP(const MachineFunction &MF) const {
    return false;
}

using namespace llvm;