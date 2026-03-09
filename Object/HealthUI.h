#pragma once
#pragma once
#include "../Object/BaseObject.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"
#include "../MyDxLib.h"

namespace {
    const int healthWidth = 400, healthHeight = 50;
    const int marginX = 30, marginY = 30;
    const int leftX = Screen::WIDTH - marginX - healthWidth, leftY = 0 + marginY;
    const int rightX = Screen::WIDTH - marginX, rightY = marginY + healthHeight;
    const int lineSize = 5;
}

/// <summary>
/// ‘Ì—Í‚ÌUI
/// </summary>
class HealthUI : public BaseObject {
private:
public:
    HealthUI();
    ~HealthUI();
    void Update() override; 
    void Draw() override;
};