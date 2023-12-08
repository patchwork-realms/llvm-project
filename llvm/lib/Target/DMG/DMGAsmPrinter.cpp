#include "DMG.h"
#include "DMGMCInstLower.h"
#include "DMGSubtarget.h"
#include "DMGTargetMachine.h"
#include "MCTargetDesc/DMGInstPrinter.h"
#include "TargetInfo/DMGTargetInfo.h"

#include "llvm/CodeGen/AsmPrinter.h"
#include "llvm/CodeGen/MachineInstr.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

#define DEBUG_TYPE "asm-printer"

namespace {

class DMGAsmPrinter : public AsmPrinter {
    DMGMCInstLower MCInstLowering;

public:
    explicit DMGAsmPrinter(TargetMachine &TM,
                           std::unique_ptr<MCStreamer> Streamer)
            : AsmPrinter(TM, std::move(Streamer)),
              MCInstLowering(&OutContext, *this) {}

    StringRef getPassName() const override { return "Game Boy Assembly Printer"; }
    void emitInstruction(const MachineInstr *MI) override;

    bool runOnMachineFunction(MachineFunction &MF) override;
};

} // end anonymous namespace

void DMGAsmPrinter::emitInstruction(const MachineInstr *MI) {
    llvm_unreachable("DMGAsmPrinter::emitInstruction not implemented");
}

bool DMGAsmPrinter::runOnMachineFunction(MachineFunction &MF) {
    return AsmPrinter::runOnMachineFunction(MF);
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGAsmPrinter() {
    RegisterAsmPrinter<DMGAsmPrinter> X(getTheDMGTarget());
}