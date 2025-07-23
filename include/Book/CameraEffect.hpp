#pragma once
#include <Book/StrategyClass.hpp>

class CameraManager;

class CameraEffect : public IStatusEffect
{
protected:
    CameraManager* cameraManager; // Pointer to the camera manager
public:
    CameraEffect(float duration, CameraManager* cameraManager = nullptr);
};