/**
 * @file EnemyBug.cpp
 * @date 2012-05-24
 *
 */
#include "EnemyBug.h"

void EnemyBug::OnCreate ()
{
    // Set initial movement direction
    m_direction = SOUTH;
    // Get movement speed from config value 
    m_movementSpeed = orxConfig_GetFloat ("MovementSpeed");
    // Get direction change interval from config value
    m_directionChangeInterval = orxConfig_GetFloat ("DirectionChangeInterval");
}

void EnemyBug::OnDelete ()
{
    // Do nothing when deleted
}

void EnemyBug::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Always initialize thy variables
    orxVECTOR speed = orxVECTOR_0;

    // Set rotation, flip, and speed based on the object's
    // current direction of movement.
    switch (m_direction)
    {
    orxBOOL flipX, flipY;
    case NORTH:
	speed.fY = -m_movementSpeed;
	SetRotation (270 * orxMATH_KF_DEG_TO_RAD);
	SetFlip (false, false);
	break;
    case SOUTH:
	speed.fY = m_movementSpeed;
	SetRotation (90 * orxMATH_KF_DEG_TO_RAD);
	SetFlip (false, false);
	break;
    case WEST:
	speed.fX = -m_movementSpeed;
	SetRotation (0 * orxMATH_KF_DEG_TO_RAD);
	SetFlip (true, false);
	GetFlip (flipX, flipY);
	break;
    case EAST:
	speed.fX = m_movementSpeed;
	SetRotation (0);
	SetFlip (false, false);
	GetFlip (flipX, flipY);
	break;
    default:
	orxASSERT (false);
    }

    // Update object's speed of movement
    SetSpeed (speed);

    // Time since direction change exceeds interval of direction change?
    if ((m_timeSinceDirectionChange += _rstInfo.fDT) >= m_directionChangeInterval)
    {
	// Reset time
	m_timeSinceDirectionChange = 0;
	// Pick random number between bounds of Direction enum
	orxU32 randomNum = orxMath_GetRandomU32 (0, highDirection);
	// Update object's direction of movement
	m_direction = static_cast<Direction> (randomNum);
    }
}