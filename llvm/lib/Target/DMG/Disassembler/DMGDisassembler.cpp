#include "DMG.h"
#include "DMGRegisterInfo.h"
#include "MCTargetDesc/DMGMCTargetDesc.h"
#include "TargetInfo/DMGTargetInfo.h"
#include "llvm/MC/MCContext.h"
#include "llvm/MC/MCDecoderOps.h"
#include "llvm/MC/MCDisassembler/MCDisassembler.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "dmg-disassembler"

using DecodeStatus = MCDisassembler::DecodeStatus;

namespace {

class DMGDisassembler : public MCDisassembler {
public:
    std::unique_ptr<MCInstrInfo const> const MCII;

    DMGDisassembler(const MCSubtargetInfo &STI, MCContext &Ctx,
                    MCInstrInfo const *MCII)
            : MCDisassembler(STI, Ctx), MCII(MCII) {}

    
    DecodeStatus getInstruction(MCInst &Instr, uint64_t &Size,
                                ArrayRef<uint8_t> Bytes, uint64_t Address,
                                raw_ostream &Cstream) const override;
    
};

} // end anonymous namespace

DecodeStatus DMGDisassembler::getInstruction(MCInst &Instr, uint64_t &Size,
                                             ArrayRef<uint8_t> Bytes,
                                             uint64_t Address,
                                             raw_ostream &cStream) const {
    llvm_unreachable("DMGDisassembler::getInstruction not implemented");
    MCDisassembler::DecodeStatus Result;
    return Result;
}

static MCDisassembler *createDMGDisassembler(const Target &T,
                                             const MCSubtargetInfo &STI,
                                             MCContext &Ctx) {
    return new DMGDisassembler(STI, Ctx, T.createMCInstrInfo());
}

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGDisassembler() {
  // Register the disassembler.
  TargetRegistry::RegisterMCDisassembler(getTheDMGTarget(),
                                         createDMGDisassembler);
}