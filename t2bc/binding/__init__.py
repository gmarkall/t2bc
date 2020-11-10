from ctypes import c_char_p
from t2bc.binding import ffi
from t2bc.binding.context import get_global_context


def assemble(llvmir, context=None):
    if context is None:
        context = get_global_context()
    charbuf = c_char_p(llvmir)
    ffi.lib.assemble(context, charbuf)

