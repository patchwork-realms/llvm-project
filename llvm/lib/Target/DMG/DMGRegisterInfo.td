//===---------------------------------------------------------------------===//
//  Declarations that describe the Game Boy register set
//===---------------------------------------------------------------------===//

class DMGReg<string n, list<string> altNames> : Register<n, altNames> {
    field bits<16> HWEncoding;
    let Namespace = "DMG";
}

class DMGReg8<int num, string n, list<string>altNames=[]> : DMGReg<n, altNames> {
    let HWEncoding = num;
}

def RA : DMGReg8<1, "ra">, DwarfRegNum<[1]>;

def GPR : RegisterClass<"DMG", [i8], 8, (add RA)>;