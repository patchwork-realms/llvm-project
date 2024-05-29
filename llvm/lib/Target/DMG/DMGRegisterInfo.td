// Declarations that describe the Game Boy register set
class DMGReg<bits<16> num, string name, list<Register> subregs = [],
             list<string> altNames = []> : RegisterWithSubRegs<name, subregs> {
  field bits<16> Num = num;
  let HWEncoding = num;
  let Namespace = "DMG";
  let SubRegs = subregs;
  let AltNames = altNames;
}

// 8-bit general-purpose registers A through L
def RA : DMGReg<0, "a">, DwarfRegNum<[0]>;
def RF : DMGReg<1, "f">, DwarfRegNum<[1]>;
def RB : DMGReg<2, "b">, DwarfRegNum<[2]>;
def RC : DMGReg<3, "c">, DwarfRegNum<[3]>;
def RD : DMGReg<4, "d">, DwarfRegNum<[4]>;
def RE : DMGReg<5, "e">, DwarfRegNum<[5]>;
def RH : DMGReg<6, "h">, DwarfRegNum<[6]>;
def RL : DMGReg<7, "l">, DwarfRegNum<[7]>;

// Special registers
def SP : DMGReg<8, "sp">, DwarfRegNum<[8]>;
def PC : DMGReg<9, "pc">, DwarfRegNum<[9]>;

def GPR8 : RegisterClass<"DMG", [i8], 8, (add RA, RB, RC, RD, RE, RH, RL)>;