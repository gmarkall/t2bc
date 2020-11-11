import faulthandler
import warnings


try:
    faulthandler.enable()
except BaseException as exc:
    warnings.warn(f"Failed to enable faulthandler due to:\n{exc}")
