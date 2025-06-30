#pragma once 
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<memory>
#include<algorithm>
#include<cmath> 
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>

#include <nlohmann/json.hpp>


const int width = 1216; // Width of the game window
const int height = 672; // Height of the game window

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

// convert it to world coordinates
// final_position = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
// sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
// sf::Vector2f worldPos = window.mapPixelToCoords(mousePixel, gameView);