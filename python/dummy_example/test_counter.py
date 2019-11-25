import pytest

from counter import some_func


def test_example_1():
    assert some_func(10, 20) == 42


@pytest.mark.parametrize("A, B, expected", [
    (1,2, 42), (3,4, 42)
])
def test_example(A, B, expected):
    assert some_func(A, B) == expected
