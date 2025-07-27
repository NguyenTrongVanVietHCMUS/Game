#include<Book/InteractingAnimation/ChestAnimation.hpp>
#include<Object/Object.hpp>
ChestAnimation::ChestAnimation(Object* owner, float scalex, float scaley) :scalex(scalex), scaley(scaley) , InteractingAnimation(owner)
{

	this->owner = owner; // Set the owner of the chest animation
	//if (this->owner == nullptr)abort();
	// Load textures for the chest animation
	if (!body->loadFromFile("Media/Assets/TileSets/Chest/body.png"))
	{
		abort();
	}
	if (!bottom->loadFromFile("Media/Assets/TileSets/Chest/bottom.png"))
	{
		abort();
	}
	left->loadFromFile("Media/Assets/TileSets/Chest/left.png");
	right->loadFromFile("Media/Assets/TileSets/Chest/right.png");
	bodySprite->setTexture(*body);
	bottomSprite->setTexture(*bottom);
	leftSprite->setTexture(*left);
	rightSprite->setTexture(*right);
	bodySprite->setScale(scalex, scaley);
	bottomSprite->setScale(scalex, scaley);
	leftSprite->setScale(scalex, scaley);
	rightSprite->setScale(scalex, scaley);
	distance = 15.0f; // Distance to move the left and right sprites
	bodySprite->setPosition(owner->getPosition());
	bottomSprite->setPosition(owner->getPosition());
	leftSprite->setPosition(sf::Vector2f((owner->getPosition().x + 6) * scalex, (owner->getPosition().y + 3) * scaley));
	rightSprite->setPosition(sf::Vector2f((owner->getPosition().x + 29) * scalex, (owner->getPosition().y + 3) * scaley));
}
ChestAnimation::~ChestAnimation()
{
	delete body;
	delete bottom;
	delete left;
	delete right;
	delete bodySprite;
	delete bottomSprite;
	delete leftSprite;
	delete rightSprite;

	// Destructor logic if needed
	// No dynamic memory allocation, so nothing to clean up
}
void ChestAnimation::activate()
{
	if (state == End)
	{
		state = End;
	}
	else state = Processing;
	//state = Processing; 
}
void ChestAnimation::update(sf::Time dt)
{
	//std::cout << "UPDATING" << std::endl;
	if (state == Processing)
	{
		//std::cout << state << " " << End << std::endl;
		sf::Vector2f L = leftSprite->getPosition();
		L.x -= distance * dt.asSeconds();
		leftSprite->setPosition(L);
		sf::Vector2f R = rightSprite->getPosition();
		R.x += distance * dt.asSeconds();
		rightSprite->setPosition(R);
		if ( rightSprite->getPosition().x-(leftSprite->getPosition().x+left->getSize().x*scalex)> (bottom->getSize().x-8)*scalex )
		{
			state = End;
		}
	}
}
void ChestAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = bottom; // Set the texture for the bottom sprite
	target.draw(*bottomSprite, states);



	states.texture = body; // Set the texture for the body sprite
	target.draw(*bodySprite, states);
	states.texture = left; // Set the texture for the left sprite
	target.draw(*leftSprite, states);
	states.texture = right; // Set the texture for the right sprite
	target.draw(*rightSprite, states);
}
