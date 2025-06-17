#pragma once
#include <Book/Weapon.hpp>
#include <Book/Utility.hpp>
#include <Object/WeaponUtility.hpp>
#include <Book/Entity.hpp>
#include <stdexcept>

class WeaponLoader
{
private:
    std::map<std::string, Weapon*> weapons;
    WeaponLoader(); // Private constructor for singleton pattern
    ~WeaponLoader() = default; // Private destructor for singleton pattern
public:
    static WeaponLoader& Instance()
    {
        static WeaponLoader instance; // Guaranteed to be destroyed, instantiated on first use
        return instance;
    }
    WeaponLoader(const WeaponLoader&) = delete; // Delete copy constructor
    WeaponLoader& operator=(const WeaponLoader&) = delete; // Delete copy assignment operator

    void RegisterWeapon(const std::string& name, Weapon* weapon);
    Weapon* GetWeapon(const std::string& name, Entity* holder);
};
