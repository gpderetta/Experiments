// Copyright Giovanni P. Deretta 2009. Use, modification and distribution is
// subject to the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#ifndef SWARM_GPD2009717_HPP
# define SWARM_GPD2009717_HPP
# include "gl.hpp"
# include <boost/noncopyable.hpp>

namespace eb { namespace swarm {
typedef gl::graphic_context world;
struct state_impl;
struct state : boost::noncopyable{
  state(int width, int height);
  ~state();
  unsigned long update(world&);
private:
  state_impl* pimpl;
};
}} // namespace eb::swarm

#endif // SWARM_GPD2009717_HPP
