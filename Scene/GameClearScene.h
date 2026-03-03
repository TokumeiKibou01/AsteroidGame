#pragma once
#include "../Scene/BaseScene.h"

class GameClearScene : public BaseScene {
private:
public:
    GameClearScene();
    ~GameClearScene();

    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};