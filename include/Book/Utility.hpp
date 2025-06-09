#pragma once 
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<cmath> 
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#define VV std::cout<<"RUN OK"<<std::endl; 
#define boom exit(1); 

enum WeaponType
{
    WeaponType_Gun,
    WeaponType_Sword
};

enum EntityType
{
    EntityType_Ally,
    EntityType_Enemy,
    EntityType_Neutral
};
