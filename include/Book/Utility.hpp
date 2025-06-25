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

#define Mask(x) (1 << (x)) // Bitmask for setting bits
#define BIT(x,y) ((x) & (1 << (y))) // Check if the y-th bit is set in x
#define BIT_SET(x,y) ((x) |= (1 << (y))) // Set the y-th bit in x
#define BIT_CLEAR(x,y) ((x) &= ~(1 << (y))) // Clear the y-th bit in x

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