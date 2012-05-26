/**
 * @file EnemyBug.h
 * @date 2012-05-24
 *
 */

#include "OrxScroll.h"

enum      Direction { NORTH, SOUTH, EAST, WEST };
const int highDirection = 3;

class EnemyBug : public ScrollObject
{
public:
    EnemyBug ()
    {
	int a = 0;
    };
    virtual ~EnemyBug ()
    {
	int a = 0;
    };
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
    float       m_movementSpeed;
    //! Time since change of direction
    float       m_timeSinceDirectionChange;
    //! Time interval between direction changes
    float       m_directionChangeInterval;
};