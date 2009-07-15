#ifndef EB_PHISICS_HPP
# define EB_PHISICS_HPP
# include "geomtery.hpp"
namespace eb {
    template<class T>
    float& position(T& x) {
        return x.position;
    }

    template<class T>
    float position(const T& x) {
        return x.position;
    }

    template<class T>
    float& speed(T& x) {
        return x.speed;
    }

    template<class T>
    float speed(const T& x) {
        return x.speed;
    }

    template<typename T>
    void update_position(T& x) {
        position(x) += speed(x);
    }

    template<typename T, typename Force>
    void apply_force(T& x, Force f) {
        accelleration accel = force * Force::mass(x);
        speed(x) += accel;
    }

    template<typename T, typename Source>
    typename Source::force_type
    compute_interaction(T&x, Source const& s) {
        typedef typename Source::force_type force_type;
        force_type ret =
            force_type::charge(s) * (position(x)-position(s))/
            std::pow(distance(x, s),3);
    }

    template<typename T1, typename T2>
    float distance(T1 const& lhs, T2 const& rhs) {
        return norm_2(position(lhs) - position(rhs)); 
    }

}
#endif 
