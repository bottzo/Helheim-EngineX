#pragma once
#include "Component.h"
#include "Math/float4x4.h"
#include "Math/float3.h"
#include "Geometry/Frustum.h"

class ENGINE_API CameraComponent :
    public Component
{
public:
    CameraComponent(GameObject* owner);
    CameraComponent(const CameraComponent& original, GameObject* owner);
    ~CameraComponent();

    void Enable() override;
    void Disable() override;
    void Update() override;
    void Reset() override;
    Component* Clone(GameObject* owner) const override;


    const Frustum& GetFrustum() const { UpdateFrustum(); return mFrustum; }

    const float4x4 GetViewMatrix() const { UpdateFrustum(); return mFrustum.ViewMatrix(); }
    const float4x4 GetProjectionMatrix() const { UpdateFrustum(); return mFrustum.ProjectionMatrix(); }
    const float4x4 GetViewProjectionMatrix() const { UpdateFrustum(); return mFrustum.ViewProjMatrix(); }

    void SetNearPlane(float value);
    void SetFarPlane(float value);
    void SetFOV(float value);
    void SetAspectRatio(float value);

    float GetNearPlane() const { UpdateFrustum(); return mFrustum.nearPlaneDistance; }
    float GetFarPlane() const { UpdateFrustum(); return mFrustum.farPlaneDistance; }
    float GetVerticicalFOV() const { UpdateFrustum(); return mFrustum.verticalFov; }
    float GetHorizontalFOV() const { UpdateFrustum(); return mFrustum.horizontalFov; }

private:

    void Save(JsonObject& obj) const override;
    void Load(const JsonObject& data, const std::unordered_map<unsigned int, GameObject*>& uidPointerMap) override;

    void UpdateFrustum() const;

    mutable bool mHasUpdatedFrustum = false;
    mutable Frustum mFrustum;
    bool mEnableCulling = true;
    float mAspectRatio;
};

