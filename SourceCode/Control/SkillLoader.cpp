#include "Control/SkillLoader.hpp"


// Static member initialization
std::unordered_map<std::string, Skill *> SkillLoader::skillCache;
void SkillLoader::initializeSkills()
{
    // Register skills with their names and cooldown times
    registerSkill("Test Skill", new TestSkill(sf::seconds(1.0f))); // Example skill with 1 second cooldown
    // Add more skills as needed
}

void SkillLoader::registerSkill(const std::string& skillName, Skill* skill)
{
    SkillLoader::skillCache[skillName] = skill;
}

Skill* SkillLoader::loadSkills(const std::string& skillName, float cooldownTime)
{
    auto it = SkillLoader::skillCache.find(skillName);
        if (it != SkillLoader::skillCache.end())
        {
            Skill* skill = it->second->clone(); // Get the skill from the cache
            skill->setCooldownTime(sf::seconds(cooldownTime)); // Set the cooldown time if provided
            return skill;
        }
        return nullptr;
}