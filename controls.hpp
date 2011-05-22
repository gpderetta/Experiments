#ifndef EB_CONTROLS_HPP
#define EB_CONTROLS_HPP
#include "geometry.hpp"
#include <array>
namespace eb {

void init_input();
void update_input();
point get_mouse();

std::array<int, 3> get_mouse_buttons();
}
#endif
