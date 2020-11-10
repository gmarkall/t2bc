from t2bc.binding import ffi


def create_context():
    return ContextRef(ffi.lib.T2BC_ContextCreate())


def get_global_context():
    return GlobalContextRef(ffi.lib.T2BC_GetGlobalContext())


class ContextRef(ffi.ObjectRef):
    def __init__(self, context_ptr):
        super(ContextRef, self).__init__(context_ptr)

    def _dispose(self):
        ffi.lib.T2BC_ContextDispose(self)


class GlobalContextRef(ContextRef):
    def _dispose(self):
        pass


ffi.lib.T2BC_GetGlobalContext.restype = ffi.LLVMContextRef

ffi.lib.T2BC_ContextCreate.restype = ffi.LLVMContextRef

ffi.lib.T2BC_ContextDispose.argtypes = [ffi.LLVMContextRef]
