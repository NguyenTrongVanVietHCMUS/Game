#include "Book/TileMap.hpp"
#include<Control/Foreach.hpp>
#include <fstream> 
#include<Book/Character.hpp>
#include<Book/Enemy.hpp>
TileMap::TileMap()
{

}
TileMap::~TileMap() 
{    
    layers.clear(); 
    entities.clear(); 
    // Destructor
}

bool TileMap::loadFromFile(const std::string& jsonFile) 
{
    File = jsonFile ; 
    std::ifstream file(jsonFile) ;  
    if(!file.is_open())return false ;

    json datafile ; 
    file >> datafile  ; 
    for(auto &data: datafile["maps"] )
    {
        std::string path =  data["fileName"] ; 
        int x = data["x"] ; 
        int y = data["y"] ; 
        std::filesystem::path jsonPath(jsonFile);
        std::filesystem::path jsonDir = jsonPath.parent_path();
        std::filesystem::path resolvedPath = jsonDir / path;
        if(!load(resolvedPath.string(),x,y,data["height"],data["width"]))return false;
    }
    return true ; 
}
bool TileMap::load(const std::string& jsonFile,int x , int y,int height, int width ) 
{

    File = jsonFile ; 
    // Load JSON file
    std::ifstream file(jsonFile);
    if (!file.is_open())return false;  
    
    json mapData;
    file >> mapData;
    // Load tilesets.back()f
    tilesets.push_back(std::vector<Tileset>());
    for (auto& tilesetData : mapData["tilesets"]) 
    {
        if (tilesetData.contains("image") == true)
        {
            Tileset tileset;
            std::string imagePath = tilesetData["image"];
            // Resolve imagePath relative to the JSON file's directory
            std::filesystem::path jsonPath(jsonFile);
            std::filesystem::path jsonDir = jsonPath.parent_path();
            std::filesystem::path resolvedImagePath = jsonDir / imagePath;

            // Load the tileset texture from the resolved path
            if (!tileset.texture.loadFromFile(resolvedImagePath.string())) {
                std::cerr << "Failed to load tileset texture from: " << resolvedImagePath.string() << std::endl;
                return false;
            }
            tileset.File = resolvedImagePath.string();
            tileset.firstGid = tilesetData["firstgid"];
            tileset.tileWidth = tilesetData["tilewidth"];
            tileset.tileHeight = tilesetData["tileheight"]; 
            tileset.columns = tilesetData["columns"];
            tileset.tileCount = tilesetData["tilecount"];
            tilesets.back().push_back(tileset);
        }
        else
        {
            for (auto& tiles : tilesetData["tiles"])
            {
                if (!tiles.contains("objectgroup"))
                {
                    std::cerr << "WRONG " << std::endl;
                }
                else std::cerr << "RIGHT " << std::endl;
                Tileset tileset;
                std::string imagePath = tiles["image"];
                // Resolve imagePath relative to the JSON file's directory
                std::filesystem::path jsonPath(jsonFile);
                std::filesystem::path jsonDir = jsonPath.parent_path();
                std::filesystem::path resolvedImagePath = jsonDir / imagePath;

                // Load the tileset texture from the resolved path
                std::cerr << imagePath << std::endl;
                if (!tileset.texture.loadFromFile(resolvedImagePath.string())) {
                    std::cerr << "Failed to load tileset texture from: " << resolvedImagePath.string() << std::endl;
                    return false;
                }
                tileset.File = resolvedImagePath.string();
                tileset.firstGid = int(tilesetData["firstgid"]) + int(tiles["id"]);
                tileset.tileWidth = tiles["imagewidth"];
				tileset.type = tiles["type"];
                tileset.tileHeight = tiles["imageheight"];
                auto& temp = tiles["objectgroup"];
                for(auto &info : temp["objects"]) // changed x to temp
                {
                    tileset.hitbox = Hitbox(sf::FloatRect(info["x"], info["y"] , info["width"], info["height"])); // changed x to info
                }
                tilesets.back().push_back(tileset);
            }
        }
    }
    
    // Load layers
    for (auto& layerData : mapData["layers"])
    {
        if (layerData["type"] == "imagelayer")
        {
            std::string imagePath = layerData["image"];
            std::filesystem::path jsonPath(jsonFile);
            std::filesystem::path jsonDir = jsonPath.parent_path();
            std::filesystem::path resolvedImagePath = jsonDir / imagePath;
            // Resolve imagePath relative to the JSON file's directory

            // Load the background texture
            sf::Texture backgroundTexture;
            if (!backgroundTexture.loadFromFile(resolvedImagePath.string())) {
                return false;
            }
            // backgroundTexture.loadFromFile("Media/Assets/Maps/Title/background.png");
            layers.push_back(new ImageLayer());
            auto layer = static_cast<ImageLayer*>(layers.back());
            layer->type = Layer::ImageLayer;
            layer->name = layerData["name"];
            layer->visible = layerData["visible"];
            layer->texture.loadFromFile(resolvedImagePath.string());
            layer->sprite.setTexture(layer->texture);
            layer->sprite.setPosition(layerData["x"] + x, layerData["y"] + y);
        }
        else if (layerData["type"] == "tilelayer")
        {
            layers.push_back(new TileLayer());
            auto layer = static_cast<TileLayer*>(layers.back());
            layer->type = Layer::TileLayer;
            layer->name = layerData["name"];
            layer->visible = layerData["visible"];
            layer->width = layerData["width"];
            layer->height = layerData["height"];
            layer->setPosition(layerData["x"] + x, layerData["y"] + y);
            // Load tile data
            layer->vertices.resize(tilesets.back().size());
            for (size_t i = 0; i < tilesets.back().size(); ++i) {
                layer->vertices[i].setPrimitiveType(sf::Quads);
                layer->vertices[i].resize(layerData["data"].size() * 4);
            }
            layer->tilesets = tilesets.back();
            for (int i = 0; i < layerData["data"].size(); i++)
            {
                int tileId = layerData["data"][i];
                if (tileId == 0) continue; // Skip empty tiles
                size_t tilesetIndex = 0;
                for (size_t j = 0; j < tilesets.back().size(); j++)
                {
                    if (tileId >= tilesets.back()[j].firstGid && tileId < tilesets.back()[j].firstGid + tilesets.back()[j].tileCount)
                    {
                        tilesetIndex = j;
                        break;
                    }
                }
                int localTileId = tileId - tilesets.back()[tilesetIndex].firstGid;
                float tileX = (localTileId % tilesets.back()[tilesetIndex].columns) * tilesets.back()[tilesetIndex].tileWidth * 1.0f;
                float tileY = (localTileId / tilesets.back()[tilesetIndex].columns) * tilesets.back()[tilesetIndex].tileHeight * 1.0f;

                // Calculate the position of the tile in the layer
                float X = (i % layer->width) * tilesets.back()[tilesetIndex].tileWidth * 1.0f;
                float Y = (i / layer->width) * tilesets.back()[tilesetIndex].tileHeight * 1.0f;

                // Define the vertices for the tile
                sf::Vertex* quad = &layer->vertices[tilesetIndex][i * 4];
                quad[0].position = sf::Vector2f(X + x, Y + y);
                quad[1].position = sf::Vector2f(X + x + tilesets.back()[tilesetIndex].tileWidth, Y + y);
                quad[2].position = sf::Vector2f(X + x + tilesets.back()[tilesetIndex].tileWidth, Y + y + tilesets.back()[tilesetIndex].tileHeight);
                quad[3].position = sf::Vector2f(X + x, Y + y + tilesets.back()[tilesetIndex].tileHeight);

                // Set the texture coordinates
                quad[0].texCoords = sf::Vector2f(tileX, tileY);
                quad[1].texCoords = sf::Vector2f(tileX + tilesets.back()[tilesetIndex].tileWidth, tileY);
                quad[2].texCoords = sf::Vector2f(tileX + tilesets.back()[tilesetIndex].tileWidth, tileY + tilesets.back()[tilesetIndex].tileHeight);
                quad[3].texCoords = sf::Vector2f(tileX, tileY + tilesets.back()[tilesetIndex].tileHeight);
            }
        }
        else if (layerData["type"] == "objectgroup")
        {
            layers.push_back(new ObjectLayer());
            auto layer = static_cast<ObjectLayer*>(layers.back());
            layer->type = Layer::ObjectGroup;
            layer->name = layerData["name"];
            layer->visible = layerData["visible"];
            layer->setPosition(layerData["x"] + x, layerData["y"] + y);
            // Load object
            for (auto& objectData : layerData["objects"])
            {
                if (objectData["type"] == "Collider")
                {
                    layer->entities.push_back(new Entity(
                        "Collider",
                        sf::Vector2f(objectData["x"] + x, objectData["y"] + y),
                        sf::FloatRect(objectData["x"] + x,
                            objectData["y"] + y,
                            objectData["width"],
                            objectData["height"])
                    ));
                }
                else if (objectData["type"] == "Point")
                {
                    if (objectData["name"] == "StartingPoint")
                    {
                        startingPoint = sf::Vector2f(objectData["x"] + x, objectData["y"] + y);
                    }
                }
                else 
                {
                    int gid = objectData["gid"];
                    size_t tilesetIndex = 0; 

                    for (size_t j = 0; j < tilesets.back().size(); ++j)
                    {
                        if (gid == tilesets.back()[j].firstGid)
                        {
                            tilesetIndex = j;
                            break;
                        }
                    }
					auto& tile = tilesets.back()[tilesetIndex];
                    if (layerData["name"] == "taskboard")
                    {

                    }
                    else
                    {
						float scalex = float(objectData["width"]) / tile.tileWidth;
						float scaley = float(objectData["height"]) / tile.tileHeight;

                        layer->entities.push_back(
                            new Object
                            (
                                objectData["name"],
                                tile.File,
                                sf::Vector2f(objectData["x"] + x, objectData["y"] + y - float(objectData["height"])),
                                sf::FloatRect(x+objectData["x"] + tile.hitbox.hitbox.left*scalex,y+ objectData["y"] - objectData["height"] + tile.hitbox.hitbox.top  * scaley, tile.hitbox.hitbox.width* scalex, tile.hitbox.hitbox.height* scaley),
                                scalex,
                                scaley
                            )
                        );
                    }
                }
            }
            for (auto&x : layer->entities)
            {
                entities.emplace_back(x); 
            }
        }
        layers.back()->area = Hitbox(sf::FloatRect (x, y, width, height));
    }
    sort(layers.begin(), layers.end(), [](const Layer* x, const Layer* y) {return x->area < y->area; });
    return true;
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states)const
{
    //target.setView(target.getDefaultView()); // Reset the view to the default view
    for(auto  x :entities)
    {
        if(auto character = dynamic_cast<Character*>(x))
        {
            sf::View view (character->getPosition(), sf::Vector2f(1216, 672));
            target.setView(view); // Set the view to the character's position
        }
    }
    for(auto& x : layers)
    {
        x->draw(target, states); // Draw each layer
	}
    for (auto& x : entities)
    {
		x->draw(target, states); // Draw each entity
    }
}
bool TileMap::handleEvent(const sf::Event& event,sf::RenderWindow* window) 
{
    for(auto&x : entities)
    {
        if (auto character = dynamic_cast<Character*>(x))
        {
            character->handleEvent(event, window);
        }
    }
    return 0; 
}
bool TileMap::update(const sf::Time& dt)
{
    for (auto& x : entities)
    {
        if (auto enemy = dynamic_cast<Enemy*>(x))
        {
            for (auto& y : entities)
            {
                if (auto character = dynamic_cast<Character*>(y))
                {
                    enemy->attack(character);
                }
            }
        }
    }
    for (auto& x : entities)x->update(dt); 
    
    handleCollision();
    
    auto drawingOrder = [](const Entity* a, const Entity* b)
    {
        return (a->getHitbox().hitbox.top + a->getHitbox().hitbox .height < b->getHitbox().hitbox.top + b->getHitbox().hitbox.height) ||
        (a->getHitbox().hitbox.top + a->getHitbox().hitbox.height == b->getHitbox().hitbox.top + b->getHitbox().hitbox.height &&
        a->getHitbox().hitbox.left + a->getHitbox().hitbox.width < b->getHitbox().hitbox.left + b->getHitbox().hitbox.width);
    };
    updateQueueEntities();
    sort(entities.begin(),entities.end(),drawingOrder);
    
    return 0; 
}

void TileMap::updateQueueEntities()
{
    // Process entities in the push queue
    for (auto& entity : PushQueueEntities)
    {
        if (entity)
        {
            entities.push_back(entity);
            
        }
    }
    PushQueueEntities.clear();

    // Process entities in the pop queue
    for (auto& entity : PopQueueEntities)
    {
        auto it = std::find(entities.begin(), entities.end(), entity);
        if (it != entities.end())
        {
            std::cerr << "entity pop\n";
            entities.erase(it);
        }
    }
 
    for (auto& entity : PopQueueEntities)
    {
        if (entity)
        {
            delete entity; // Clean up the entity if it was dynamically allocated
        }
    }

    PopQueueEntities.clear();
}
 
void TileMap::handleCollision()
{
    //// entities intersect with entities 
	std::vector<std::pair<Entity*, Entity*>> collision; // To avoid checking the same pair twice
    for(auto& entity : entities)if(entity->movable())
    {
        for (auto& other : entities)if(!other->movable())
        {
            if (isCollide(entity, other))
            {
                other->collide(entity); 
                entity->collide(other); 
            }
        }
	}
	for (int i = 0; i < entities.size(); i++)if (entities[i]->movable())
    {
		for (int j = i + 1; j < entities.size(); j++)if (entities[j]->movable())
        {
            if(isCollide(entities[i],entities[j]))
            {
				entities[i]->collide(entities[j]);
                entities[j]->collide(entities[i]);
            }
		}
    }


    for (auto& entity : entities)if (entity->movable())
    {
        for (auto& other : entities)if (!other->movable())
        {
            if (isCollide(entity, other))
            {
                other->collide(entity);
                entity->collide(other);
            }
        }
    }
    // Handle potential aftermath of collisions here
}
 
