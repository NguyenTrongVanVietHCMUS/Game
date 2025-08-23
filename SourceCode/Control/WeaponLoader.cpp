#include <Control/WeaponLoader.hpp>
#include <Control/ProjectileLoader.hpp>
#include <Book/Weapon2.hpp>
#include <Control/State.hpp>
std::shared_ptr<Weapon2> WeaponLoader::LoadWeapons(std::string weaponName) {
    ProjectileLoader projectileLoader(mState);
    std::ifstream file = std::ifstream(filePath);
    if (!file.is_open()) {
        std::cerr << "Failed to open weapon file: " << weaponName << std::endl;
        throw std::runtime_error("Failed to open weapon file: " + weaponName);
    }
    json weaponData;
    file >> weaponData;
    if (!weaponData.contains(weaponName)) {
        throw std::runtime_error("Weapon not found: " + weaponName);
    }
    std::cerr << "Start building weapon : " << weaponName << std::endl;
    // Create a WeaponBuilder instance
    WeaponBuilder builder = WeaponBuilder::create(weaponData[weaponName]["name"].get<std::string>(), 
                                                  sf::Vector2f(weaponData[weaponName]["position"]["x"], weaponData[weaponName]["position"]["y"]), 
                                                  mState);
    if (weaponData[weaponName].contains("behavior")) {
        
        auto behavior = StrategyFactory::createBehavior(weaponData[weaponName]["behavior"], mState);
        if (weaponData[weaponName]["behavior"].contains("Projectile")) {
            behavior->setProjectile(weaponData[weaponName]["behavior"]["Projectile"].get<std::string>());
        }
        builder.withBehavior(std::move(behavior));
    }

    if(weaponData[weaponName].contains("manaUsage")) {
        builder.withManaUsage(weaponData[weaponName]["manaUsage"].get<float>());
    }

    if(weaponData[weaponName].contains("SoundPath")) {
        std::string soundPath = weaponData[weaponName]["SoundPath"].get<std::string>();
        if (!soundPath.empty()) {
            builder.withSoundPath(soundPath);
        }
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
    
    std::shared_ptr<Weapon2> weapon = builder.build();

    // If the weapon has an advanced component, load it
    if (weaponData[weaponName].contains("ComboPath")) {
        std::unique_ptr<AdvanceWeaponComponent> advanceComponent = std::make_unique<AdvanceWeaponComponent>(weapon, nullptr);
        advanceComponent->loadFromJson(weaponData[weaponName]["ComboPath"], mState, nullptr);
    }

    file.close(); // Close the file after reading
    // Build and return the weapon
    return weapon;
}

std::shared_ptr<Weapon2> WeaponLoader::LoadRandomWeapon() {
    std::cerr << "Creating a random weapon\n";
    std::ifstream file = std::ifstream(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open weapon file for random weapon selection.");
    }

    json weaponData;
    file >> weaponData;

    // Get a random weapon name from the JSON data
    if (weaponData.empty()) {
        throw std::runtime_error("No weapons available in the file.");
    }

    auto it = weaponData.begin();
    std::advance(it, rand() % weaponData.size()); // Randomly select a weapon
    std::string randomWeaponName = it.key();
    std::cerr << "Random weapon selected: " << randomWeaponName << std::endl;
    // close the file after reading
    file.close();
    return LoadWeapons(randomWeaponName);
}