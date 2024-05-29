add_llvm_component_library(LLVMDMGInfo
  DMGTargetInfo.cpp

  LINK_COMPONENTS
  MC
  Support

  ADD_TO_COMPONENT
  DMG
)