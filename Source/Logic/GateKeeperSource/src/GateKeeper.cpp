/********************************************************************************
**	SOURCE FILE:	GateKeeper.cpp -  	GateKeeper class implementation. Parent class
**                                    for the enemies.
**
**	PROGRAM:	Term_Project
**
**	DATE: 		February 15, 2015
**
**
**	DESIGNER: 	Filip Gutica A00781910
**
**	PROGRAMMER: Filip Gutica A00781910
**
***********************************************************************************/
#include "GateKeeper.h"
#include "../../Event.h"
#include "../../Entities/ServerEnemyController.h"
#include <typeinfo>
#include <iostream>

using namespace Manager;

// bug fix by Sanders Lee
GateKeeper::GateKeeper(SGO &sprite, Marx::Map* map, float x, float y, Marx::Controller* ctrl, float h = 1.0, float w = 1.0) :
  VEntity(sprite, map, x, y, ctrl, h, w)
//  _ctrl(ctrl)
  {
    _range = 1;
    _health = 100;
    _type = 1;
    _attack = 1;
    _attackSpeed = 1;
    _movementSpeed = 1;
    _incombat = false;
    _cooldown = 1;
    _xPos = x;
    _yPos = y;
    _xSpeed = 0.09;
    _ySpeed = 0.09;
    movingLeft = movingRight = movingUp = movingDown = _moving = false;

    // sound set loaded should be determined by enemy type
    if (_type == 1) // if (_type == BEE )
    {
        //grassWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
    	//stoneWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Enemies/bee/bee_travel_01.ogg"));
        grassWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_stone.ogg"));
    	stoneWalkSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_stone.ogg"));
        hurtSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_stone.ogg"));
    	attackSound = SoundManager::store(SoundManager::load("Assets/Sound/Player/Run/run_stone.ogg"));
    }
  };

GateKeeper::~GateKeeper()
{

}

/***
-- PROGRAMMER:  ???
--				Sanders Lee (Debugged synchronization problem across clients)
***/
void GateKeeper::onUpdate(float deltaTime)
{


//  std::cout << "GateKeeper.cpp ON UPDATE." << std::endl;

std::vector<Marx::Event*>* eventQueue = getController()->getEvents();
for( std::vector< Marx::Event*>::iterator it = eventQueue->begin()
  ; it != eventQueue->end()
  ; ++it )
{
    static bool soundActive = false;
    static BlockZone steppedTile = GRASS;

  // switch on type
	switch((*it)->type)
	{
		case ::Marx::MOVE:
			MoveEvent* ev = (MoveEvent*) (*it);
      int xDir = ev->getXDir();
      int yDir = ev->getYDir();

      Entity::aMove(ev->getX(), ev->getY(), false);

      if (yDir < 0)
      {
        newYSpeed = -_ySpeed;
      }
      else
      {
        newYSpeed = _ySpeed;
      }

      if (xDir > 0)
      {
        newXSpeed = _xSpeed;
      }
      else
      {
        newXSpeed = -_xSpeed;
      }

      if (xDir == 0)
        newXSpeed = 0;

      if (yDir == 0)
        newYSpeed = 0;

      //old code - replaced with the if-else block above
      //movingLeft = (xDir < 0);
      //movingRight = (xDir > 0);
      //movingUp = (yDir < 0);
      //movingDown = (yDir > 0);
			break;
	}

    /***
	*
	* Code for playing sounds
	*
	***/
	// Sounds for walking:
	// first get the tile type we're walking on
	Cell* footstepTile = *getCell().begin();
	sf::Vector2f soundPos(left, top);
    //*
	if (footstepTile->getTileId() >= GRASS_TL && footstepTile->getTileId() <= GRASS_BR)
	{
		// we need the extra soundActive boolean to make sure we're not playing a new
		// sound when there's already a walking sound active for our vessel
		if (((newXSpeed != 0 || newYSpeed != 0) && !soundActive) ||
			(soundActive && steppedTile != GRASS))
		{
			footstep.stop();
			footstep = SoundManager::play(grassWalkSound, soundPos);
			footstep.setLoop(true);
			footstep.play();
			soundActive = true;
			steppedTile = GRASS;
		}
	}
	else if (footstepTile->getTileId() >= STONE_TL && footstepTile->getTileId() <= ARBITER_BR)
	{
		if (((newXSpeed != 0 || newYSpeed != 0) && !soundActive) ||
			(soundActive && steppedTile != STONE))
		{
			footstep.stop();
			footstep = SoundManager::play(stoneWalkSound, soundPos);
			footstep.setLoop(true);
			footstep.play();
			soundActive = true;
			steppedTile = STONE;
		}
	}
    // stop all sounds of walking if travelling speed is (0, 0)
	if ((newXSpeed == 0 && newYSpeed == 0) && soundActive)
	{
		footstep.stop();
		soundActive = false;
	}//*/

}
getController()->clearEvents();


Entity::rMove(newXSpeed, newYSpeed,false);


}

bool GateKeeper::isMoving()
{
  return (movingLeft || movingRight || movingUp || movingDown);
}

void GateKeeper::detectPlayers()
{

}

void GateKeeper::enterCombat()
{

}

void GateKeeper::leaveCombat()
{

}

bool GateKeeper::inCombatRange()
{
  return true;
}

void GateKeeper::setRange(int r)
{

}

void GateKeeper::setHealth(int h)
{

}

void GateKeeper::setAttack(int as)
{

}

void GateKeeper::setAttackSpeed(int as)
{

}

void GateKeeper::setMovementSPed(int ms)
{

}

void GateKeeper::setTarget(/*Player*/)
{

}

void GateKeeper::setCooldown(/*Timer*/)
{

}

void GateKeeper::setPosition(float x, float y)
{

}

void GateKeeper::setXSpeed(float x)
{

}

void GateKeeper::setYSpeed(float y)
{

}

int GateKeeper::getRange()
{
  return _range;
}

int GateKeeper::getHealth()
{
  return _health;
}

int GateKeeper::getAttack()
{
  return _attack;
}

int GateKeeper::getAttackSpeed()
{
  return _attackSpeed;
}

int GateKeeper::getMovementSpeed()
{
  return _movementSpeed;
}
//virtual Vessel getTarget();
time_t GateKeeper::getCooldown()
{
  return _cooldown;
}

void GateKeeper::turn()
{

}

void GateKeeper::onCreate()
{

}

void GateKeeper::onDestroy()
{

}

bool GateKeeper::operator==(const VEntity&)
{
  return true;
}

/*------------------------------------------------------------------------------------------------------------------
-- FUNCTION: getEntity
--
-- DATE:
--
-- REVISIONS: (Date and Description)
--
-- DESIGNER:	Calvin Rempel
--
-- PROGRAMMER:	Calvin Rempel
--
-- INTERFACE: Entity *getEntity()
--
-- RETURNS: The Entity associated with the Creature
--
-- NOTES:
-- This function provides a method for retrieving the Entity from the Creature.
----------------------------------------------------------------------------------------------------------------------*/
Entity *GateKeeper::getEntity()
{
    return this;
}
