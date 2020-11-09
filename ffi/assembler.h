#ifndef T2BC_ASSEMBLER_H_
#define T2BC_ASSEMBLER_H_


#if defined(_MSC_VER)
    #define HAVE_DECLSPEC_DLL
#endif

#if defined(HAVE_DECLSPEC_DLL)
    #define API_EXPORT(RTYPE) __declspec(dllexport) RTYPE
#else
    #define API_EXPORT(RTYPE) RTYPE
#endif

extern "C" {

  void assemble(const char *ir);

}

#endif /* T2BC_ASSEMBLER_H_ */
