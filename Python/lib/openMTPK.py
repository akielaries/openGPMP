# This file was automatically generated by SWIG (https://www.swig.org).
# Version 4.1.1+fortran
#
# Do not make changes to this file unless you know what you are doing - modify
# the SWIG interface file instead.

from sys import version_info as _swig_python_version_info
# Import the low-level C/C++ module
if __package__ or "." in __name__:
    from . import _openMTPK
else:
    import _openMTPK

try:
    import builtins as __builtin__
except ImportError:
    import __builtin__


def _swig_repr(self):
    try:
        strthis = "proxy of " + self.this.__repr__()
    except __builtin__.Exception:
        strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__,
                             self.__class__.__name__, strthis,)


def _swig_setattr_nondynamic_instance_variable(set):
    def set_instance_attr(self, name, value):
        if name == "this":
            set(self, name, value)
        elif name == "thisown":
            self.this.own(value)
        elif hasattr(self, name) and isinstance(getattr(type(self), name), property):
            set(self, name, value)
        else:
            raise AttributeError(
                "You cannot add instance attributes to %s" %
                self)
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


class Primality(object):
    thisown = property(
        lambda x: x.this.own(),
        lambda x,
        v: x.this.own(v),
        doc="The membership flag")
    __repr__ = _swig_repr

    def is_prime(self, n):
        return _openMTPK.Primality_is_prime(self, n)

    def compute_miller_rabin(self, d, n):
        return _openMTPK.Primality_compute_miller_rabin(self, d, n)

    def miller_rabin_prime(self, n, iters):
        return _openMTPK.Primality_miller_rabin_prime(self, n, iters)

    def miller_rabin(self, inters, min_val, max_val):
        return _openMTPK.Primality_miller_rabin(self, inters, min_val, max_val)

    def jacobian_number(self, a, n):
        return _openMTPK.Primality_jacobian_number(self, a, n)

    def solovoy_strassen(self, p, iters):
        return _openMTPK.Primality_solovoy_strassen(self, p, iters)

    def mod_pow(self, base, exponent, mod):
        return _openMTPK.Primality_mod_pow(self, base, exponent, mod)

    def carmichael_num(self, n):
        return _openMTPK.Primality_carmichael_num(self, n)

    def sieve_of_eratosthenes(self, n):
        return _openMTPK.Primality_sieve_of_eratosthenes(self, n)

    def pollard_rho(self, n):
        return _openMTPK.Primality_pollard_rho(self, n)

    def ETF(self, n):
        return _openMTPK.Primality_ETF(self, n)

    def __init__(self):
        _openMTPK.Primality_swiginit(self, _openMTPK.new_Primality())
    __swig_destroy__ = _openMTPK.delete_Primality


# Register Primality in _openMTPK:
_openMTPK.Primality_swigregister(Primality)
BITS = _openMTPK.BITS
BYTE_LIMIT = _openMTPK.BYTE_LIMIT


class RC4(object):
    thisown = property(
        lambda x: x.this.own(),
        lambda x,
        v: x.this.own(v),
        doc="The membership flag")
    __repr__ = _swig_repr

    def byte_swap(self, a, b):
        return _openMTPK.RC4_byte_swap(self, a, b)

    def trad_swap(self, a, b):
        return _openMTPK.RC4_trad_swap(self, a, b)

    def XOR_swap(self, a, b):
        return _openMTPK.RC4_XOR_swap(self, a, b)

    def KSA(self, key, S, swap_type):
        return _openMTPK.RC4_KSA(self, key, S, swap_type)

    def PRGA(self, S, plaintext, ciphertext, swap_type):
        return _openMTPK.RC4_PRGA(self, S, plaintext, ciphertext, swap_type)

    def store_hash(self, plaintext, hashtext, swap_type):
        return _openMTPK.RC4_store_hash(self, plaintext, hashtext, swap_type)

    def compute(self, key, plaintext, hashtext, swap_type):
        return _openMTPK.RC4_compute(self, key, plaintext, hashtext, swap_type)

    def __init__(self):
        _openMTPK.RC4_swiginit(self, _openMTPK.new_RC4())
    __swig_destroy__ = _openMTPK.delete_RC4


# Register RC4 in _openMTPK:
_openMTPK.RC4_swigregister(RC4)


class Cipher(object):
    thisown = property(
        lambda x: x.this.own(),
        lambda x,
        v: x.this.own(v),
        doc="The membership flag")
    __repr__ = _swig_repr

    def C_cipher(self, plaintext, key):
        return _openMTPK.Cipher_C_cipher(self, plaintext, key)

    def KC_encode(self, key):
        return _openMTPK.Cipher_KC_encode(self, key)

    def KC_cipher(self, plaintext, encoded_text):
        return _openMTPK.Cipher_KC_cipher(self, plaintext, encoded_text)

    def __init__(self):
        _openMTPK.Cipher_swiginit(self, _openMTPK.new_Cipher())
    __swig_destroy__ = _openMTPK.delete_Cipher


# Register Cipher in _openMTPK:
_openMTPK.Cipher_swigregister(Cipher)
