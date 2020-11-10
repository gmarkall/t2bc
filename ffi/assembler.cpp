#include "assembler.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/InitLLVM.h"
#include "llvm/Support/raw_ostream.h"

#include "llvm-c/Core.h"
#include "llvm-c/Support.h"

#include <cstdio>
#include <unistd.h>
#include <memory>
#include <iostream>

API_EXPORT(void)
assemble(LLVMContextRef context, const char *ir)
{
  printf("%s\n", ir);

  llvm::SMDiagnostic error;

  printf("parse assembly\n");
  std::unique_ptr<llvm::Module> m = llvm::parseAssemblyString(ir, error, *llvm::unwrap(context));

  printf("Check error\n");
  if (!m) {
    llvm::raw_fd_ostream s(STDERR_FILENO, false);
    // Error occurred
    printf("Print error\n");
    error.print("test prog", s);
  }
  else {
    printf("Parsed OK\n");
  }

  std::string errorStr;
  llvm::raw_string_ostream os(errorStr);

  if (llvm::verifyModule(*m.get(), &os)) {
    printf("Verification failed\n");
    std::cerr << os.str() << std:: endl;
  } else {
    printf("Verification OK\n");
  }
}

API_EXPORT(LLVMContextRef)
T2BC_GetGlobalContext()
{
  return LLVMGetGlobalContext();
}

API_EXPORT(LLVMContextRef)
T2BC_ContextCreate() {
  return LLVMContextCreate();
}

API_EXPORT(void)
T2BC_ContextDispose(LLVMContextRef context) {
  LLVMContextDispose(context);
}

