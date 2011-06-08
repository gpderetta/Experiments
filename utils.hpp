#ifndef GPD_UTILS_HPP
#define GPD_UTILS_HPP
#include <utility>
namespace gpd {
template<typename T>
T square(T x) { return x*x; }

real absclamp(real x, real min, real max) {
    return x >= 0
        ? std::min(std::max(x, min), max)
        : std::max(std::min(x,-min),-max)
        ;
}

template<class T>
T absclamp(T val, real min, real max) {
    real norm = norm_2(val);
    real scaled_norm = absclamp(norm, min, max);
    return val * (scaled_norm / norm) ;
}

}
#endif
