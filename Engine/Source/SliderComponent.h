#pragma once
#include "Component.h"

class CanvasComponent;
class GameObject;
class Transform2DComponent;
class ImageComponent;

class ENGINE_API SliderComponent :
    public Component
{
public:
    SliderComponent(GameObject* owner);
    SliderComponent(GameObject* owner, bool active);
    SliderComponent(const SliderComponent& original, GameObject* owner);
    ~SliderComponent();

    void Reset() override {}
    void Update() override {}

    Component* Clone(GameObject* owner) const override;
    void SetValue(float fillPercent);

    float GetValue() { return mValue; }
    float* GetValuePointer() { return &mValue; }

    void Save(JsonObject& obj) const override;
    void Load(const JsonObject& data, const std::unordered_map<unsigned int, GameObject*>& uidPointerMap) override;

private:
    GameObject* FindCanvasOnParents(GameObject* gameObject);

    GameObject* mFill = nullptr;
    GameObject* mBackground = nullptr;

    Transform2DComponent* mSliderTransform2D = nullptr;

    ImageComponent* mBgImage = nullptr;
    ImageComponent* mFillImage = nullptr;

    Transform2DComponent* mBgTransform2D = nullptr;
    Transform2DComponent* mFillTransform2D = nullptr;

    float mValue = 0.75f;

    CanvasComponent* mCanvas = nullptr;
};

