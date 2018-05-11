#pragma once

#include <functional>

class Application final {
public:
    int run(std::function<void()>) const;
    void terminate() const noexcept;
};
