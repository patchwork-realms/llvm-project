//===-- DMG.td - Describe the Game Boy Target  Machine--------------------===//
//
//
//===---------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===---------------------------------------------------------------------===//
// Subtarget features
//===---------------------------------------------------------------------===//
// def FeatureSoftMulDiv
//     : SubtargetFeature<"soft-mul-div", "UseSoftMulDiv", "true",
//                        "Use software emulation for integer multiply and divide">;

// def FeatureSoftFloat
//     : SubtargetFeature<"soft-float", "UseSoftFloat", "true",
//                        "Use software emulation for floating point">;

//===---------------------------------------------------------------------===//
// Registers, calling conventions, instruction descriptions
//===---------------------------------------------------------------------===//

include "DMGRegisterInfo.td"
include "DMGInstrInfo.td"
include "DMGCallingConv.td"

def DMGInstrInfo : InstrInfo;

//===---------------------------------------------------------------------===//
// Optional features are represented by new "processors"
//===---------------------------------------------------------------------===//
class Proc<string Name, list<SubtargetFeature> Features>
    : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",   []>;
// def : Proc<"v2",        [FeatureSoftMulDiv, FeatureSoftFloat]>;

//===---------------------------------------------------------------------===//
// Assembly Printers
//===---------------------------------------------------------------------===//
def DMGAsmWriter : AsmWriter {
    string AsmWriterClassName = "InstPrinter";
    bit isMCAsmWriter = 1;
}

//===---------------------------------------------------------------------===//
// Assembly Parsers
//===---------------------------------------------------------------------===//
def DMGAsmParser : AsmParser {
    let ShouldEmitMatchRegisterName = 1;
    let ShouldEmitMatchRegisterAltName = 1;
}

def DMGAsmParserVariant : AsmParserVariant {
    int Variant = 0;

    // Recognise hardcoded registers
    string RegisterPrefix = "$";
    string TokenizingCharacters = "+";
}

def DMG : Target {
    let InstructionSet = DMGInstrInfo;
    let AssemblyWriters = [DMGAsmWriter];
    let AssemblyParsers = [DMGAsmParser];
    let AssemblyParserVariants = [DMGAsmParserVariant];
}