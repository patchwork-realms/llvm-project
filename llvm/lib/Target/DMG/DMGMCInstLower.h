#ifndef LLVM_LIB_TARGET_DMG_DMGMCINSTLOWER_H
#define LLVM_LIB_TARGET_DMG_DMGMCINSTLOWER_H

#include "llvm/CodeGen/MachineOperand.h"
#include "llvm/Support/Compiler.h"

namespace llvm {

class MCContext;
class MCInst;
class MCOperand;
class MachineInstr;
class MachineFunction;
class Mangler;
class AsmPrinter;

class LLVM_LIBRARY_VISIBILITY DMGMCInstLower {
    using MachineOperandType = MachineOperand::MachineOperandType;
    MCContext *Ctx;
    AsmPrinter &Printer;

public:
    DMGMCInstLower(MCContext *C, AsmPrinter &asmprinter);
    void Lower(const MachineInstr *MI, MCInst &OutMI) const;
    MCOperand LowerOperand(const MachineOperand &MO, unsigned offset = 0) const;

private:
    MCOperand LowerSymbolOperand(const MachineOperand &MO,
                                 MachineOperandType MOTy, unsigned Offset) const;
};

} // end namespace llvm;

#endif // LLVM_LIB_TARGET_DMG_DMGINSTLOWER_H