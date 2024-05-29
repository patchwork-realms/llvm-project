// TODO: Placeholder return calling convention
def RetCC_DMG : CallingConv<[CCIfType<[i8], CCAssignToReg<[RA]>>]>;

// TODO: Placeholder calling convention
def CC_DMG : CallingConv<[CCIfType<[i8], CCAssignToReg<[RA]>>]>;

// TODO: This is a placeholder value!
def CSR : CalleeSavedRegs<(add RH, RL)>;