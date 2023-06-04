#ifndef EUCLIDEAN_DIV_HPP
#define EUCLIDEAN_DIV_HPP
#include <cstdint>

namespace gpmp {

/*
 * @class EuclideanDivision
 * @brief Euclidean Division algorithms also known as division with
 * remainder
 */
class EuclideanDivision {
  public:
    void binary(uint64_t n);
    void chunking();
    void fourier();
    void goldschmidt();
    void newton_raphson();
    void SRT();
};

} // namespace gpmp

#endif
