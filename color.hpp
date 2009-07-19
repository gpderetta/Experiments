#ifndef EB_COLOR_HPP
# define EB_COLOR_HPP
namespace eb {
struct color {
  color(double r,
        double g,
        double b)
   :r(r),g(g),b(b){}
  double r;
  double g;
  double b;
};
}
#endif
    
