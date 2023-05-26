#ifndef PRIME_GEN_HPP
#define PRIME_GEN_HPP
#include <cstdint>

namespace mtpk {

class PrimalityGen {
  public:
    void sieve_of_eratosthenes(uint64_t n);
};

} // namespace mtpk

#endif
