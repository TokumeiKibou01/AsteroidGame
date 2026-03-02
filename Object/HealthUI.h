#pragma once
#pragma once
#include "../Object/BaseObject.h"
#include "../Library/Location2D.h"
#include "../Library/Vector2D.h"

/// <summary>
/// ‘Ì—Í‚ÌUI
/// </summary>
class HealthUI : public BaseObject {
private:
public:
    HealthUI();
    ~HealthUI();
    void Update() override; 
    void Draw() override;
};