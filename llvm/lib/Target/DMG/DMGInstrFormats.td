// Generic Game Boy instruction
class DMGInst<dag outs, dag ins, string asmstr, list<dag> pattern>
  : Instruction {
  let Namespace = "DMG";
  dag OutOperandList = outs;
  dag InOperandList = ins;
  let AsmString = asmstr;
  let Pattern = pattern;
  field bits<32> SoftFail = 0;
}

// 8-bit Instruction
class DMGInst8<dag outs, dag ins, string asmstr, list<dag> pattern>
  : DMGInst<outs, ins, asmstr, pattern> {
  field bits<8> Inst;
  let Size = 1;
}

// FORMATS
// Format 0: No Operands
class GBF0<bits<8> op, dag outs, dag ins, string asmstr, list<dag> pattern>
: DMGInst8<outs, ins, asmstr, pattern>
{
  let Inst{7 - 0} = op;
}