#include <Control/WeaponLoader.hpp>

void WeaponLoader::RegisterWeapon(const std::string& name, Weapon* weapon)
{
    std::cerr << "Registering weapon: " << name << std::endl;
    weapons[name] = weapon;
}

Weapon* WeaponLoader::GetWeapon(const std::string& name, Entity* holder)
{
    auto it = weapons.find(name);
    if (it != weapons.end())
    {
        std::cerr << "Weapon found: " << name << std::endl;
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
	RegisterWeapon("AK_47", std::make_unique<AK_47>(nullptr, 1.0f)->clone());
    // Add more weapons as needed
    // using nlohmann::json; to load from a JSON file and create weapons base on default weapons
    std::cerr << "Default weapons registered." << std::endl;
    // read json file and register weapons
    std::ifstream file("Media/Config/weaponsList.json");
    if (!file)
    {
        std::cerr << "Failed to open weapons list JSON file." << std::endl;
        return;
    }

    nlohmann::json json;
    file >> json;

    for (const auto& item : json)
    {
        std::string name = item["name"];
        std::string type = item["type"];
        float cooldownTime = item["cooldownTime"];
        float damage = item["damage"];
        float speed = item["speed"];

        // Create a new weapon based on the JSON data
        Weapon* weapon = GetWeapon(type, nullptr); // Get a weapon instance
        if (weapon == nullptr) 
            throw std::runtime_error("Weapon not found in JSON: " + type);
        weapon->setCooldownTime(cooldownTime);
        weapon->setDamage(damage);
        weapon->setSpeed(speed);
        weapon->setHolder(nullptr); // Set holder to nullptr for now, can be set later
        // Register the weapon
        RegisterWeapon(name, weapon);
    }
}