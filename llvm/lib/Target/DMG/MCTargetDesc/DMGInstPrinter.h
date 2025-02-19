#ifndef LLVM_LIB_TARGET_DMG_DMGINSTPRINTER_H
#define LLVM_LIB_TARGET_DMG_DMGINSTPRINTER_H

#include "llvm/MC/MCInstPrinter.h"

namespace llvm {

class DMGInstPrinter : public MCInstPrinter {
public:
    DMGInstPrinter(const MCAsmInfo &MAI, const MCInstrInfo &MII,
                   const MCRegisterInfo &MRI)
            : MCInstPrinter(MAI, MII, MRI) {}

    // Autogenerated by table gen
    std::pair<const char *, uint64_t> getMnemonic(const MCInst *MI) override;
    void printInstruction(const MCInst *MI, uint64_t Address, raw_ostream &O);
    static const char *getRegisterName(MCRegister Reg);

    void printRegName(raw_ostream &OS, MCRegister Reg) const override;
    void printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                    const MCSubtargetInfo &STI, raw_ostream &O) override;
    void printCCOperand(const MCInst *MI, int OpNum, raw_ostream &O);
    void printU6(const MCInst *MI, int OpNum, raw_ostream &O);

private:
    void printMemOperandRI(const MCInst *MI, unsigned OpNum, raw_ostream &O);
    void printOperand(const MCInst *MI, unsigned OpNum, raw_ostream &O);
    void printOperand(const MCInst *MI, uint64_t /*Address*/, unsigned OpNum,
                        raw_ostream &O) {
        printOperand(MI, OpNum, O);
    }
    void printPredicateOperand(const MCInst *MI, unsigned OpNum, raw_ostream &O);
    void printBRCCPredicateOperand(const MCInst *MI, unsigned OpNum,
                                    raw_ostream &O);
    void printU6ShiftedBy(unsigned ShiftBy, const MCInst *MI, int OpNum,
                            raw_ostream &O);
};
} // end namespace llvm

#endif // LLVM_LIB_TARGET_DMG_DMGINSTPRINTER_H