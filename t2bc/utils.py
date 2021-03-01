import os


# This module must be importable without loading the binding, to avoid
# bootstrapping issues in setup.py.

def get_library_name():
    """
    Return the name of the llvmlite shared library file.
    """
    if os.name == 'posix':
        return 'libt2bc.so'
    else:
        assert os.name == 'nt'
        return 't2bc.dll'


def get_library_files():
    """
    Return the names of shared library files needed for this platform.
    """
    files = [get_library_name()]
    if os.name == 'nt':
        files.extend(['msvcr120.dll', 'msvcp120.dll'])
    return files
