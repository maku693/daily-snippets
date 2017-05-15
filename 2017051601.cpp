// States

struct Application {
    bool isActive;
};

struct Window {
    bool isFullScreen;
    Vec2 size;
};

struct Curosor {
    bool isLocked;
};

// Events

struct Initialize {};
struct Activate {};
struct Inactivate {};
struct Quit {};

struct LockCursor {};

struct MoveCursor {
    int x;
    int y;
};

enum class KeyCode {
    Space = 0x20,
};

struct DownKey {
    KeyCode key;
};
