#pragma once
#include <string>
#include <DxLib.h>

enum TextDrawType {
    LEFT, //ç∂ëµÇ¶
    CENTER, //íÜâõëµÇ¶
    RIGHT //âEëµÇ¶
};

namespace TextUtil {

    static void DrawFixText(TextDrawType type, int x, int y, int size, int text_color, int edge_color, std::string text) {
        int fontSize = GetFontSize();
        SetFontSize(size);
        int strWidth = GetDrawStringWidth(text.c_str(), strlen(text.c_str()));
        if (type == TextDrawType::LEFT) {
            //DxLibÇ≈ÇÕí èÌÇ≈ç∂ëµÇ¶ÇÃÇΩÇﬂÅAâΩÇ‡ÇµÇ»Ç¢
        } 
        else if (type == TextDrawType::RIGHT) {
            x -= strWidth;
        } 
        else if (type == TextDrawType::CENTER) {
            x -= strWidth / 2;
            y -= size / 2;
        }

        if (edge_color < 0) {
            DrawString(x, y, text.c_str(), text_color);
        }
        else {
            DrawString(x, y, text.c_str(), text_color, edge_color);
        }
        
        SetFontSize(fontSize);
    }

    static void DrawFixText(TextDrawType type, int x, int y, int size, int text_color, std::string text) {
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_8X8);
        DrawFixText(type, x, y, size, text_color, -1, text);
        ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
    }

}