#include "SceneManager.h"
#include "../Scene/BootScene.h"
#include "../Scene/TitleScene.h"
#include "../Scene/RunningScene.h"

SceneManager::SceneManager() {
    currentScene_ = nullptr;

    sceneVector_.push_back(new BootScene());
    sceneVector_.push_back(new TitleScene());
    sceneVector_.push_back(new RunningScene());
    
    ChangeScene("BootScene");
    ChangeScene("TitleScene");
}

SceneManager::~SceneManager() {}

SceneManager& SceneManager::GetInstance() {
    static SceneManager manager;
    return manager;
}

void SceneManager::ChangeScene(const std::string& sceneName) {
    for (auto& scene : sceneVector_) {
        if (scene->GetName() == sceneName) {
            currentScene_ = scene;
            break;
        }
    }
}

void SceneManager::UpdateScene() {
    if (currentScene_ == nullptr) return;
    currentScene_->Update();
}

void SceneManager::DrawScene() {
    if (currentScene_ == nullptr) return;
    currentScene_->Draw();
}

void SceneManager::InitScene() {
    if (currentScene_ == nullptr) return;
    currentScene_->Init();
}

void SceneManager::ReleaseScene() {
    if (currentScene_ == nullptr) return;
    currentScene_->Release();
}
