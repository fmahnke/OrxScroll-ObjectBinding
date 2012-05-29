/**
 * @file Hero.cpp
 * @date 2012-05-24
 *
 */
#include "Hero.h"

void Hero::OnCreate ()
{
    // Get movement speed from config value
    m_movementSpeed = orxConfig_GetFloat ("MovementSpeed");
}

void Hero::OnDelete ()
{
    // Do nothing when deleted
}

void Hero::Update(const orxCLOCK_INFO &_rstInfo)
{
    // Always initialize thy variables
    orxVECTOR speed = orxVECTOR_0;

    if (orxInput_IsActive ("MoveLeft"))
    {
	speed.fX = -m_movementSpeed;
    }
    else if (orxInput_IsActive ("MoveUp"))
    {
	speed.fY = -m_movementSpeed;
    }
    else if (orxInput_IsActive ("MoveRight"))
    {
	speed.fX = m_movementSpeed;
    }
    else if (orxInput_IsActive ("MoveDown"))
    {
	speed.fY = m_movementSpeed;
    }
    SetSpeed (speed, false);
}

orxBOOL Hero::OnCollide(ScrollObject *_poCollider,
	      const orxSTRING _zPartName,
	      const orxVECTOR &_rvPosition,
	      const orxVECTOR &_rvNormal)
{
    // Add flash effect
    AddFX ("FX-Flash");

    return true;
}