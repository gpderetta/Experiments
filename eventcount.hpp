#ifndef GPD_EVENTCOUNT_HPP
#define GPD_EVENTCOUNT_HPP
#include "atomic.hpp"
#include "futex.hpp"
namespace gpd {

/**
 * Very Simple futex-based eventcount implementation . 
 *
 * The signal path is probablyn ot particularly efficient.
 *
 * TODO: add for fetch_{add,and,or,etc...} to
 * atomic<> and use them instead of CAS
 */
struct eventcount
{
    // generation count; lsb is the waiters pending bit
	futex value;

    // sequentially consistent
    T getkey() {
        return value | 1;
    }


    void broadcast() {
        auto v = value.load(memory_order_acquire);
        while(value.compare_exchange_strong(v, v+2))
            ;

        if (v & 1) {
            while(value.compare_exchange_strong(v, v&~1))
                ;
            value.signal();
        }
    }

    void signal() {
        auto v = value.load(memory_order_acquire);
        while(value.compare_exchange_strong(v, v+2))
            ;

        if (v & 1) {
            while(value.compare_exchange_strong(v, v&~1))
                ;
            value.signal(1);
        }
        return;
    }

    void wait(unsigned int key)
    {
        while (key == value.load(memory_order_acquire) | 1)  {
            // set wait bit
            while(value.compare_exchange_strong(v, v | 1))
                ;
            v = value.load(memory_order_acquire) | 1;
            
            if (v != key) return;
            value.wait();
        }
    }
};
}
#endif
