#include "DMG.h"
#include "DMGTargetMachine.h"
#include "TargetInfo/DMGTargetInfo.h"
#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineConstantPool.h"
#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/CodeGen/MachineModuleInfo.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {
class DMGAsmPrinter : public AsmPrinter {
public:
  explicit DMGAsmPrinter(TargetMachine &TM,
                         std::unique_ptr<MCStreamer> Streamer)
      : AsmPrinter(TM, std::move(Streamer)) {}
};
} // namespace

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGAsmPrinter() {
  RegisterAsmPrinter<DMGAsmPrinter> X(getTheDMGTarget());
}