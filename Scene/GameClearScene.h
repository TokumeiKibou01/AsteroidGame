#pragma once
#include "../Scene/BaseScene.h"

class GameClearScene : public BaseScene {
private:
    int count;
public:
    GameClearScene();
    ~GameClearScene();

    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};