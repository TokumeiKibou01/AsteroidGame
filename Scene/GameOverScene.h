#pragma once
#include "BaseScene.h"
class GameOverScene : public BaseScene {
private:
public:
    GameOverScene();
    ~GameOverScene();

    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};
