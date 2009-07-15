#ifndef EB_PARTICLE_HPP
# define EB_PARTICLE_HPP
# include "geometry.hpp"
namespace eb {

    /* Create our particle structure */
    struct particle {
        size_t life; 
        color col;
        point   position;
        vector  speed;

        friend float mass(particle const&) {
            return 1.0;
        }
        
        particle(color col, point pos,
                 vector dir) 
            : col(col), position(pos), speed(dir)
        {}

    };


}
#endif 
