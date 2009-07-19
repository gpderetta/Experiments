#ifndef EB_GEOMETRY_HPP
# define EB_GEOMETRY_HPP
# include <cmath>
namespace eb {

typedef float real;
typedef real angle;

struct point;
struct vector {
  real x, y, z;

  void test() const {}
    
  vector(real x, real y, real z = 0)
   : x(x),y(y),z(z) { test(); }
  vector& operator *=(real rhs) {
    x *= rhs;
    y *= rhs;
    z *= rhs;
    test();
    return *this;
  }

  explicit vector(point p);
    
  
  friend
  vector operator *(vector lhs, real rhs) {
    return lhs *= rhs;
  } 

  vector& operator /=(real rhs) {
    x /= rhs;
    y /= rhs;
    z /= rhs;
    test();
    return *this;
  }

  friend
  vector operator -(vector lhs, vector rhs) {
    return lhs -= rhs;
  } 

  vector& operator -=(vector rhs) {
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    test();
    return *this;
  }

  friend
  vector operator +(vector lhs, vector rhs) {
    return lhs += rhs;
  } 

  vector& operator +=(vector rhs) {
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    test();
    return *this;
  }
  
  friend
  vector operator /(vector lhs, real rhs) {
    return lhs /= rhs;
  } 

  friend
  real norm_2(vector v) {
    return std::sqrt(inner_prod(v,v));
  }

  friend
  real inner_prod(vector lhs, vector rhs) {
    lhs.test();
    rhs.test();
    return (lhs.x*rhs.x + 
            lhs.y*rhs.y + 
            lhs.z*rhs.z);
  }

  friend
  // return inner_prod with itself
  real inner_prod(vector v) {
    return inner_prod(v,v);
  }

  
  friend real atan2(vector v){
    return atan2(v.x, v.y);
  }

};

struct point {
  real x, y, z;

  void test(){}
    
  point(real x, real y, real z = 0) 
   :x(x), y(y), z(z) { test(); }

  point& operator +=(vector rhs) {
    x+=rhs.x;
    y+=rhs.y;
    z+=rhs.z;
    test();
    return *this;
  }

  point& operator *=(vector rhs) {
    x*=rhs.x;
    y*=rhs.y;
    z*=rhs.z;
    test();
    return *this;
  }

  template<typename T>
  point& operator -=(T rhs) {
    x-=rhs.x;
    y-=rhs.y;
    z-=rhs.z;
    test();
    return *this;
  }

  friend
  vector operator-(point lhs, point rhs) {
    return vector(lhs-=rhs);
  }

  friend point operator+(point lhs, vector rhs) {
    return lhs+=rhs;
  }
  friend point operator*(point lhs, vector rhs) {
    return lhs*=rhs;
  }

};

inline vector::vector(point p) :x(p.x), y(p.y), z(p.z) {}

inline
vector
make_unit_vector(angle rho, angle tau) {
  vector r ( std::sin(rho) * std::cos(tau),
             std::sin(rho) * std::sin(tau),
             std::cos(rho) );
  return r;
} 


}
#endif 
