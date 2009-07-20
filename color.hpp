#ifndef EB_COLOR_HPP
# define EB_COLOR_HPP
namespace eb {
struct color {
  color(double r,
        double g,
        double b,
        double a = 1)
   :r(r),g(g),b(b), a(a){}
  double r;
  double g;
  double b;
  double a;
};
}
#endif
    
