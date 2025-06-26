#pragma once 
#include<Book/Utility.hpp>
#include<Book/Entity.hpp>

class Collision
{
    public : 
        void handleCollision(Entity* entity1, Entity* entity2)
        {
            // Handle collision logic between two entities
            // This is a placeholder function and should be implemented with actual collision handling logic
            if (entity1->getHitbox().hitbox.intersects(entity2->getHitbox().hitbox))
            {
                // Collision detected, handle accordingly
                entity1->collide(entity2);
                entity2->collide(entity1);
            }
        }
};