add_llvm_component_library(LLVMDMGDesc
  DMGInstPrinter.cpp
  DMGMCTargetDesc.cpp
  # DMGMCAsmInfo.cpp

  LINK_COMPONENTS
  MC
  Support
  DMGInfo

  ADD_TO_COMPONENT
  DMG
)