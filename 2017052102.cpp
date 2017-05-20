enum class KeyCode {
    Undefined,
    Esc,
    Space,
    A, D, S, W,
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
