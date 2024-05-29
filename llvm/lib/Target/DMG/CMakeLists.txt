add_llvm_component_group(DMG)

set(LLVM_TARGET_DEFINITIONS DMG.td)

tablegen(LLVM DMGGenAsmWriter.inc -gen-asm-writer)
# tablegen(LLVM DMGGenCallingConv.inc -gen-callingconv)
# tablegen(LLVM DMGGenDAGISel.inc -gen-dag-isel)
# tablegen(LLVM DMGGenDisassemblerTables.inc -gen-disassembler)
tablegen(LLVM DMGGenInstrInfo.inc -gen-instr-info)
tablegen(LLVM DMGGenRegisterInfo.inc -gen-register-info)
tablegen(LLVM DMGGenSubtargetInfo.inc -gen-subtarget)

add_public_tablegen_target(DMGCommonTableGen)

add_llvm_target(DMGCodeGen
  # DMGAsmPrinter.cpp
  # DMGBranchFinalize.cpp
  # DMGExpandPseudos.cpp
  # DMGFrameLowering.cpp
  # DMGInstrInfo.cpp
  # DMGISelDAGToDAG.cpp
  # DMGISelLowering.cpp
  # DMGMachineFunctionInfo.cpp
  # DMGMCInstLower.cpp
  # DMGRegisterInfo.cpp
  # DMGSubtarget.cpp
  # DMGTargetMachine.cpp

  LINK_COMPONENTS
  # DMGDesc
  # DMGInfo
  Analysis
  AsmPrinter
  CodeGen
  CodeGenTypes
  Core
  MC
  SelectionDAG
  Support
  Target
  TargetParser
  TransformUtils

  ADD_TO_COMPONENT
  DMG
)

add_subdirectory(MCTargetDesc)
add_subdirectory(TargetInfo)
# add_subdirectory(Disassembler)