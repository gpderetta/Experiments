#ifndef GPD_SPRING_HPP
#define GPD_SPRING_HPP
namespace gpd {
struct spring_arm {
    spring_arm(int a, int b,
               real len,
               real k,
               real c) 
        : a_index(a)
        , b_index(b)
        , arm_len(len)
        , spring_constant(k)
        , damp_factor(c) {}
    int a_index;
    int b_index;
    real arm_len;  
    real spring_constant;
    real damp_factor;
};
}
#endif
