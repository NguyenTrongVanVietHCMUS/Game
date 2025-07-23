#include<Book/CameraEffect.hpp>
#include <Control/CameraManager.hpp>

CameraEffect::CameraEffect(float duration, CameraManager* cameraManager)
    : IStatusEffect(duration), cameraManager(cameraManager) {
    if (cameraManager) {
        cameraManager->applyEffect(this);
    }
}