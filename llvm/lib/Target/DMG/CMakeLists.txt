add_llvm_component_group(DMG)

set(LLVM_TARGET_DEFINITIONS DMG.td)

tablegen(LLVM DMGGenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM DMGGenCallingConv.inc -gen-callingconv)
tablegen(LLVM DMGGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM DMGGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM DMGGenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM DMGGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM DMGGenSubtargetInfo.inc -gen-subtarget)
tablegen(LLVM DMGGenGlobalISel.inc -gen-global-isel)
tablegen(LLVM DMGGenRegisterBank.inc -gen-register-bank)

add_public_tablegen_target(DMGCommonTableGen)

add_llvm_target(DMGCodeGen
  GISel/DMGCallLowering.cpp
  GISel/DMGInstructionSelector.cpp
  GISel/DMGLegalizerInfo.cpp
  GISel/DMGRegisterBankInfo.cpp
  DMGAsmPrinter.cpp
  DMGFrameLowering.cpp
  DMGInstrInfo.cpp
  # DMGISelDAGToDAG.cpp
  # DMGISelLowering.cpp
  # DMGMachineFunctionInfo.cpp
  # DMGMCInstLower.cpp
  DMGRegisterInfo.cpp
  DMGSubtarget.cpp
  DMGTargetMachine.cpp

  LINK_COMPONENTS
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  DMGDesc
  DMGInfo
  GlobalISel
  MC
  Support
  Target
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  DMG
)

add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
# add_subdirectory(Disassembler)