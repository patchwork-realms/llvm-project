include "DMGInstrFormats.td"

// TODO: Remove this- just a placeholder to get the build
// working successfully!
def AddRdRr : GBF0<0b11111111,
                   (outs GPR : $rd),
                   (ins GPR : $src, GPR : $rr),
                   "add\t$rd, $rr",
                   [(set i8 : $rd, 
                      (add i8 : $src, i8 : $rr))]>;
def NOP : GBF0<0b00000000, (outs), (ins), "nop", []>;
def RET : GBF0<0b11001001, (outs), (ins), "RET", []>;