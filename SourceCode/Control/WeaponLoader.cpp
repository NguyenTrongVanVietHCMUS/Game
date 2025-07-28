#include <Control/WeaponLoader.hpp>
#include <Book/Weapon2.hpp>

std::shared_ptr<Weapon2> WeaponLoader::LoadWeapons(std::string weaponName) {
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open weapon file: " + weaponName);
    }

    json weaponData;
    file >> weaponData;

    // get the weapon data by name
    if (!weaponData.contains(weaponName)) {
        throw std::runtime_error("Weapon not found: " + weaponName);
    }

    // Create a WeaponBuilder instance
    WeaponBuilder builder = WeaponBuilder::create(weaponData[weaponName]["name"].get<std::string>(), 
                                                  sf::Vector2f(weaponData[weaponName]["position"]["x"], weaponData[weaponName]["position"]["y"]), 
                                                  mState);
    if (weaponData[weaponName].contains("behavior")) {
        builder.withBehavior(StrategyFactory::createBehavior(weaponData[weaponName]["behavior"], mState));
    }
    if (weaponData[weaponName].contains("animation")) {
        builder.withAnimation(StrategyFactory::createAnimation(weaponData[weaponName]["animation"], nullptr));
    }
    if (weaponData[weaponName].contains("cooldownTime")) {
        builder.withCooldownTime(weaponData[weaponName]["cooldownTime"].get<float>());
    }
    if (weaponData[weaponName].contains("scaleBulletSpawnPosition")) {
        builder.withScaleBulletSpawnPosition(sf::Vector2f(
            weaponData[weaponName]["scaleBulletSpawnPosition"]["x"],
            weaponData[weaponName]["scaleBulletSpawnPosition"]["y"]
        ));
    }

    // Build and return the weapon
    return builder.build();

}