#ifndef GPD_ATOMICS_HPP
#define GPD_ATOMICS_HPP
namespace gpd {
/*
 * Why this file? GCC 4.6 <atomic> implementation is currently
 * suboptimal (too strongly locked) and we currently need minimal
 * functionality anyway, so this class should in the meantime work for compatiblity;
 *
 * Note: x86-64 only
 */

namespace details {
/* Returns nonzero if the comparison succeeded. */

template<class T>
typename std::enable_if<sizeof(T)==sizeof(long long), bool>::type
cas(volatile T *addr,
         T& old, T new_)
{
  char result;
  asm volatile("lock; cmpxchgq %4, %0; setz %1"
               : "=m"(*addr), "=q"(result), "+a"(old)
               : "m"(*addr), "r" (new_)  : "memory");
  if(!(result == 1 || result == 0))
      __builtin_unreachable();
  return (bool) result;
}

template<class T>
typename std::enable_if<sizeof(T)==sizeof(int), bool>::type
cas(volatile T *addr,
         T& old, T new_)
{
  char result;
  asm volatile("lock; cmpxchgl %4, %0; setz %1"
               : "=m"(*addr), "=q"(result), "+a"(old)
               : "m"(*addr), "r" (new_)  : "memory");
  if(!(result == 1 || result == 0))
      __builtin_unreachable();
  return (bool) result;
}

template<class T>
typename std::enable_if<sizeof(T)==sizeof(short), bool>::type
cas(volatile T *addr,
         T& old, T new_)
{
  char result;
  asm volatile("lock; cmpxchgw %4, %0; setz %1"
               : "=m"(*addr), "=q"(result), "+a"(old)
               : "m"(*addr), "r" (new_)  : "memory");
  if(!(result == 1 || result == 0))
      __builtin_unreachable();
  return (bool) result;
}

template<class T>
typename std::enable_if<sizeof(T)==sizeof(short), T>::type
cas(volatile T *addr,
         T& old, T new_)
{
  char result;
  asm volatile("lock; cmpxchgb %4, %0; setz %1"
               : "=m"(*addr), "=q"(result), "+a"(old)
               : "m"(*addr), "r" (new_)  : "memory");
  if(!(result == 1 || result == 0))
      __builtin_unreachable();
  return (bool) result;
}
             
bool dwcas(volatile void *addr,
     long long old_val1, long long old_val2,
     long long new_val1, long long new_val2)
{
  char result;
  asm volatile("lock; cmpxchg16b %0; setz %1"
               : "=m"(*(volatile long long*)addr), "=q"(result)
               : "m"(*(volatile long long*)addr),
                 "d" (old_val2),
                 "a" (old_val1),
                 "c" (new_val2),
                 "b" (new_val1)  : "memory");
  return (int) result;
}

template<class T>
typename std::enable_if<sizeof(T) == sizeof(char), T>::type
xchg(T x, volatile T *ptr)
{
    asm volatile("xchgb %b0,%1"
                 : "=q" (x)
                 : "m" (*ptr), "0" (x)
                 : "memory");
    return x;

}

template<class T>
typename std::enable_if<sizeof(T) == sizeof(short), T>::type 
xchg(T x, volatile T *ptr)
{   
    asm volatile("xchgw %w0,%1"
                 : "=r" (x)
                 : "m" (*ptr), "0" (x)
                 : "memory");
    return x;
}

template<class T>
typename std::enable_if<sizeof(T) == sizeof(int), T>::type
xchg(T x, volatile T *ptr)
{
    asm volatile("xchgl %k0,%1"
                 : "=r" (x)
                 : "m" (*ptr), "0" (x)
                 : "memory");
    return x;
}
template<class T>
typename std::enable_if<sizeof(T) == sizeof(long long), T>::type
xchg(T x, volatile T *ptr)
{
    asm volatile("xchgq %0,%1"
                 : "=r" (x)
                 : "m" (*ptr), "0" (x)
                 : "memory");
    return x;
}
}
enum memory_order {
    memory_order_relaxed,
    memory_order_consume,
    memory_order_acquire,
    memory_order_release,
    memory_order_acq_rel,
    memory_order_seq_cst
};

void atomic_signal_fence() {
    asm volatile("":::"memory");
}

void atomic_thread_fence() {
    __sync_synchronize();
}

template<class T>
struct atomic {
    constexpr atomic(T x) : val(x) {}
    
    operator T () const { return load(); } 

    T operator=(T rhs) { 
        store(rhs); 
        return rhs;
    }

    atomic() = default;
    atomic(const atomic&) = delete;
    atomic& operator=(const atomic&) = delete;

    void store(T x,  memory_order o = memory_order_seq_cst) {
        switch(o) {
        case memory_order_relaxed:
            val = x;
            return;
        case memory_order_release:
            atomic_signal_fence();
            val = x;
            break;
        case memory_order_seq_cst:
        default:
            exchange(x); break;
        }
    }

    T load( memory_order o = memory_order_seq_cst) const {
        switch(o) {
        case memory_order_relaxed:
            return val;
        case memory_order_acquire:
        {
            T ret = val;
            atomic_signal_fence();
            return ret;
        }
        case memory_order_seq_cst:
        default:
        {
            atomic_thread_fence();
            T ret = val;
            atomic_thread_fence();
            return ret;
        }
        }
    }

    T exchange(T x, memory_order = memory_order_seq_cst) {
        auto ret = details::xchg(x, &val);
        return ret;
    }

    bool compare_exchange_strong(T & old, T new_,
                                 memory_order = memory_order_seq_cst) {
        return details::cas(&val, old, new_);
    }
        
    volatile T val;
};

// store hoist barrier
// #loadstore | #storestore
// prevent prior operations to be ordered after this op
template<class T>
void store_release(atomic<T*>& x, T* value) {
    x.store(value, memory_order_release);
}

// load sink barrier
// #loadload | #loadstore
// prevent subsequent operations of being reordered before this load
template<class T>
T load_acquire(const atomic<T>& x) {
    return x.load(memory_order_acquire);
}

}
#endif
