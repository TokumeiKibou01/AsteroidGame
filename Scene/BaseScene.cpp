#include "BaseScene.h"

BaseScene::BaseScene(std::string name) {
    name_ = name;
    sceneCounter_ = 0;
}

std::string BaseScene::GetName() {
    return name_;
}
