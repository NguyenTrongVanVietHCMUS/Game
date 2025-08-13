#pragma once 
#include <Book/Utility.hpp>
#include<Control/Hitbox.hpp>
#include<memory>

class Projectile2;
class Entity:public sf::Drawable, public std::enable_shared_from_this<Entity>
{

public :
	typedef std::unique_ptr<Entity> Ptr; // Smart pointer for managing Entity objects
    std::vector<Ptr>children;
    
    enum class Type
    {
		EnemyProjectile, 
        AllyProjectile,
        Projectile,
        Enemy, 
        Ally, 
        Entity,
        Weapon, 
        Object
    };
    Type type; 
    Entity(std::string name, sf::Vector2f position); 
    Entity(std::string name, sf::Vector2f position, Hitbox hitbox); 
    virtual ~Entity();

public :

    
    std::string name ; 
    sf::Vector2f position; // Position of the entity
    Hitbox hitbox ;  
    Hitbox bodyHitbox ; 
    virtual bool handleEvent(const sf::Event& event, sf::RenderWindow* window);
    virtual bool update(sf::Time dt)  ;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states)const ; // Draw the entity
    void attachChild(Ptr child); 
    virtual Hitbox getHitbox()const ; // Get the hitbox of the entity
    virtual Hitbox getBodyHitbox() const; 
public :
    // utility functions
    void updateHitboxOnPosition();
    bool inRange(const Entity* other)const;
public: 
    virtual float getRange()const; 
public : 
    bool movable()const; 
    // Getters and Setters
    virtual sf::Vector2f getPosition() const { 
        // std::cerr << "Get position : " << position.x << ", " << position.y << std::endl; 
        return position;
     }
    sf::Vector2f getDirection() const { return sf::Vector2f(0.45f, 0.45f); } // Placeholder for direction ; 
    virtual void collide(const Entity* other) ;
	virtual void bodyCollide(const Entity* other);
    bool isCollide(const Entity* other)const;
    bool isBodyCollide(const Entity* other)const;
    bool operator<(const Entity& other)const{
        return getHitbox().hitbox.top + getHitbox().hitbox.height < other.getHitbox().hitbox.top + other.getHitbox().hitbox.height||(
            getHitbox().hitbox.top + getHitbox().hitbox.height == other.getHitbox().hitbox.top + other.getHitbox().hitbox.height &&
            getHitbox().hitbox.left + getHitbox().hitbox.width < other.getHitbox().hitbox.left + other.getHitbox().hitbox.width
        );
    }
    virtual bool passAble()const; 
    virtual bool isNear(Entity* other)const; 
    virtual sf::Vector2f getHandPosition()const; 


public:
    // extra method 
    virtual void takeDamage(int damage) {}; 
    virtual void knockBack(sf::Vector2f force) {};
    virtual void knockBack(const Projectile2* projectile, float Force = 1000.0f) {};
};