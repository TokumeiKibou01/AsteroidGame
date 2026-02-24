#pragma once

extern float DeltaTime;

inline float GetDeltaTime() {
    return DeltaTime;
}

namespace Screen {
    static const int WIDTH = 1024;
    static const int HEIGHT = 768;
}