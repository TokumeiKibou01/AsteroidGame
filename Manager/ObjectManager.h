#pragma once
#include <vector>
#include <map>
#include <string>
#include "../Object/BaseObject.h"

class ObjectManager {
private:
    // std::vector<Base2DObject*> objAllSceneVector;
    std::map<std::string, std::vector<BaseObject*>> objEachSceneMap;
public:
    static ObjectManager& GetInstance();

    void AddObject(std::string sceneName, BaseObject* obj);

    /// <summary>
    /// Œã‚ë‚É•`‰æ‚·‚é‚Æ‚«‚ÉŽg‚¤
    /// </summary>
    /// <param name="sceneName"></param>
    /// <param name="obj"></param>
    void AddObjectBegin(std::string sceneName, BaseObject* obj);

    void RemoveObject(std::string sceneName, BaseObject* obj);

    template<class C> C* GetDrawObject(std::string sceneName) {
        std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
        for (int i = 0; i < sceneObjVector.size(); i++) {
            auto& obj = sceneObjVector[i];
            if (obj == nullptr) continue;
            C* instance = dynamic_cast<C*>(obj);
            if (instance != nullptr) {
                return instance;
            }
        }
        return nullptr;
    }

    template<class C> std::vector<C*> GetDrawObjects(std::string sceneName) {
        std::vector<C*> base;
        std::vector<BaseObject*>& sceneObjVector = objEachSceneMap.at(sceneName);
        for (int i = 0; i < sceneObjVector.size(); i++) {
            auto& obj = sceneObjVector[i];
            if (obj == nullptr) continue;
            C* instance = dynamic_cast<C*>(obj);

            if (instance != nullptr) {
                base.push_back(instance);
            }
        }
        return base;
    }

    void UpdateObject(std::string sceneName);
    void DrawObject(std::string sceneName);

    void ClearObjects(std::string sceneName);
    void ClearAllObjects();
};

