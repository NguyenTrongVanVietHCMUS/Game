#include<Book/Game.hpp>
int main()
{
    Game game ; 
    game.Run();
    return 0;
}

// #include "Book/TileMap.hpp"
// #include<Book/Utility.hpp>
// int main() {
    // std::string filename = "Media/Assets/Maps/Lobby/lobby.json"; 
    // std::ifstream file(filename);
    // if (!file.is_open()) {
    //     std::cerr << "Failed to open map file: " << filename << std::endl;
    //     return false;
    // }
    // nlohmann::json mapData;
    // try {
    //     file >> mapData;
    // } catch (const nlohmann::json::parse_error& e) {
    //     std::cerr << "JSON parse error: " << e.what() << std::endl;
    //     return false;
    // }
    // int m_tileWidth = mapData["tilewidth"];
    // int m_tileHeight = mapData["tileheight"];
    // std::cout<<m_tileWidth<<std::endl;
    // std::cout<<m_tileHeight<<std::endl;
    // sf::Texture texture ; 
    // if(!texture.loadFromFile("Media/Assets/TileSets/Copy.png"))
    // {
    //     std::cerr << "Failed to load texture" << std::endl;
    //     return EXIT_FAILURE;
    // }
    // sf::RenderWindow window(sf::VideoMode(1920, 1000), "TileMap Demo", sf::Style::Close | sf::Style::Titlebar);
    // window.setFramerateLimit(60);
    // TileMap map;
    // if(!map.load("Media/Assets/Maps/Lobby/lobby.json")) {
    //     std::cerr << "Failed to load map" << std::endl;
    //     return EXIT_FAILURE;
    // }
    // //Hide decorative layers

    // while (window.isOpen()) {
    //     sf::Event event;
    //     while (window.pollEvent(event)) {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear(sf::Color::Green);
    //     window.draw(map); // Uses the draw() override
    //     window.display();
    //     // In main.cpp
    //     // window.clear();
    //     // sf::Text debugText;
    //     // sf::Font font;
    //     // font.loadFromFile("Sansation.ttf");
    //     // debugText.setFont(font);
    //     // debugText.setString("Debug View - Map should appear below");
    //     // debugText.setPosition(10, 10);
    //     // window.draw(debugText);
    //     // window.draw(map);
    //     // window.display();
//     }
//     // return EXIT_SUCCESS;
// }