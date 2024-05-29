#include "DMGMCTargetDesc.h"
#include "DMGInstPrinter.h"
#include "DMGMCAsmInfo.h"
#include "TargetInfo/DMGTargetInfo.h"
#include "llvm/MC/MCInstrAnalysis.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/TargetParser/Host.h"

#define GET_INSTRINFO_MC_DESC
#include "DMGGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "DMGGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "DMGGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createDMGMCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitDMGMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createDMGMCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();
  InitDMGMCRegisterInfo(X, DMG::RA);
  return X;
}

static MCSubtargetInfo *createDMGMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createDMGMCSubtargetInfoImpl(TT, CPU, CPU, FS);
}

static MCStreamer *
createDMGMCStreamer(const Triple &T, MCContext &Ctx,
                    std::unique_ptr<MCAsmBackend> &&MAB,
                    std::unique_ptr<MCObjectWriter> &&OW,
                    std::unique_ptr<MCCodeEmitter> &&Emitter) {
  return createELFStreamer(Ctx, std::move(MAB), std::move(OW), std::move(Emitter));
}

static MCInstPrinter *createDMGMCInstPrinter(const Triple &T,
                                           unsigned SyntaxVariant,
                                           const MCAsmInfo &MAI,
                                           const MCInstrInfo &MII,
                                           const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new DMGInstPrinter(MAI, MII, MRI);
  return nullptr;
}

// TODO: Create DMGMCInstrAnalysis class?

extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGTargetMC() {
  for (Target *T : {&getTheDMGTarget()}) {
    RegisterMCAsmInfo<DMGMCAsmInfo> X(*T);
    TargetRegistry::RegisterMCInstrInfo(*T, createDMGMCInstrInfo);
    TargetRegistry::RegisterMCRegInfo(*T, createDMGMCRegisterInfo);
    TargetRegistry::RegisterMCSubtargetInfo(*T, createDMGMCSubtargetInfo);
    TargetRegistry::RegisterELFStreamer(*T, createDMGMCStreamer);
    TargetRegistry::RegisterMCInstPrinter(*T, createDMGMCInstPrinter);
    // InstructionAnalyzer goes here
  }

  // TODO: MCCodeEmitter, AsmBackend
  // TargetRegistry::RegisterMCCodeEmitter(getTheDMGTarget(), createDMGMCCodeEmitter);
  // TargetRegistry::RegisterMCAsmBackend(getTheDMGTarget(), createDMGAsmBackend);

}