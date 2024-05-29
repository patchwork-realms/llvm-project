#include "DMGInstPrinter.h"
// #include "MCTargetDesc/DMGInfo.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/MC/MCExpr.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/Support/Casting.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

#include "DMGGenAsmWriter.inc"

void DMGInstPrinter::printOperand(const MCInst *MI, unsigned OpNum,
                                  raw_ostream &O) {
  const MCOperand &Op = MI->getOperand(OpNum);
  assert(Op.isExpr() && "unknown operand kind in printOperand");
}

void DMGInstPrinter::printRegName(raw_ostream &OS, MCRegister Reg) const {}
void DMGInstPrinter::printInst(const MCInst *MI, uint64_t Address, StringRef Annot,
                               const MCSubtargetInfo &STI, raw_ostream &O) {}
void DMGInstPrinter::printCCOperand(const MCInst *MI, int OpNum, raw_ostream &O) {}
void DMGInstPrinter::printU6(const MCInst *MI, int OpNum, raw_ostream &O) {}