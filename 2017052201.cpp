enum class KeyCode {
    Esc,
    Space,
    A, D, S, W,
    Undefined,
};

auto translateVKToKeyCode(USHORT vk)
{
    switch (vk) {
    case VK_ESCAPE:
        return KeyCode::Esc;
    case VK_SPACE:
        return KeyCode::Space;
    case 0x41:
        return KeyCode::A;
    case 0x44:
        return KeyCode::D;
    case 0x53:
        return KeyCode::S;
    case 0x57:
        return KeyCode::W;
    default:
        return KeyCode::Undefined;
    }
}

enum class MouseButton {
    L, R, Undefined,
};

enum class MouseButtonState {
    Down, Up,
};

struct MouseClick {
    MouseButton button;
    MouseButtonState state;
};
