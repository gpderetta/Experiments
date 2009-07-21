#ifndef EB_GEOMETRY_HPP
# define EB_GEOMETRY_HPP
# include <cmath>
# include <iostream>
# include <cstring>
namespace eb {

typedef float real;
typedef real angle;


inline
float __attribute__((pure))  inv_sqrt(float x) {
  float xhalf = 0.5f * x;
  int i;
  std::memcpy((char*)&i, (char*)&x, sizeof(x));
  i = 0x5f3759df - (i >> 1);
  std::memcpy((char*)&x, (char*)&i, sizeof(x));
  x = x*(1.5f - xhalf*x*x);
//  x = x*(1.5f - xhalf*x*x);
//  x = x*(1.5f - xhalf*x*x);
  return x;
}

struct point;
struct vector {
  real x, y, z;

  void test() const {}

  vector() : x(0), y(0), z(0) {}
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

  vector& operator -() {
    x = -x;
    y = -y;
    z = -z;
    test();
    return *this;
  }

  friend std::ostream&operator<<(std::ostream&o, vector v) {
    return o << "("<<v.x<<", "<<v.y<<")";
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
  vector versor(vector v) {
# ifdef EB_SLOW
    return v /= norm_2(v);
# else
    return v *= inv_sqrt(inner_prod(v));
# endif 
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
  vector rotate(vector v, float angle) {
    return vector(v.x*cos(angle)-v.y*sin(angle),
                  v.x*sin(angle)+v.y*cos(angle));
  }
  
  friend
  // return inner_prod with itself
  real inner_prod(vector v) {
    return inner_prod(v,v);
  }

  
  friend real atan2(vector v){
    return atan2(v.y, v.x);
  }

};


struct point {
  real x, y, z;

  friend std::ostream&operator<<(std::ostream&o, point v) {
    return o << "("<<v.x<<", "<<v.y<<")";
  }

  
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
