#include "HealthUI.h"
#include <DxLib.h>
#include "Base2DObject.h"
#include "../MyDxLib.h"
#include "Player.h"
#include "../Manager/ObjectManager.h"
#include "../Library/TextUtil.h"

namespace {
    const int healthWidth = 400, healthHeight = 50;
    const int marginX = 30, marginY = 30;
    const int leftX = Screen::WIDTH - marginX - healthWidth, leftY = 0 + marginY;
    const int rightX = Screen::WIDTH - marginX, rightY = marginY + healthHeight;
    const int lineSize = 5;
}

HealthUI::HealthUI()
    : BaseObject("ExplosionEffect", true) {
}

HealthUI::~HealthUI()
{
}

void HealthUI::Update() {
}

void HealthUI::Draw() {
    ObjectManager& objManager = ObjectManager::GetInstance();
    auto player = objManager.GetDrawObject<Player>("RunningScene");

    //‘S‘Ì‚Ì•`‰æ
    DrawBox(leftX - lineSize, leftY - lineSize, rightX + lineSize, rightY + lineSize, GetColor(255, 255, 255), true);
    DrawBox(leftX, leftY, rightX, rightY, GetColor(10, 10, 10), true);

    //1ŒÂ
    const int oneHealthWidth = healthWidth / PlayerParams::MAX_HEART;
    for (int n = 0; n < player->GetHeart(); n++) {
        DrawBox(rightX - (n * oneHealthWidth), leftY, rightX - ((n + 1) * oneHealthWidth), rightY, GetColor(255, 0, 0), true);
    }

    for (int n = 1; n < PlayerParams::MAX_HEART; n++) {
        DrawBox(leftX + (n * oneHealthWidth), leftY, leftX + (n * oneHealthWidth) + lineSize, rightY, GetColor(255, 255, 255), true);
    }

    TextUtil::DrawFixText(TextDrawType::LEFT, leftX, leftY - marginY, 30, GetColor(255, 255, 255), "‘Ì—Í");
}
