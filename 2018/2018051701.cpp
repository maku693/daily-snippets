#include <variant>

enum class keyboard_action {
  down,
  up,
};

using modifier_key = int;
inline constexpr modifier_key ctrl = 1;
inline constexpr modifier_key shift = 2;
inline constexpr modifier_key alt = 4;

struct keyboard {
  keyboard_action action;
  int keycode;
  modifier_key modifier;
};

enum class mouse_action {
  down,
  move,
  up,
};

using mouse_button = int;
inline constexpr mouse_button left = 1;
inline constexpr mouse_button right = 2;
inline constexpr mouse_button middle = 4;

struct mouse {
  mouse_action actiion;
  int x, y;
  mouse_button button;
  modifier_key modifier;
  bool repeat;
};

using event = std::variant<keyboard, mouse>;
