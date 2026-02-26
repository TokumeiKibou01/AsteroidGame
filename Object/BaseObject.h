#pragma once
#include <string>

/// <summary>
/// ゲームオブジェクトの基底クラス（※2D/3Dの場合は、Base2D/3DObjectを推奨。）
/// </summary>
class BaseObject {
private:
protected:
    std::string name_;
    bool isAlive_;
public:
    virtual void Update() = 0;
    virtual void Draw() = 0;

    BaseObject(std::string name, bool isAlive) {
        name_ = name;
        isAlive_ = isAlive;
    };
    virtual ~BaseObject() {}

    std::string GetName() { return name_; };
    bool IsAlive() { return isAlive_; };
    void Dead() { isAlive_ = false; }
};

