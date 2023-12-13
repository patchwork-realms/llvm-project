include "DMGInstrFormats.td"

def HasSoftFloat    : Predicate<"Subtarget->hasSoftFloat()">;
def HasSoftMulDiv   : Predicate<"Subtarget->hasSoftMulDiv()">;

def NOP : GBF0<0b00000000, (outs), (ins), "nop", []>;