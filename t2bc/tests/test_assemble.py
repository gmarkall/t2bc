from t2bc.binding import assemble

import pytest

mul_add = b'''\
; ModuleID = 'mul_add.bc'
source_filename = "<string>"

define i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
  %tmp = mul i32 %x, %y
  %tmp2 = add i32 %tmp, %z
  ret i32 %tmp2
}
'''

# Missing a closing curly brace
mul_add_bad_syntax = b'''\
; ModuleID = 'mul_add.bc'
source_filename = "<string>"

define i32 @mul_add(i32 %x, i32 %y, i32 %z) {
entry:
  %tmp = mul i32 %x, %y
  %tmp2 = add i32 %tmp, %z
  ret i32 %tmp2
'''

# Types of the mul operation have different types (i32, i64)
mul_add_bad_binop_types = b'''\
; ModuleID = 'mul_add.bc'
source_filename = "<string>"

define i32 @mul_add(i32 %x, i64 %y, i32 %z) {
entry:
  %tmp = mul i32 %x, %y
  %tmp2 = add i32 %tmp, %z
  ret i32 %tmp2
}
'''


def test_assemble_empty_string():
    bc = assemble(b'')
    assert bc[:4] == b'BC\xc0\xde'


def test_assemble_mul_add():
    bc = assemble(mul_add)
    assert bc[:4] == b'BC\xc0\xde'


def test_assemble_mul_add_bad_syntax():
    with pytest.raises(RuntimeError) as excinfo:
        assemble(mul_add_bad_syntax)

    msg = str(excinfo.value)
    assert "Error assembling LLVM IR" in msg
    assert "found end of file when expecting more instructions" in msg


def test_assemble_with_verification_error():
    with pytest.raises(RuntimeError) as excinfo:
        assemble(mul_add_bad_binop_types)

    msg = str(excinfo.value)
    assert "Error assembling LLVM IR" in msg
    assert "'%y' defined with type 'i64'" in msg
