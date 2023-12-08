add_llvm_component_library(LLVMDMGDisassembler
  DMGDisassembler.cpp

  LINK_COMPONENTS
  DMGInfo
  CodeGenTypes
  MCDisassembler
  Support

  ADD_TO_COMPONENT
  DMG
)