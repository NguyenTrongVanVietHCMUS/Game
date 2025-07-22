#pragma once
#include <Book/StrategyClass.hpp>

class CameraManager; // Forward declaration


class CameraEffect : public IStatusEffect
{
protected:
    CameraManager* cameraManager; // Pointer to the camera manager
};