from ctypes import c_char_p
from t2bc.binding import ffi


def assemble(llvmir):
    charbuf = c_char_p(llvmir)
    ffi.lib.assemble(charbuf)

