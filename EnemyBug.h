/**
 * @file EnemyBug.h
 * @date 2012-05-24
 *
 */

#include "OrxScroll.h"

enum         Direction { NORTH, SOUTH, EAST, WEST };
const orxU32 highDirection = 3;

class EnemyBug : public ScrollObject
{
private:
    //! Called on object creation.
    virtual void OnCreate ();
    //! Called on object deletion.
    virtual void OnDelete ();
    //! Called on clock update
    virtual void Update (const orxCLOCK_INFO &_rstInfo);

    //! Direction of movement
    Direction   m_direction;
    //! Speed of movement
    orxFLOAT	m_movementSpeed;
    //! Time since change of direction
    orxFLOAT    m_timeSinceDirectionChange;
    //! Time interval between direction changes
    orxFLOAT    m_directionChangeInterval;
};