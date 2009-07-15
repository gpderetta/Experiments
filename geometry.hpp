#ifndef EB_GEOMETRY_HPP
# define EB_GEOMETRY_HPP
namespace eb {

    template<typename Value, int Dim, typename Tag>
    class array {        
        typedef Value value_type;
        value_type v[Dim];
    };

    struct univ;
    typedef array<float, 2, univ> v2f;
    typedef array<float, 2, univ> p2f;
    typedef array<float, 2, univ> a2f;
    
    template<typename Tag, typename T>
    array<T, 2, Tag>
    make(T x, T y) {
        array<T, 2, Tag> r = {x,y};
        return r;
    }

    template<typename Tag, typename T>
    array<T, 3, Tag>
    make(T x, T y, T z) {
        array<T, 3, Tag> r = {x,y,z};
        return r;
    }


    
}
#endif 
