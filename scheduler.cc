#include "scheduler.hpp"
#include <vector>
#include <algorithm>
#include <iterators>
#include <thread>
namespace gpd {

class scheduler_impl : scheduler  {


    void run()  {
        update_actors();
        run_workers();
    }

    void spawn(actor x) {
    }


    struct task : node {
        continuation<task*(task*)> m_cont;
    };

    struct interrupt : node {
        virtual void run() = 0;
    };

    struct worker {
        std::thread m_thread;
        mpsc_queue<interrupt> m_attention;
        std::deqeue<task*> m_ready;
        std::mutex m_spill_mutex;
        std::deqeue<task*> m_actors_spill;      
        futex m_futex;
        
        operator()() {
            XASSERT(scheduler_impl::this_worker == 0);
        }


        void steal() {
            struct stealer : interrupt {
                
            };
        }

        void pump_signals() {
            while(auto *n = m_attention.pop())
                (*n);
        }

        void do_yield() {
            XASSERT(!m_read.empty());
            task * n = m_ready.front();
            m_ready.pop_front();
            m_cont(); // context switch
            // auto from = this_task;
            // this_task = this;
            
        }
    
        struct idle : task {
            void run(task * previous) {
                auto self = this;
                swap(current_task, self);
                XASSERT(scheduler_impl::this_worker == 0);
                scheduler_impl::this_worker = this;
                while(true) {
                    node * n = 0;
                    auto v = m_futex.load();
                    while(m_ready.empty()) {
                        m_futex.wait(v);
                        check_attention();
                    }
                }
            }
        }
    };

    static __thread this_worker * = 0;
    static __thread current_task   * = 0;

    const std::vector<worker> m_threads;
};

template<class T>
struct thread_specific

scheduler & scheduler::instance() {
    scheduler_impl sched;
    return sched;
}

}
