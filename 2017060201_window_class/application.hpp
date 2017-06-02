#pragma once

class Application final {
public:
    int run() noexcept;
    void updateWindows() noexcept;
    void terminate() noexcept;

private:
    bool m_shouldKeepRunning;
    std::array<std::function<void()>> m_listeners;
    std::array<Window> m_windows;
};
