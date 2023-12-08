#include "DMGMCInstLower.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"

using namespace llvm;

DMGMCInstLower::DMGMCInstLower(MCContext *C, AsmPrinter &AsmPrinter)
    : Ctx(C), Printer(AsmPrinter) {}

MCOperand DMGMCInstLower::LowerSymbolOperand(const MachineOperand &MO,
                                             MachineOperandType MOTy,
                                             unsigned Offset) const {
    llvm_unreachable("LowerOperand not implemented");
    return {};
}

MCOperand DMGMCInstLower::LowerOperand(const MachineOperand &MO,
                                             unsigned offset) const {
    llvm_unreachable("LowerOperand not implemented");
    return {};
}

void DMGMCInstLower::Lower(const MachineInstr *MI, MCInst &OutMI) const {}

