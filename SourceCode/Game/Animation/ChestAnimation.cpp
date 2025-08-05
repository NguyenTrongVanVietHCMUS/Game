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

ChestAnimation::ChestAnimation(Object* owner, float scalex, float scaley, std::shared_ptr<Weapon2> items) :scalex(scalex), scaley(scaley) , InteractingAnimation(owner), items(items)
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
	this->items->position = sf::Vector2f((owner->getPosition().x + 18) * scalex, (owner->getPosition().y + 10) * scaley);
	std::cerr << this->items->name << " position: " << this->items->position.x << ", " << this->items->position.y << std::endl;
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
	delete itemsSprite; // Clean up the items sprite if it was created
	// Destructor logic if needed
	// No dynamic memory allocation, so nothing to clean up
}
void ChestAnimation::activate()
{
	if (state == Begin)
	{
		state = Activating;
	}
	else if(state==Activating)
	{
		//state = Activating; 
	}
	else if(state == Deactivating )
	{
		state = Activating; 
	}
	else if(state == End)
	{
		// state = End ;
	}
	//state = Processing; 
}
void ChestAnimation::deactivate()
{
	if (state == Begin)
	{
		state = Begin;
	}
	else if (state == Activating)
	{
		state = Activating;
	}
	else if (state == Deactivating)
	{
		state = Deactivating;
	}
	else if (state == End)
	{
		state = Deactivating; 
	}
}
void ChestAnimation::update(sf::Time dt)
{
	//std::cout << "UPDATING" << std::endl;
	if (state == Activating)
	{
		//std::cout << state << " " << End << std::endl;
		sf::Vector2f L = leftSprite->getPosition();
		L.x -= distance * dt.asSeconds();
		sf::Vector2f R = rightSprite->getPosition();
		R.x += distance * dt.asSeconds();
		if ( R.x-(L.x+left->getSize().x*scalex)> (bottom->getSize().x-8)*scalex )
		{
			state = End;
		}
		leftSprite->setPosition(L);
		rightSprite->setPosition(R);

	}
	else if (state == Deactivating)
	{
		sf::Vector2f L = leftSprite->getPosition();
		L.x += distance * dt.asSeconds();
		sf::Vector2f R = rightSprite->getPosition();
		R.x -= distance * dt.asSeconds();
		if (rightSprite->getPosition().x - (leftSprite->getPosition().x + left->getSize().x * scalex)<0)
		{
			state = Begin; 
		}
		else
		{ 
			leftSprite->setPosition(L);
			rightSprite->setPosition(R);
		}
	}
}
void ChestAnimation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.texture = bottom; // Set the texture for the bottom sprite
	target.draw(*bottomSprite, states);

	if(state==End&&items){
		states.texture = items->getTexture(); // Set the texture for the items sprite
		target.draw(*itemsSprite, states);
	}

	states.texture = body; // Set the texture for the body sprite
	target.draw(*bodySprite, states);
	states.texture = left; // Set the texture for the left sprite
	target.draw(*leftSprite, states);
	states.texture = right; // Set the texture for the right sprite
	target.draw(*rightSprite, states);
}

void ChestAnimation::setItems(std::shared_ptr<Weapon2> newItems)
{
	if (newItems) {
		items = newItems; // Update the items in the chest
		
		items->position = sf::Vector2f((owner->getPosition().x) * scalex, (owner->getPosition().y) * scaley);
		if (!itemsSprite) {
			itemsSprite = new sf::Sprite();
			itemsSprite->setTexture(*items->getTexture());
			itemsSprite->setPosition(items->position);
			itemsSprite->setScale(0.4, 0.4);
		} else {
			itemsSprite->setTexture(*items->getTexture());
			itemsSprite->setPosition(items->position);
			itemsSprite->setScale(0.4, 0.4);
		}
	} else {
		items = nullptr;
		if (itemsSprite) {
			delete itemsSprite; // Clean up the items sprite if it was created
			itemsSprite = nullptr;
		}
	}
}