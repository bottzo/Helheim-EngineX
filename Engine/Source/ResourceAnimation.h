#pragma once

#include <memory> // Include the <memory> header for std::unique_ptr
#include <unordered_map>
#include "Quat.h" // Include the headers for Quat and float3 if they are custom types
#include "float3.h"
#include "Resource.h"
#include <string>

namespace tinygltf
{
    class Model;
    struct Animation;
    struct AnimationChannel;
}

class ENGINE_API ResourceAnimation : public Resource
{
public:
    ResourceAnimation(unsigned int uid, const std::string name); 
    ~ResourceAnimation();

    // Define a structure to store keyframes for positions and rotations
    struct AnimationChannel {
        std::unique_ptr<float3[]> positions;
        std::unique_ptr<float[]> posTimeStamps;
        std::unique_ptr<Quat[]> rotations;
        std::unique_ptr<float[]> rotTimeStamps;
        /*std::unique_ptr<float3[]> scales;
        std::unique_ptr<float[]> scaleTimeStamps;*/

        uint32_t numPositions = 0;
        uint32_t numRotations = 0;
        /*uint32_t numScales = 0;*/

        bool hasTranslation = false;
        bool hasRotation = false;
        /*bool hasScale = false;*/

    };

    
    AnimationChannel* GetChannel(const std::string& name) const;
   
    const std::unordered_map<std::string, AnimationChannel*>& GetChannels() { return mChannels; }
    const std::string& GetName() const {return mName; }
    const float& GetDuration() const { return mDuration; }

    void CleanUp();

    //TODO:Make private//
    std::unordered_map<std::string, AnimationChannel*> mChannels;

    std::string mName;
    float mDuration = 0;
};


