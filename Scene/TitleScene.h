#pragma once
#include "BaseScene.h"
class TitleScene : public BaseScene {
private:
public:
    TitleScene();
    ~TitleScene();

    void Update() override;
    void Draw() override;
    void Init() override;
    void Release() override;
};
