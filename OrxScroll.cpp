//! Includes
#define __SCROLL_IMPL__
#include "OrxScroll.h"
#undef __SCROLL_IMPL__

#include <time.h>

#include "EnemyBug.h"
#include "Hero.h"

orxSTATUS OrxScroll::Init ()
{
    orxSTATUS result = orxSTATUS_SUCCESS;

    // Get current time since Epoch
    orxS32 seconds = static_cast<orxS32> (time (NULL));
    // Initialize random number generator with current time
    orxMath_InitRandom (seconds);

    CreateObject (OrxScrollConstants::heroConfigSection);

    for (orxU32 i = 0; i < 5; i++)
    {
	CreateObject (OrxScrollConstants::enemyBugConfigSection);
    }
    return result;
}

orxSTATUS OrxScroll::Run ()
{
    orxSTATUS result = orxSTATUS_SUCCESS;

    return result;
}

void OrxScroll::Exit ()
{
}

void OrxScroll::BindObjects ()
{
    ScrollBindObject<EnemyBug> (OrxScrollConstants::enemyBugConfigSection);
    ScrollBindObject<Hero>     (OrxScrollConstants::heroConfigSection);
}

int main (int argc, char **argv)
{
  // Executes game
  OrxScroll::GetInstance ().Execute (argc, argv);

  // Done!
  return EXIT_SUCCESS;
}

#ifdef __orxWINDOWS__

#include "windows.h"

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
  // Executes game
  OrxScroll::GetInstance ().Execute ();

  // Done!
  return EXIT_SUCCESS;
}

#endif // __orxWINDOWS__
