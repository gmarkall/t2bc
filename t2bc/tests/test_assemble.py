from t2bc.binding import assemble


def test_assemble_empty_string():
    bc = assemble(b'')
    assert bc[:4] == b'BC\xc0\xde'
