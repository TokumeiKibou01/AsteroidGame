#pragma once
#include "../Scene/BaseScene.h"
#include <vector>

class SceneManager {
private:
    std::vector<BaseScene*> sceneVector_;
    BaseScene* currentScene_;

    SceneManager();
    ~SceneManager();
public:
    static SceneManager& GetInstance();
    void ChangeScene(const std::string& sceneName);
    void UpdateScene();
    void DrawScene();
    void InitScene();
    void ReleaseScene();
    void InitManager();
};