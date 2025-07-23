#include<Book/CameraEffect.hpp>
#include <Control/CameraManager.hpp>

CameraEffect::CameraEffect(float duration, CameraManager* cameraManager)
    : IStatusEffect(duration), cameraManager(cameraManager) {
    std::cerr << "CameraEffect created with duration: " << duration << std::endl;
    if (cameraManager) {
        cameraManager->applyEffect(this);
        std::cerr << "Camera effect applied with duration: " << duration << std::endl;
    }
}