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

void ObjectManager::AddObjectBegin(std::string sceneName, BaseObject* obj) {
    if (objEachSceneMap.find(sceneName) == objEachSceneMap.end()) {
        objEachSceneMap[sceneName] = std::vector<BaseObject*>();
    }
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    sceneObjVector.insert(sceneObjVector.begin(), obj);
}

void ObjectManager::AddObjectEnd(std::string sceneName, BaseObject* obj) {
    if (objEachSceneMap.find(sceneName) == objEachSceneMap.end()) {
        objEachSceneMap[sceneName] = std::vector<BaseObject*>();
    }
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    sceneObjVector.insert(sceneObjVector.begin() + sceneObjVector.size() - 1, obj);
}

void ObjectManager::RemoveObject(std::string sceneName, BaseObject* obj) {
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    for (auto it = sceneObjVector.begin(); it != sceneObjVector.end(); ) {
        if ((*it) == obj && (*it)->IsAlive() && *it != nullptr) {
            obj->Dead();
            break;
        } else {
            ++it;
        }
    }
}

void ObjectManager::UpdateObject(std::string sceneName) {
    auto& objVector = objEachSceneMap.at(sceneName);
    for (int i = 0; i < objVector.size(); i++) {
        auto& obj = objVector[i];
        if (obj == nullptr) continue;
        obj->Update();
    }

    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    for (auto it = sceneObjVector.begin(); it != sceneObjVector.end(); ) {
        if (!(*it)->IsAlive() && *it != nullptr) {
            delete* it;
            it = sceneObjVector.erase(it);
        } else {
            ++it;
        }
    }
}

void ObjectManager::DrawObject(std::string sceneName) {
    auto& objVector = objEachSceneMap.at(sceneName);
    for (int i = 0; i < objVector.size(); i++) {
        auto& obj = objVector[i];
        if (obj == nullptr) continue;
        obj->Draw();
    }
}

void ObjectManager::ClearObjects(std::string sceneName) {
    std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
    for (auto it = sceneObjVector.begin(); it != sceneObjVector.end(); ) {
        if (*it != nullptr) {
            delete* it;
            it = sceneObjVector.erase(it);
        } else {
            ++it;
        }
    }
}

void ObjectManager::ClearAllObjects() {
    objEachSceneMap.clear();
}
