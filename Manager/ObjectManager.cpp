#include "../Manager/ObjectManager.h"
#include "../Object/BaseObject.h"
#include <string>

ObjectManager& ObjectManager::GetInstance() {
    static ObjectManager manager;
    return manager;
}

void ObjectManager::AddObject(std::string sceneName, BaseObject* obj) {
    if (objEachSceneMap.find(sceneName) == objEachSceneMap.end()) {
        objEachSceneMap[sceneName] = std::vector<BaseObject*>();
    }
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    sceneObjVector.push_back(obj);
}

void ObjectManager::RemoveObject(std::string sceneName, BaseObject* obj) {
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    for (auto it = sceneObjVector.begin(); it != sceneObjVector.end(); ) {
        if ((*it) == obj && (*it)->IsAlive() && *it != nullptr) {
            obj->Dead();
        } else {
            it++;
        }
    }
}

void ObjectManager::UpdateObject(std::string sceneName) {
    auto& objVector = objEachSceneMap.at(sceneName);
    for (auto& obj : objVector) {
        if (obj == nullptr) continue;
        obj->Update();
    }

    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    for (auto it = sceneObjVector.begin(); it != sceneObjVector.end(); ) {
        if (!(*it)->IsAlive() && *it != nullptr) {
            delete* it;
            it = sceneObjVector.erase(it);
        } else {
            it++;
        }
    }
}

void ObjectManager::DrawObject(std::string sceneName) {
    auto& objVector = objEachSceneMap.at(sceneName);
    for (auto& obj : objVector) {
        if (obj == nullptr) continue;
        obj->Draw();
    }
}
