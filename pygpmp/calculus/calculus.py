# This file was automatically generated by SWIG (https://www.swig.org).
# Version 4.1.0
#
# Do not make changes to this file unless you know what you are doing - modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _calculus
else:
    import _calculus

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__

def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "this":
            set(self, name, value)
        elif name == "thisown":
            self.this.own(value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError("You cannot add instance attributes to %s" % self)
    return set_instance_attr


def _swig_setattr_nondynamic_class_variable(set):
    def set_class_attr(cls, name, value):
        if hasattr(cls, name) and not isinstance(getattr(cls, name), property):
            set(cls, name, value)
        else:
            raise AttributeError("You cannot add class attributes to %s" % cls)
    return set_class_attr


def _swig_add_metaclass(metaclass):
    """Class decorator for adding a metaclass to a SWIG wrapped class - a slimmed down version of six.add_metaclass"""
    def wrapper(cls):
        return metaclass(cls.__name__, cls.__bases__, cls.__dict__.copy())
    return wrapper


class _SwigNonDynamicMeta(type):
    """Meta class to enforce nondynamic attributes (no new attributes) for a class"""
    __setattr__ = _swig_setattr_nondynamic_class_variable(type.__setattr__)


class SwigPyIterator(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")

    def __init__(self, *args, **kwargs):
        raise AttributeError("No constructor defined - class is abstract")
    __repr__ = _swig_repr
    __swig_destroy__ = _calculus.delete_SwigPyIterator

    def value(self):
        return _calculus.SwigPyIterator_value(self)

    def incr(self, n=1):
        return _calculus.SwigPyIterator_incr(self, n)

    def decr(self, n=1):
        return _calculus.SwigPyIterator_decr(self, n)

    def distance(self, x):
        return _calculus.SwigPyIterator_distance(self, x)

    def equal(self, x):
        return _calculus.SwigPyIterator_equal(self, x)

    def copy(self):
        return _calculus.SwigPyIterator_copy(self)

    def next(self):
        return _calculus.SwigPyIterator_next(self)

    def __next__(self):
        return _calculus.SwigPyIterator___next__(self)

    def previous(self):
        return _calculus.SwigPyIterator_previous(self)

    def advance(self, n):
        return _calculus.SwigPyIterator_advance(self, n)

    def __eq__(self, x):
        return _calculus.SwigPyIterator___eq__(self, x)

    def __ne__(self, x):
        return _calculus.SwigPyIterator___ne__(self, x)

    def __iadd__(self, n):
        return _calculus.SwigPyIterator___iadd__(self, n)

    def __isub__(self, n):
        return _calculus.SwigPyIterator___isub__(self, n)

    def __add__(self, n):
        return _calculus.SwigPyIterator___add__(self, n)

    def __sub__(self, *args):
        return _calculus.SwigPyIterator___sub__(self, *args)
    def __iter__(self):
        return self

# Register SwigPyIterator in _calculus:
_calculus.SwigPyIterator_swigregister(SwigPyIterator)
class Term(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    coefficient = property(_calculus.Term_coefficient_get, _calculus.Term_coefficient_set)
    exponent = property(_calculus.Term_exponent_get, _calculus.Term_exponent_set)

    def __init__(self, coef, exp):
        _calculus.Term_swiginit(self, _calculus.new_Term(coef, exp))
    __swig_destroy__ = _calculus.delete_Term

# Register Term in _calculus:
_calculus.Term_swigregister(Term)
class Differential(object):
    thisown = property(lambda x: x.this.own(), lambda x, v: x.this.own(v), doc="The membership flag")
    __repr__ = _swig_repr
    terms = property(_calculus.Differential_terms_get, _calculus.Differential_terms_set)

    def __add__(self, other):
        return _calculus.Differential___add__(self, other)

    def __mul__(self, other):
        return _calculus.Differential___mul__(self, other)

    def add_term(self, coefficient, exponent):
        return _calculus.Differential_add_term(self, coefficient, exponent)

    def display(self):
        return _calculus.Differential_display(self)

    def power_rule(self):
        return _calculus.Differential_power_rule(self)

    def product_rule(self, other):
        return _calculus.Differential_product_rule(self, other)

    def quotient_rule(self, other):
        return _calculus.Differential_quotient_rule(self, other)

    def chain_rule(self, inner):
        return _calculus.Differential_chain_rule(self, inner)

    def nth_derivative(self, n):
        return _calculus.Differential_nth_derivative(self, n)

    def eval(self, x):
        return _calculus.Differential_eval(self, x)

    def limit_at(self, x):
        return _calculus.Differential_limit_at(self, x)

    def limit_at_infinity(self):
        return _calculus.Differential_limit_at_infinity(self)

    def __init__(self):
        _calculus.Differential_swiginit(self, _calculus.new_Differential())
    __swig_destroy__ = _calculus.delete_Differential

# Register Differential in _calculus:
_calculus.Differential_swigregister(Differential)

