//===---------------------------------------------------------------------===//
//  Declarations that describe the Game Boy register set
//===---------------------------------------------------------------------===//

class DMGReg<bits<16> num, string name, list<Register> subregs = [],
             list<string> altNames = []> : RegisterWithSubRegs<name, subregs> {
    field bits<16> Num = num;
    let HWEncoding = num;
    let Namespace = "DMG";
    let SubRegs = subregs;
    let AltNames = altNames;
}

let Namespace = "DMG" in {
    def sub_lo : SubRegIndex<8>;
    def sub_hi : SubRegIndex<8, 8>;
}

let Namespace = "DMG" in { def ptr : RegAltNameIndex; }

//===---------------------------------------------------------------------===//
// 8-bit general-purpose registers A through L
//===---------------------------------------------------------------------===//
def RA : DMGReg<0, "a">, DwarfRegNum<[0]>;
def RF : DMGReg<1, "f">, DwarfRegNum<[1]>;
def RB : DMGReg<2, "b">, DwarfRegNum<[2]>;
def RC : DMGReg<3, "c">, DwarfRegNum<[3]>;
def RD : DMGReg<4, "d">, DwarfRegNum<[4]>;
def RE : DMGReg<4, "e">, DwarfRegNum<[5]>;
def RH : DMGReg<5, "h">, DwarfRegNum<[6]>;
def RL : DMGReg<6, "l">, DwarfRegNum<[7]>;

//===---------------------------------------------------------------------===//
// 16-bit general-purpose registers AF through HL
//===---------------------------------------------------------------------===//
let SubRegIndices = [sub_lo, sub_hi], CoveredBySubRegs = 1 in {
    def RARF : DMGReg<0, "af", [RA, RF]>, DwarfRegNum<[0]>;
    def RBRC : DMGReg<2, "bc", [RB, RC]>, DwarfRegNum<[2]>;
    def RDRE : DMGReg<4, "de", [RD, RE]>, DwarfRegNum<[4]>;
    def RHRL : DMGReg<6, "hl", [RH, RL]>, DwarfRegNum<[6]>;
}

//===---------------------------------------------------------------------===//
// Special registers
//===---------------------------------------------------------------------===//
def SP : DMGReg<8, "sp">, DwarfRegNum<[8]>;
def PC : DMGReg<9, "pc">, DwarfRegNum<[9]>;

//===---------------------------------------------------------------------===//
// Register classes
//===---------------------------------------------------------------------===//
def GPR8    : RegisterClass<"DMG", [i8], 8, (add RA, RB, RC, RD, RE, RH, RL)>;
def GPR16   : RegisterClass<"DMG", [i16], 16, (add RBRC, RDRE, RHRL)>;