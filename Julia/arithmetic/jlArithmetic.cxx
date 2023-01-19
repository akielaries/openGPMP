#include <type_traits>
#include "jlcxx/jlcxx.hpp"
#include "jlcxx/functions.hpp"
#include "jlcxx/stl.hpp"

#include "jlArithmetic.h"

#ifdef VERBOSE_IMPORT
#  define DEBUG_MSG(a) std::cerr << a << "\n"
#else
#  define DEBUG_MSG(a)
#endif
#define __HERE__  __FILE__ ":" QUOTE2(__LINE__)
#define QUOTE(arg) #arg
#define QUOTE2(arg) QUOTE(arg)

namespace jlcxx {
  template<> struct IsMirroredType<mtpk::Basics> : std::false_type { };
}

JLCXX_MODULE define_julia_module(jlcxx::Module& types){

  DEBUG_MSG("Adding wrapper for type mtpk::Basics (" __HERE__ ")");
  // defined in ./../../include/arithmetic/arith_ops.hpp:21:7
  auto t0 = types.add_type<mtpk::Basics>("mtpk!Basics");

  /**********************************************************************
   * Wrappers for typedefs
   */

  /* End of typedefs wrappers
   **********************************************************************/


  /**********************************************************************/
  /* Wrappers for the methods of class mtpk::Basics
   */

  DEBUG_MSG("Adding wrapper for int64_t mtpk::Basics::greatest_power(int64_t, int64_t) (" __HERE__ ")");
  // signature to use in the veto list: int64_t mtpk::Basics::greatest_power(int64_t, int64_t)
  // defined in ./../../include/arithmetic/arith_ops.hpp:32:17
  t0.method("greatest_power", static_cast<int64_t (mtpk::Basics::*)(int64_t, int64_t) >(&mtpk::Basics::greatest_power));

  DEBUG_MSG("Adding wrapper for int64_t mtpk::Basics::op_gcd(int64_t, int64_t) (" __HERE__ ")");
  // signature to use in the veto list: int64_t mtpk::Basics::op_gcd(int64_t, int64_t)
  // defined in ./../../include/arithmetic/arith_ops.hpp:42:17
  t0.method("op_gcd", static_cast<int64_t (mtpk::Basics::*)(int64_t, int64_t) >(&mtpk::Basics::op_gcd));

  /* End of mtpk::Basics class method wrappers
   **********************************************************************/

  DEBUG_MSG("End of wrapper definitions");

}
