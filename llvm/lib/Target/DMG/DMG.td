include "llvm/Target/Target.td"

// Subtarget features

// Registers, calling conventions, instruction descriptions

include "DMGRegisterInfo.td"
include "DMGInstrInfo.td"
include "DMGCallingConv.td"

def DMGInstrInfo : InstrInfo;

class Proc<string Name, list<SubtargetFeature> Features>
    : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

def DMG : Target {
    let InstructionSet = DMGInstrInfo;
}