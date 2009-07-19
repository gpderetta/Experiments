// Copyright Giovanni P. Deretta 2009. Use, modification and
// distribution is subject to the Boost Software License, Version
// 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)
#ifndef GL_GPD2009715_H
# define GL_GPD2009715_H
#include "color.hpp"
#include "geometry.hpp"
#include <string>
#include <boost/noncopyable.hpp>
namespace eb {
namespace gl {

struct texture { unsigned int id;};

struct graphic_context : boost::noncopyable {
  graphic_context();
  void resize_window(int, int);
  void reset();
  void swap_buffers();
  ~graphic_context();
  texture load_textures(const std::string& =
                       "data/particle.bmp");
  void bind_texture(texture const&) const;
//private:
  texture tex;
};



void draw_dot(const graphic_context&,
              const point p, 
              const color c = color(1,1,1),
              const float alpha = 1.f,
              const float radius = 10.f);

}}
#endif // GL_GPD2009715_H

