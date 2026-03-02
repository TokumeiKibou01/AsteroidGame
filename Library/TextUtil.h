#pragma once
#include <string>
#include <DxLib.h>

enum TextDrawType {
    LEFT, //ç∂ëµÇ¶
    CENTER, //íÜâõëµÇ¶
    RIGHT //âEëµÇ¶
};

namespace TextUtil {

    static void DrawFontEdgeFixText(TextDrawType type, int x, int y, int size, int text_color, int edge_color, std::string font, std::string text) {
        const char* oldFont = GetFontName();
        ChangeFont(font.c_str());
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
        int fontSize = GetFontSize();
        SetFontSize(size);
        int strWidth = GetDrawStringWidth(text.c_str(), strlen(text.c_str()));
        if (type == TextDrawType::LEFT) {
            //DxLibÇ≈ÇÕí èÌÇ≈ç∂ëµÇ¶ÇÃÇΩÇﬂÅAâΩÇ‡ÇµÇ»Ç¢
        } else if (type == TextDrawType::RIGHT) {
            x -= strWidth;
        } else if (type == TextDrawType::CENTER) {
            x -= strWidth / 2;
            y -= size / 2;
        }

        if (edge_color < 0) {
            DrawString(x, y, text.c_str(), text_color);
        } else {
            DrawString(x, y, text.c_str(), text_color, edge_color);
        }

        SetFontSize(fontSize);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
        ChangeFont(oldFont);
    }

    static void DrawFixText(TextDrawType type, int x, int y, int size, int text_color, int edge_color, std::string text) {
        DrawFontEdgeFixText(type, x, y, size, text_color, edge_color, std::string(GetFontName()), text);
    }

    static void DrawFixText(TextDrawType type, int x, int y, int size, int text_color, std::string text) {
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_4X4);
        DrawFontEdgeFixText(type, x, y, size, text_color, -1, std::string(GetFontName()), text);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_4X4);
    }

}