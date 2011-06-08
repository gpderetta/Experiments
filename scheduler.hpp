#ifndef GPD_SCHEDULER_HPP
#define GPD_SCHEDULER_HPP
#include "switch.hpp"
#include "queue.hpp"
namespace gpd {




class scheduler {

    static scheduler& instance();
    
    template<class T>
    void launch(F f);

    virtual void
private:
    virtual void run() = 0;
    virtual void spawn(actor_impl) = 0;
    
};

class actor : node_base {
    friend class scheduler;
    actor(actor c, scheduler& sched) : c(std::move(c)), m_sched(sched) {}

    actor(const sched&) = delete;
    void operator=(const sched&) = delete;

    typedef continuation<> actor_impl;

    actor_impl m_coni;
    scheduler& m_sched
public:
    template<class T>
    void launch(F f) {
        m_sched.launch(std::move(f));
    }

    void yield() {
        m_sched.yeld(c);
    }
};

template<class T>
void scheduler::launch(F f) {
    struct  {
        F f;
        scheduler& sched;
        actor_impl operator(actor_impl c) {
            actor self(std::move(c), sched);
            f(self);
            return std::move(self.c);
        } 
    } wrapper = { std::move(c), scheduler() };
    spawn(callcc(std::move(wrapper)));
}


}
#endif
