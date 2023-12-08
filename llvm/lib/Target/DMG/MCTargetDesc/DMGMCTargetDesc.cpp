#include "DMGMCTargetDesc.h"
#include "DMGInstPrinter.h"
#include "DMGMCAsmInfo.h"
#include "DMGTargetStreamer.h"
#include "TargetInfo/DMGTargetInfo.h"

#include "llvm/MC/MCDwarf.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/TargetRegistry.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/FormattedStream.h"

#define GET_INSTRINFO_MC_DESC
#define ENABLE_INSTR_PREDICATE_VERIFIER
#include "DMGGenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "DMGGenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "DMGGenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createDMGMCInstrInfo() {
  auto *X = new MCInstrInfo();
  InitDMGMCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createDMGMCRegisterInfo(const Triple &TT) {
  auto *X = new MCRegisterInfo();
  InitDMGMCRegisterInfo(X, 0);
  return X;
}

static MCSubtargetInfo *createDMGMCSubtargetInfo(const Triple &TT,
                                                 StringRef CPU, StringRef FS) {
  return createDMGMCSubtargetInfoImpl(TT, CPU, /*TuneCPU=*/CPU, FS);
}

static MCAsmInfo *createDMGMCAsmInfo(const MCRegisterInfo &MRI,
                                     const Triple &TT,
                                     const MCTargetOptions &Options) {
  MCAsmInfo *MAI = new DMGMCAsmInfo(TT);

  // Initial state of the frame pointer is SP.
  // TODO: Actually add SP. This is a placeholder value to get the build working.
  MCCFIInstruction Inst = MCCFIInstruction::cfiDefCfa(nullptr, DMG::RA, 0);
  MAI->addInitialFrameState(Inst);

  return MAI;
}

static MCInstPrinter *createDMGMCInstPrinter(const Triple &T,
                                             unsigned SyntaxVariant,
                                             const MCAsmInfo &MAI,
                                             const MCInstrInfo &MII,
                                             const MCRegisterInfo &MRI) {
  return new DMGInstPrinter(MAI, MII, MRI);
}

DMGTargetStreamer::DMGTargetStreamer(MCStreamer &S) : MCTargetStreamer(S) {}
DMGTargetStreamer::~DMGTargetStreamer() = default;

static MCTargetStreamer *createTargetAsmStreamer(MCStreamer &S,
                                                 formatted_raw_ostream &OS,
                                                 MCInstPrinter *InstPrint,
                                                 bool isVerboseAsm) {
  return new DMGTargetStreamer(S);
}

// Force static initialization.
extern "C" LLVM_EXTERNAL_VISIBILITY void LLVMInitializeDMGTargetMC() {
  // Register the MC asm info.
  Target &TheDMGTarget = getTheDMGTarget();
  RegisterMCAsmInfoFn X(TheDMGTarget, createDMGMCAsmInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheDMGTarget, createDMGMCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheDMGTarget, createDMGMCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheDMGTarget,
                                          createDMGMCSubtargetInfo);

  // Register the MCInstPrinter
  TargetRegistry::RegisterMCInstPrinter(TheDMGTarget, createDMGMCInstPrinter);

  TargetRegistry::RegisterAsmTargetStreamer(TheDMGTarget,
                                            createTargetAsmStreamer);
}