add_llvm_component_library(LLVMDMGDesc
  DMGMCTargetDesc.cpp
  DMGInstPrinter.cpp
  # DMGMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  DMGInfo

  ADD_TO_COMPONENT
  DMG
)