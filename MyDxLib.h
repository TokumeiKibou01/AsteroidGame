#pragma once
#include <DxLib.h>

extern float DeltaTime;

inline float GetDeltaTime() {
    return DeltaTime;
}

namespace Screen {
    static const int WIDTH = 1024;
    static const int HEIGHT = 768;
}

namespace DxLibParam {
    static const char* WINDOW_TITLE = "Asteroids";
    static const char* FONT_NAME = "Meiryo UI";
    static int FONT_TYPE = DX_FONTTYPE_ANTIALIASING_EDGE_8X8;
    static int BACKGROUND_COLOR[3] = { 117, 120, 125 };
}