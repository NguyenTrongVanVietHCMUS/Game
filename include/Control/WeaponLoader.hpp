#pragma once

#include<fstream>
#include<stdexcept>
#include<nlohmann/json.hpp>
#include "Control/WeaponBuilder.hpp"
#include "Control/StrategyFactory.hpp"
#include "Control/State.hpp"
using json = nlohmann::json;
class WeaponLoader
{
public:
    WeaponLoader(State* state, std::string filename = "Media/Config/weaponsList.json") : mState(state), file(filename) {}
    std::shared_ptr<Weapon2> LoadWeapons(std::string weaponName);
private:
    std::ifstream file;
    State* mState;
};