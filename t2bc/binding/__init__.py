from t2bc.binding import ffi
from t2bc.binding.context import get_global_context

import ctypes
import sys

def assemble(llvmir, context=None):
    if context is None:
        context = get_global_context()
    charbuf = ctypes.c_char_p(llvmir)
    with ffi.OutputString() as errmsg:
        with ffi.OutputBytes() as bitcode:
            size = ffi.lib.assemble(context, charbuf, bitcode, errmsg)
            if size == 0:
                raise RuntimeError(f"Error assembling LLVM IR:\n{errmsg}")
            data = ctypes.POINTER(ctypes.c_char).from_buffer(bitcode._ptr)[:size]
            return data
