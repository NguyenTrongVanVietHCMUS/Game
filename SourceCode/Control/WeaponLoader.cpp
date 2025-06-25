#include <Control/WeaponLoader.hpp>

void WeaponLoader::RegisterWeapon(const std::string& name, Weapon* weapon)
{
    weapons[name] = weapon;
}

Weapon* WeaponLoader::GetWeapon(const std::string& name, Entity* holder)
{
    auto it = weapons.find(name);
    if (it != weapons.end())
    {
        Weapon* weapon = it->second->clone(); // Return a clone of the weapon
        weapon->setHolder(holder);
        return weapon;
    }
    throw std::runtime_error("Weapon not found: " + name);
    return nullptr; // Return nullptr if the weapon is not found
}

WeaponLoader::WeaponLoader()
{
    // Register default weapons here
    std::cerr << "Registering default weapons..." << std::endl;
    RegisterWeapon("Gun", std::make_unique<Gun>(nullptr, 1.0f)->clone());
    // Add more weapons as needed
}