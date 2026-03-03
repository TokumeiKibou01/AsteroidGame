#pragma once
#include "BaseScene.h"

class BootScene : public BaseScene {
private:
public:
    BootScene();
    ~BootScene();
    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};