#include "assembler.h"
#include "llvm/AsmParser/Parser.h"
#include "llvm/Bitcode/BitcodeWriter.h"
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
#include <iomanip>

void print_bitcode(const std::string& bc)
{
  std::cerr << bc;
  return;

  char c = std::cerr.fill('0');
  std::cerr << std::hex << std::setw(2);

  for (const char& c: bc) {
    std::cerr << c;
  }

  std::cerr.fill(c);
  std::cerr << std::dec << std::setw(2);
}

API_EXPORT(size_t)
assemble(LLVMContextRef context, const char *ir, const char **bitcode, const char **errormsg)
{
  llvm::SMDiagnostic error;

  std::unique_ptr<llvm::Module> m = llvm::parseAssemblyString(ir, error, *llvm::unwrap(context));

  if (!m) {
    // Error occurred
    std::string errbuf;
    llvm::raw_string_ostream s(errbuf);
    error.print("", s);
    s.flush();
    *errormsg = T2BC_CreateString(s.str().c_str());
    return 0;
  }

  std::string errorStr;
  llvm::raw_string_ostream os(errorStr);

  if (llvm::verifyModule(*m.get(), &os)) {
    *errormsg = T2BC_CreateString(os.str().c_str());
    return 0;
  }

  std::string tmp;
  llvm::raw_string_ostream bcs(tmp);

  llvm::WriteBitcodeToFile(*m, bcs);
  size_t len = bcs.str().size();
  char* copy = (char*)malloc(sizeof(char) * len);
  memcpy(copy, bcs.str().c_str(), sizeof(char) * len);
  *bitcode = copy;
  return len;
}

API_EXPORT(const char *)
T2BC_CreateString(const char *msg)
{
  return strdup(msg);
}

API_EXPORT(void)
T2BC_DisposeString(const char *msg)
{
  free(const_cast<char*>(msg));
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

