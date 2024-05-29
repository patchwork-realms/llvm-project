#include "DMG.h"
#include "clang/Basic/MacroBuilder.h"
#include "llvm/ADT/StringSwitch.h"

using namespace clang;
using namespace clang::targets;

namespace clang {
namespace targets {

} // end namespace targets
} // end namespace clang

void DMGTargetInfo::getTargetDefines(const LangOptions &Opts,
                                     MacroBuilder &Builder) const {
  Builder.defineMacro("DMG");
  Builder.defineMacro("__DMG");
  Builder.defineMacro("__DMG__");
}