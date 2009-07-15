#ifndef EB_GEOMETRY_HPP
# define EB_GEOMETRY_HPP
namespace eb {

  typedef float angle;

  struct vector {
    float x, y, z;

    void test() const {}
    
    vector(double x, double y, double z = 0)
     : x(x),y(y),z(z) { test() }
    vector& operator *=(double rhs) {
      x *= rhs;
      y *= rhs;
      z *= rhs;
      test();
      return *this;
    }
    
    friend
    vector operator *(vector lhs, double rhs) {
      return lhs *= rhs;
    } 
    friend
    double norm_2(vector v) {
      v.test();
      return std::sqrt(v.x*v.x + 
		       v.y*v.y + 
		       v.z*v.z);
    } 
  };

  struct point {
    double x, y, z;

    void test();
    
    point(double x, double y, double z = 0) 
      :x(x), y(y), z(z) { test(); }

    point& operator +=(vector rhs) {
      x+=rhs.x;
      y+=rhs.y;
      z+=rhs.z;
      test();
      return *this;
    }

    point& operator -=(vector rhs) {
      x-=rhs.x;
      y-=rhs.y;
      z-=rhs.z;
      test();
      return *this;
    }

    friend
    vector operator-(point lhs, point rhs) {
      lhs.test();
      rhs.test();
      vector r (lhs.x-rhs.x,
		lhs.y-rhs.y,
		lhs.z-rhs.z);
      return r;
    }

    friend point operator+(point lhs, vector rhs) {
      point r(lhs);
      r+=rhs;
      return r;
    }
  };

  vector
  make_unit_vector(angle rho, angle tau) {
    vector r ( std::sin(rho) * std::cos(tau),
	       std::sin(rho) * std::sin(tau),
	       std::cos(rho) );
    return r;
  } 


}
#endif 
