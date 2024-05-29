#include "ABIInfoImpl.h"
#include "TargetInfo.h"
#include "clang/Basic/DiagnosticFrontend.h"

using namespace clang;
using namespace clang::CodeGen;

namespace {
class DMGABIInfo : public DefaultABIInfo {
private:
  const unsigned ParamRegs;
  const unsigned RetRegs;
public:
  DMGABIInfo(CodeGenTypes &CGT, unsigned NPR, unsigned NRR)
    : DefaultABIInfo(CGT), ParamRegs(NPR), RetRegs(NRR) {}

  ABIArgInfo classifyReturnType(QualType Ty, bool &LargeRet) const {
    return DefaultABIInfo::classifyReturnType(Ty);
  }

  ABIArgInfo classifyArgumentType(QualType Ty, unsigned &NumRegs) const {
    return ABIArgInfo::getDirect();
  }

  void computeInfo(CGFunctionInfo &FI) const override {}
};

class DMGTargetCodeGenInfo : public TargetCodeGenInfo {
public:
  DMGTargetCodeGenInfo(CodeGenTypes &CGT, unsigned NPR, unsigned NRR)
    : TargetCodeGenInfo(std::make_unique<DMGABIInfo>(CGT, NPR, NRR)) {}

  LangAS getGlobalVarAddressSpace(CodeGenModule &CGM,
                                  const VarDecl *D) const override {}
};
} // end anonymous namespace

std::unique_ptr<TargetCodeGenInfo>
CodeGen::createDMGTargetCodeGenInfo(CodeGenModule &CGM, unsigned NPR,
                                    unsigned NRR) {
  return std::make_unique<DMGTargetCodeGenInfo>(CGM.getTypes(), NPR, NRR);
}