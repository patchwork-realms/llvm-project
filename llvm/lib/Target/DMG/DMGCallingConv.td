def RetCC_DMG : CallingConv<[
    CCIfType<[i8], CCAssignToReg<[RA]>>
]>;

def CC_DMG : CallingConv<[
    CCIfType<[i8], CCAssignToReg<[RA]>>
]>;

def CSR_DMG : CalleeSavedRegs<(add RA)>;