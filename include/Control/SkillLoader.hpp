#pragma once
#include <Object/SkillLibraryUtility.hpp>
#include <unordered_map>

class SkillLoader
{
public:
    static std::unordered_map<std::string, Skill *> skillCache;
public:
    SkillLoader() = default;
    ~SkillLoader() = default;

    // Load skills from a file
    static Skill* loadSkills(const std::string& skillName, float cooldownTime = 0.0f);
    static void registerSkill(const std::string& skillName, Skill* skill);
    // static constructor
    static void initializeSkills();
};