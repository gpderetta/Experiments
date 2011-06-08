#include "switch.hpp"
#include "boid.hpp"
#include <vector>
#include <algorithm>
#include <iterators>
namespace gpd {

typedef continuation<> actor;

class world {
    scheduler & sched;

    void init() {
        sched.spawh
            (callcc
             ([&](actor scheduler)
              {
                  
              }));
                          
    }

};


}
