#include<Book/AIEnemy.hpp>
#include<Book/Enemy.hpp>
#include<Boss/Zulan.hpp>

AIZulan::AIZulan()
{
	NumShootPerSkill["Zulan Laser"] = 1;
	NumShootPerSkill["Zulan Radial Shot"] = 20;
	NumShootPerSkill["Zulan Shot"] = 10;
	NumShootPerSkill["Zulan Bomb"] = 3;
}

int AIZulan::getNumTimesToShoot(std::string weaponName) const
{
	
	if(NumShootPerSkill.find(weaponName) != NumShootPerSkill.end())
	{
		std::cerr << "Number of times to shoot with weapon " << weaponName << ": " << NumShootPerSkill.at(weaponName) << std::endl;
		return NumShootPerSkill.at(weaponName);
	} else return 5;
}

void AIZulan::update(Enemy* mob, Entity* target, sf::Time dt)
{
	ElapseTime += dt.asSeconds();
	if (mob->inRange(target))
	{
		mob->chase(target, dt);
		if(isShooting)
		{
			if(ElapseTime)
			{
				if(ElapseTime >= spamShootTime)
				{
					mob->shoot(target, dt);
					ElapseTime = 0.0f;
					ShootTime++;
					if(ShootTime >= getNumTimesToShoot(CurrentWeapon))
					{
						std::cerr << "Finished shooting with weapon: " << CurrentWeapon << ' ' << " - " << getNumTimesToShoot(CurrentWeapon) << std::endl;
						isShooting = false;
						ElapseTime = 0.0f;
					}
				}
			}
		} else {
			if (ElapseTime >= NextShootTime)
			{
				isShooting = true;
				ElapseTime = 0.0f;
				ShootTime = 0;
				NumShootPerSkill.clear();
				mob->SwitchWeapon();
				CurrentWeapon = mob->getCurrentWeaponName();
			}
		}
	}
	else
	{
		mob->wander(dt);
	}
}