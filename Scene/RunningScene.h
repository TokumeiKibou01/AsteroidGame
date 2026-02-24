#pragma once
#include "BaseScene.h"
class RunningScene : public BaseScene {
private:
public:
    RunningScene();
    ~RunningScene();

    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};

