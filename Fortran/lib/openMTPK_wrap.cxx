/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.1.1+fortran
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */
/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif


#ifndef SWIGEXTERN
# ifdef __cplusplus
#   define SWIGEXTERN extern
# else
#   define SWIGEXTERN
# endif
#endif


#define SWIG_exception_impl(DECL, CODE, MSG, RETURNNULL) \
 { throw std::logic_error("In " DECL ": " MSG); }


enum SwigMemFlags {
    SWIG_MEM_OWN = 0x01,
    SWIG_MEM_RVALUE = 0x02,
};


#define SWIG_check_nonnull(PTR, TYPENAME, FNAME, FUNCNAME, RETURNNULL) \
  if (!(PTR)) { \
    SWIG_exception_impl(FUNCNAME, SWIG_NullReferenceError, \
                        "Cannot pass null " TYPENAME " (class " FNAME ") " \
                        "as a reference", RETURNNULL); \
  }


namespace swig {
enum AssignmentType {
  ASSIGNMENT_DEFAULT,
  ASSIGNMENT_NODESTRUCT,
  ASSIGNMENT_SMARTPTR
};
}



#define SWIG_VERSION 0x040101
#define SWIGFORTRAN
#define SWIGPOLICY_Primality swig::ASSIGNMENT_DEFAULT
#define SWIGPOLICY_RC4 swig::ASSIGNMENT_DEFAULT
#define SWIGPOLICY_Cipher swig::ASSIGNMENT_DEFAULT

#ifdef __cplusplus
#include <utility>
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigSmartPointer {
    T *ptr;
    SwigSmartPointer(T *p) : ptr(p) { }
    ~SwigSmartPointer() { delete ptr; }
    SwigSmartPointer& operator=(SwigSmartPointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
    void reset(T *p) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = p; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigSmartPointer tmp(new T(t)); pointer = tmp; return *this; }
#if __cplusplus >=201103L
  SwigValueWrapper& operator=(T&& t) { SwigSmartPointer tmp(new T(std::move(t))); pointer = tmp; return *this; }
  operator T&&() const { return std::move(*pointer.ptr); }
#else
  operator T&() const { return *pointer.ptr; }
#endif
  T *operator&() const { return pointer.ptr; }
  static void reset(SwigValueWrapper& t, T *p) { t.pointer.reset(p); }
};

/*
 * SwigValueInit() is a generic initialisation solution as the following approach:
 * 
 *       T c_result = T();
 * 
 * doesn't compile for all types for example:
 * 
 *       unsigned int c_result = unsigned int();
 */
template <typename T> T SwigValueInit() {
  return T();
}

#if __cplusplus >=201103L
# define SWIG_STD_MOVE(OBJ) std::move(OBJ)
#else
# define SWIG_STD_MOVE(OBJ) OBJ
#endif

#endif


#include <stdexcept>


/* Support for the `contract` feature.
 *
 * Note that RETURNNULL is first because it's inserted via a 'Replaceall' in
 * the fortran.cxx file.
 */
#define SWIG_contract_assert(RETURNNULL, EXPR, MSG) \
 if (!(EXPR)) { SWIG_exception_impl("$decl", SWIG_ValueError, MSG, RETURNNULL); } 


#define SWIG_as_voidptr(a) const_cast< void * >(static_cast< const void * >(a)) 
#define SWIG_as_voidptrptr(a) ((void)SWIG_as_voidptr(*a),reinterpret_cast< void** >(a)) 


#include <string>


    /*#include "../../include/arithmetic/arith.hpp"
    */
    #include "../../include/number_theory/primes.hpp"
    #include "../../include/number_theory/rc4.hpp"
    #include "../../include/number_theory/cipher.hpp"


struct SwigClassWrapper {
    void* cptr;
    int cmemflags;
};


SWIGINTERN SwigClassWrapper SwigClassWrapper_uninitialized() {
    SwigClassWrapper result;
    result.cptr = NULL;
    result.cmemflags = 0;
    return result;
}


namespace swig {

template<class T, AssignmentType A>
struct DestructorPolicy {
  static SwigClassWrapper destroy(SwigClassWrapper self) {
    delete static_cast<T*>(self.cptr);
    return SwigClassWrapper_uninitialized();
  }
};
template<class T>
struct DestructorPolicy<T, ASSIGNMENT_NODESTRUCT> {
  static SwigClassWrapper destroy(SwigClassWrapper) {
    SWIG_exception_impl("assignment", SWIG_TypeError, "Invalid assignment: class type has private destructor", return SwigClassWrapper_uninitialized());
  }
};
}


namespace swig {

SWIGINTERN SwigClassWrapper capture(SwigClassWrapper other) {
  other.cmemflags &= ~SWIG_MEM_RVALUE;
  return other;
}

template<class T, AssignmentType A>
struct AssignmentPolicy {
  static SwigClassWrapper destroy(SwigClassWrapper self) {
    return DestructorPolicy<T, A>::destroy(self);
  }
  static SwigClassWrapper alias(SwigClassWrapper other) {
    SwigClassWrapper self = other;
    self.cmemflags &= ~SWIG_MEM_OWN;
    return self;
  }
  static SwigClassWrapper move_alias(SwigClassWrapper self, SwigClassWrapper other) {
    if (self.cmemflags & SWIG_MEM_OWN) {
      destroy(self);
    }
    return capture(other);
  }
  static SwigClassWrapper copy_alias(SwigClassWrapper self, SwigClassWrapper other) {
    if (self.cmemflags & SWIG_MEM_OWN) {
      destroy(self);
    }
    return capture(other);
  }
};

template<class T>
struct AssignmentPolicy<T, ASSIGNMENT_SMARTPTR> {
  static SwigClassWrapper destroy(SwigClassWrapper self) {
    return DestructorPolicy<T, ASSIGNMENT_SMARTPTR>::destroy(self);
  }
  static SwigClassWrapper alias(SwigClassWrapper other) {
    SwigClassWrapper self;
    self.cptr = new T(*static_cast<T*>(other.cptr));
    self.cmemflags = other.cmemflags | SWIG_MEM_OWN;
    return self;
  }
  static SwigClassWrapper move_alias(SwigClassWrapper self, SwigClassWrapper other) {
    self = copy_alias(self, other);
    self.cmemflags = other.cmemflags & ~SWIG_MEM_RVALUE;
    destroy(other);
    return self;
  }
  static SwigClassWrapper copy_alias(SwigClassWrapper self, SwigClassWrapper other) {
    // LHS and RHS should both 'own' their shared pointers
    T *pself = static_cast<T*>(self.cptr);
    T *pother = static_cast<T*>(other.cptr);
    *pself = *pother;
    return self;
  }
};

} // end namespace swig

template<class T, swig::AssignmentType A>
SWIGINTERN void SWIG_assign(SwigClassWrapper* self, SwigClassWrapper other) {
  typedef swig::AssignmentPolicy<T, A> Policy_t;

  if (self->cptr == NULL) {
    /* LHS is unassigned */
    if (other.cmemflags & SWIG_MEM_RVALUE) {
      /* Capture pointer from RHS, clear 'moving' flag */
      *self = swig::capture(other);
    } else {
      /* Aliasing another class; clear ownership or copy smart pointer */
      *self = Policy_t::alias(other);
    }
  } else if (other.cptr == NULL) {
    /* Replace LHS with a null pointer */
    *self = Policy_t::destroy(*self);
  } else if (self->cptr == other.cptr) {
    /* Self-assignment: ignore */
  } else if (other.cmemflags & SWIG_MEM_RVALUE) {
    /* Transferred ownership from a variable that's about to be lost.
     * Move-assign and delete the transient data */
    *self = Policy_t::move_alias(*self, other);
  } else {
    /* RHS shouldn't be deleted, alias to LHS */
    *self = Policy_t::copy_alias(*self, other);
  }
}

template<class T, swig::AssignmentType A>
SWIGINTERN void SWIG_free_rvalue(SwigClassWrapper other) {
  typedef swig::AssignmentPolicy<T, A> Policy_t;
  if (other.cmemflags & SWIG_MEM_RVALUE 
      && other.cmemflags & SWIG_MEM_OWN) {
    /* We own *and* are being passed an expiring value */
    Policy_t::destroy(other);
  }
}



#include <stdlib.h>
#ifdef _MSC_VER
# ifndef strtoull
#  define strtoull _strtoui64
# endif
# ifndef strtoll
#  define strtoll _strtoi64
# endif
#endif


struct SwigArrayWrapper {
    void* data;
    size_t size;
};


SWIGINTERN SwigArrayWrapper SwigArrayWrapper_uninitialized() {
  SwigArrayWrapper result;
  result.data = NULL;
  result.size = 0;
  return result;
}


#include <string.h>

extern "C" {
SWIGEXPORT int _wrap_Primality_is_prime(SwigClassWrapper *farg1, int const *farg2) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  bool result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::is_prime(int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  result = (bool)(arg1)->is_prime(arg2);
  fresult = (result ? 1 : 0);
  return fresult;
}


SWIGEXPORT int _wrap_Primality_compute_miller_rabin(SwigClassWrapper *farg1, int const *farg2, int const *farg3) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  int arg3 ;
  bool result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::compute_miller_rabin(int,int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  arg3 = (int)(*farg3);
  result = (bool)(arg1)->compute_miller_rabin(arg2,arg3);
  fresult = (result ? 1 : 0);
  return fresult;
}


SWIGEXPORT int _wrap_Primality_miller_rabin_prime(SwigClassWrapper *farg1, int const *farg2, int const *farg3) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  int arg3 ;
  bool result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::miller_rabin_prime(int,int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  arg3 = (int)(*farg3);
  result = (bool)(arg1)->miller_rabin_prime(arg2,arg3);
  fresult = (result ? 1 : 0);
  return fresult;
}


SWIGEXPORT void _wrap_Primality_miller_rabin(SwigClassWrapper *farg1, int const *farg2, int const *farg3, int const *farg4) {
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  int arg3 ;
  int arg4 ;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::miller_rabin(int,int,int)", return );
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  arg3 = (int)(*farg3);
  arg4 = (int)(*farg4);
  (arg1)->miller_rabin(arg2,arg3,arg4);
}


SWIGEXPORT int _wrap_Primality_jacobian_number(SwigClassWrapper *farg1, long long const *farg2, long long const *farg3) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  long long arg2 ;
  long long arg3 ;
  int result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::jacobian_number(long long,long long)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (long long)(*farg2);
  arg3 = (long long)(*farg3);
  result = (int)(arg1)->jacobian_number(arg2,arg3);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_Primality_solovoy_strassen(SwigClassWrapper *farg1, long long const *farg2, int const *farg3) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  long long arg2 ;
  int arg3 ;
  bool result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::solovoy_strassen(long long,int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (long long)(*farg2);
  arg3 = (int)(*farg3);
  result = (bool)(arg1)->solovoy_strassen(arg2,arg3);
  fresult = (result ? 1 : 0);
  return fresult;
}


SWIGEXPORT long long _wrap_Primality_mod_pow(SwigClassWrapper *farg1, long long const *farg2, long long const *farg3, long long const *farg4) {
  long long fresult ;
  Primality *arg1 = (Primality *) 0 ;
  long long arg2 ;
  long long arg3 ;
  long long arg4 ;
  long long result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::mod_pow(long long,long long,long long)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (long long)(*farg2);
  arg3 = (long long)(*farg3);
  arg4 = (long long)(*farg4);
  result = (long long)(arg1)->mod_pow(arg2,arg3,arg4);
  fresult = (long long)(result);
  return fresult;
}


SWIGEXPORT int _wrap_Primality_carmichael_num(SwigClassWrapper *farg1, int const *farg2) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  bool result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::carmichael_num(int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  result = (bool)(arg1)->carmichael_num(arg2);
  fresult = (result ? 1 : 0);
  return fresult;
}


SWIGEXPORT void _wrap_Primality_sieve_of_eratosthenes(SwigClassWrapper *farg1, int const *farg2) {
  Primality *arg1 = (Primality *) 0 ;
  int arg2 ;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::sieve_of_eratosthenes(int)", return );
  arg1 = (Primality *)farg1->cptr;
  arg2 = (int)(*farg2);
  (arg1)->sieve_of_eratosthenes(arg2);
}


SWIGEXPORT long long _wrap_Primality_pollard_rho(SwigClassWrapper *farg1, long long const *farg2) {
  long long fresult ;
  Primality *arg1 = (Primality *) 0 ;
  long long arg2 ;
  long long result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::pollard_rho(long long)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (long long)(*farg2);
  result = (long long)(arg1)->pollard_rho(arg2);
  fresult = (long long)(result);
  return fresult;
}


SWIGEXPORT int _wrap_Primality_ETF(SwigClassWrapper *farg1, int const *farg2) {
  int fresult ;
  Primality *arg1 = (Primality *) 0 ;
  unsigned int arg2 ;
  int result;
  
  SWIG_check_nonnull(farg1->cptr, "Primality *", "Primality", "Primality::ETF(unsigned int)", return 0);
  arg1 = (Primality *)farg1->cptr;
  arg2 = (unsigned int)(*farg2);
  result = (int)(arg1)->ETF(arg2);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_new_Primality() {
  SwigClassWrapper fresult ;
  Primality *result = 0 ;
  
  result = (Primality *)new Primality();
  fresult.cptr = (void*)result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (1 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT void _wrap_delete_Primality(SwigClassWrapper *farg1) {
  Primality *arg1 = (Primality *) 0 ;
  
  arg1 = (Primality *)farg1->cptr;
  delete arg1;
}


SWIGEXPORT void _wrap_Primality_op_assign__(SwigClassWrapper *farg1, SwigClassWrapper *farg2) {
  Primality *arg1 = (Primality *) 0 ;
  Primality *arg2 = 0 ;
  
  (void)sizeof(arg1);
  (void)sizeof(arg2);
  SWIG_assign<Primality, SWIGPOLICY_Primality>(farg1, *farg2);
  
}


SWIGEXPORT int _wrap_BITS_get() {
  int fresult ;
  int result;
  
  result = (int)(255);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT int _wrap_BYTE_LIMIT_get() {
  int fresult ;
  int result;
  
  result = (int)(256);
  fresult = (int)(result);
  return fresult;
}


SWIGEXPORT void _wrap_RC4_byte_swap(SwigClassWrapper *farg1, SwigClassWrapper *farg2, SwigClassWrapper *farg3) {
  RC4 *arg1 = (RC4 *) 0 ;
  uint8_t *arg2 = (uint8_t *) 0 ;
  uint8_t *arg3 = (uint8_t *) 0 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::byte_swap(uint8_t *,uint8_t *)", return );
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (uint8_t *)farg2->cptr;
  arg3 = (uint8_t *)farg3->cptr;
  (arg1)->byte_swap(arg2,arg3);
}


SWIGEXPORT void _wrap_RC4_trad_swap(SwigClassWrapper *farg1, SwigClassWrapper *farg2, SwigClassWrapper *farg3) {
  RC4 *arg1 = (RC4 *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::trad_swap(unsigned char *,unsigned char *)", return );
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (unsigned char *)farg2->cptr;
  arg3 = (unsigned char *)farg3->cptr;
  (arg1)->trad_swap(arg2,arg3);
}


SWIGEXPORT void _wrap_RC4_XOR_swap(SwigClassWrapper *farg1, SwigClassWrapper *farg2, SwigClassWrapper *farg3) {
  RC4 *arg1 = (RC4 *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::XOR_swap(unsigned char *,unsigned char *)", return );
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (unsigned char *)farg2->cptr;
  arg3 = (unsigned char *)farg3->cptr;
  (arg1)->XOR_swap(arg2,arg3);
}


SWIGEXPORT void _wrap_RC4_KSA(SwigClassWrapper *farg1, SwigArrayWrapper *farg2, SwigClassWrapper *farg3, int const *farg4) {
  RC4 *arg1 = (RC4 *) 0 ;
  char *arg2 = (char *) 0 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  int arg4 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::KSA(char *,unsigned char *,int)", return );
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (char *)(farg2->data);
  arg3 = (unsigned char *)farg3->cptr;
  arg4 = (int)(*farg4);
  (arg1)->KSA(arg2,arg3,arg4);
}


SWIGEXPORT void _wrap_RC4_PRGA(SwigClassWrapper *farg1, SwigClassWrapper *farg2, SwigArrayWrapper *farg3, SwigClassWrapper *farg4, int const *farg5) {
  RC4 *arg1 = (RC4 *) 0 ;
  unsigned char *arg2 = (unsigned char *) 0 ;
  char *arg3 = (char *) 0 ;
  unsigned char *arg4 = (unsigned char *) 0 ;
  int arg5 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::PRGA(unsigned char *,char *,unsigned char *,int)", return );
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (unsigned char *)farg2->cptr;
  arg3 = (char *)(farg3->data);
  arg4 = (unsigned char *)farg4->cptr;
  arg5 = (int)(*farg5);
  (arg1)->PRGA(arg2,arg3,arg4,arg5);
}


SWIGEXPORT SwigArrayWrapper _wrap_RC4_store_hash(SwigClassWrapper *farg1, SwigArrayWrapper *farg2, SwigClassWrapper *farg3, int const *farg4) {
  SwigArrayWrapper fresult ;
  RC4 *arg1 = (RC4 *) 0 ;
  char *arg2 = (char *) 0 ;
  unsigned char *arg3 = (unsigned char *) 0 ;
  int arg4 ;
  std::string result;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::store_hash(char *,unsigned char *,int)", return SwigArrayWrapper_uninitialized());
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (char *)(farg2->data);
  arg3 = (unsigned char *)farg3->cptr;
  arg4 = (int)(*farg4);
  result = (arg1)->store_hash(arg2,arg3,arg4);
  fresult.size = (&result)->size();
  if (fresult.size > 0) {
    fresult.data = malloc(fresult.size);
    memcpy(fresult.data, (&result)->c_str(), fresult.size);
  } else {
    fresult.data = NULL;
  }
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_RC4_compute(SwigClassWrapper *farg1, SwigArrayWrapper *farg2, SwigArrayWrapper *farg3, SwigClassWrapper *farg4, int const *farg5) {
  SwigClassWrapper fresult ;
  RC4 *arg1 = (RC4 *) 0 ;
  char *arg2 = (char *) 0 ;
  char *arg3 = (char *) 0 ;
  unsigned char *arg4 = (unsigned char *) 0 ;
  int arg5 ;
  unsigned char *result = 0 ;
  
  SWIG_check_nonnull(farg1->cptr, "RC4 *", "RC4", "RC4::compute(char *,char *,unsigned char *,int)", return SwigClassWrapper_uninitialized());
  arg1 = (RC4 *)farg1->cptr;
  arg2 = (char *)(farg2->data);
  arg3 = (char *)(farg3->data);
  arg4 = (unsigned char *)farg4->cptr;
  arg5 = (int)(*farg5);
  result = (unsigned char *)(arg1)->compute(arg2,arg3,arg4,arg5);
  fresult.cptr = (void*)result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (0 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_new_RC4() {
  SwigClassWrapper fresult ;
  RC4 *result = 0 ;
  
  result = (RC4 *)new RC4();
  fresult.cptr = (void*)result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (1 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT void _wrap_delete_RC4(SwigClassWrapper *farg1) {
  RC4 *arg1 = (RC4 *) 0 ;
  
  arg1 = (RC4 *)farg1->cptr;
  delete arg1;
}


SWIGEXPORT void _wrap_RC4_op_assign__(SwigClassWrapper *farg1, SwigClassWrapper *farg2) {
  RC4 *arg1 = (RC4 *) 0 ;
  RC4 *arg2 = 0 ;
  
  (void)sizeof(arg1);
  (void)sizeof(arg2);
  SWIG_assign<RC4, SWIGPOLICY_RC4>(farg1, *farg2);
  
}


SWIGEXPORT SwigArrayWrapper _wrap_Cipher_C_cipher(SwigClassWrapper *farg1, SwigArrayWrapper *farg2, int const *farg3) {
  SwigArrayWrapper fresult ;
  Cipher *arg1 = (Cipher *) 0 ;
  std::string arg2 ;
  int arg3 ;
  std::string result;
  
  SWIG_check_nonnull(farg1->cptr, "Cipher *", "Cipher", "Cipher::C_cipher(std::string,int)", return SwigArrayWrapper_uninitialized());
  arg1 = (Cipher *)farg1->cptr;
  (&arg2)->assign(static_cast<char *>(farg2->data), farg2->size);
  arg3 = (int)(*farg3);
  result = (arg1)->C_cipher(arg2,arg3);
  fresult.size = (&result)->size();
  if (fresult.size > 0) {
    fresult.data = malloc(fresult.size);
    memcpy(fresult.data, (&result)->c_str(), fresult.size);
  } else {
    fresult.data = NULL;
  }
  return fresult;
}


SWIGEXPORT SwigArrayWrapper _wrap_Cipher_KC_encode(SwigClassWrapper *farg1, SwigArrayWrapper *farg2) {
  SwigArrayWrapper fresult ;
  Cipher *arg1 = (Cipher *) 0 ;
  std::string arg2 ;
  std::string result;
  
  SWIG_check_nonnull(farg1->cptr, "Cipher *", "Cipher", "Cipher::KC_encode(std::string)", return SwigArrayWrapper_uninitialized());
  arg1 = (Cipher *)farg1->cptr;
  (&arg2)->assign(static_cast<char *>(farg2->data), farg2->size);
  result = (arg1)->KC_encode(arg2);
  fresult.size = (&result)->size();
  if (fresult.size > 0) {
    fresult.data = malloc(fresult.size);
    memcpy(fresult.data, (&result)->c_str(), fresult.size);
  } else {
    fresult.data = NULL;
  }
  return fresult;
}


SWIGEXPORT SwigArrayWrapper _wrap_Cipher_KC_cipher(SwigClassWrapper *farg1, SwigArrayWrapper *farg2, SwigArrayWrapper *farg3) {
  SwigArrayWrapper fresult ;
  Cipher *arg1 = (Cipher *) 0 ;
  std::string arg2 ;
  std::string arg3 ;
  std::string result;
  
  SWIG_check_nonnull(farg1->cptr, "Cipher *", "Cipher", "Cipher::KC_cipher(std::string,std::string)", return SwigArrayWrapper_uninitialized());
  arg1 = (Cipher *)farg1->cptr;
  (&arg2)->assign(static_cast<char *>(farg2->data), farg2->size);
  (&arg3)->assign(static_cast<char *>(farg3->data), farg3->size);
  result = (arg1)->KC_cipher(arg2,arg3);
  fresult.size = (&result)->size();
  if (fresult.size > 0) {
    fresult.data = malloc(fresult.size);
    memcpy(fresult.data, (&result)->c_str(), fresult.size);
  } else {
    fresult.data = NULL;
  }
  return fresult;
}


SWIGEXPORT SwigClassWrapper _wrap_new_Cipher() {
  SwigClassWrapper fresult ;
  Cipher *result = 0 ;
  
  result = (Cipher *)new Cipher();
  fresult.cptr = (void*)result;
  fresult.cmemflags = SWIG_MEM_RVALUE | (1 ? SWIG_MEM_OWN : 0);
  return fresult;
}


SWIGEXPORT void _wrap_delete_Cipher(SwigClassWrapper *farg1) {
  Cipher *arg1 = (Cipher *) 0 ;
  
  arg1 = (Cipher *)farg1->cptr;
  delete arg1;
}


SWIGEXPORT void _wrap_Cipher_op_assign__(SwigClassWrapper *farg1, SwigClassWrapper *farg2) {
  Cipher *arg1 = (Cipher *) 0 ;
  Cipher *arg2 = 0 ;
  
  (void)sizeof(arg1);
  (void)sizeof(arg2);
  SWIG_assign<Cipher, SWIGPOLICY_Cipher>(farg1, *farg2);
  
}


} // extern

