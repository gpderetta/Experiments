#ifndef GPD_BOID_HPP
#define GPD_BOID_HPP
#include "geometry.hpp"
#include "color.hpp"
namespage gpd {

static const int  num_charges = 3;
typedef std::array<real, num_charges> charges_t;

struct boid {
    boid(point position,
         vector velocity,
         color c, float mass, charges_t const& charges)
        : m_life(0)
        , m_color(c)
        , m_mass(mass)   
        , m_charges(charges)
        , m_position(position)
        , m_old_force()
        , m_force()
        , m_velocity(velocity)
    {   }

    real m_life;
    color m_color;
    real m_mass;
    charges_t m_charges;
    point m_position;
    vector m_old_force;
    vector m_force;
    vector m_velocity;
};
}
#endif
