#ifndef LLVM_CLANG_LIB_BASIC_TARGETS_DMG_H
#define LLVM_CLANG_LIB_BASIC_TARGETS_DMG_H

#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/TargetOptions.h"
#include "llvm/Support/Compiler.h"
#include "llvm/TargetParser/Triple.h"

namespace clang {
namespace targets {

// DMG Target (Game Boy)
class LLVM_LIBRARY_VISIBILITY DMGTargetInfo : public TargetInfo {
public:
  DMGTargetInfo(const llvm::Triple &Triple, const TargetOptions &)
  : TargetInfo(Triple) {
      resetDataLayout("e-p:16:8-i8:8-i16:16-i32:16-i64:16-f32:8-f64:8-n8-a:8");
  }

  void getTargetDefines(const LangOptions &Opts,
                        MacroBuilder &Builder) const override;

  ArrayRef<Builtin::Info> getTargetBuiltins() const override {
    return std::nullopt;
  }

  BuiltinVaListKind getBuiltinVaListKind() const override {
    return TargetInfo::VoidPtrBuiltinVaList;
  }

  bool validateAsmConstraint(const char *&Name,
                              TargetInfo::ConstraintInfo &Info) const override {
    if (StringRef(Name).size() > 1)
      return false;

    switch(*Name) {
    default:
      return false;
    }

    return false;
  }

  std::string_view getClobbers() const override { return ""; }

  ArrayRef<const char*> getGCCRegNames() const override {
    static const char *const GCCRegNames[] = {
          "ra", "rb", "rc", "rd", "rh", "rl", "rf", "pc", "sp"
    };
    return llvm::ArrayRef(GCCRegNames);
  }

  ArrayRef<TargetInfo::AddlRegName> getGCCAddlRegNames() const override {
    static const TargetInfo::AddlRegName AddlRegNames[] = {
      {{"rb", "rc"}, 1}
    };
    return llvm::ArrayRef(AddlRegNames);
  }

  ArrayRef<TargetInfo::GCCRegAlias> getGCCRegAliases() const override {
    return std::nullopt;
  }

protected:
  std::string CPU;
  StringRef ABI;
  StringRef DefineName;
  StringRef Arch;
};

} // end namespace targets
} // end namespace clang

#endif // LLVM_CLANG_LIB_BASIC_TARGETS_DMG_H