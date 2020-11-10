#ifndef T2BC_ASSEMBLER_H_
#define T2BC_ASSEMBLER_H_

#include "llvm-c/Types.h"

#if defined(_MSC_VER)
  #define HAVE_DECLSPEC_DLL
#endif

#if defined(HAVE_DECLSPEC_DLL)
  #define API_EXPORT(RTYPE) __declspec(dllexport) RTYPE
#else
  #define API_EXPORT(RTYPE) RTYPE
#endif

extern "C" {

  API_EXPORT(void)
  assemble(LLVMContextRef ref, const char *ir);

  API_EXPORT(LLVMContextRef)
  T2BC_GetGlobalContext();

  API_EXPORT(LLVMContextRef)
  T2BC_ContextCreate();

  API_EXPORT(void)
  T2BC_ContextDispose(LLVMContextRef context);

}

#endif /* T2BC_ASSEMBLER_H_ */
