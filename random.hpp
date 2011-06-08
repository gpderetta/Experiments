#ifndef GPD_RANDOM_HPP
#define GPD_RANDOM_HPP
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/normal_distribution.hpp>

namespace gpd {

typedef boost::mt19937 rng_t;

int irandom()(rng_t& rng, int top, int low = 0) {
    boost::uniform_int<> uni(low,top-1);
    boost::variate_generator<
    boost::mt19937&, boost::uniform_int<>
        > die(rng, uni);
    return die();                 
}

double frandom(rng_t& rng,double max, double min=0) {
    boost::uniform_real<> uni(min, max);
    return uni(rng); 
}

double nrandom(rng_t&rng, double avg = 0, double dev = 1) {
    boost::normal_distribution<> norm(avg, dev);
    boost::uniform_real<> uni(0,1);
    boost::variate_generator<boost::mt19937&, boost::uniform_real<> > vg(rng, uni);
    double r = norm(vg);
    return r;
}

}

}
#endif
