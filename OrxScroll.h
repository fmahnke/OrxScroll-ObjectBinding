#ifndef __ORXSCROLL_H_
#define __ORXSCROLL_H_

//! Includes
#define __NO_SCROLLED__ // Uncomment this define to prevent the embedded editor (ScrollEd) from being compiled
#include "Scroll.h"

namespace OrxScrollConstants
{
    static const orxSTRING heroConfigSection     = "O-Hero";
    static const orxSTRING enemyBugConfigSection = "O-EnemyBug";
}

//! OrxScroll class
class OrxScroll : public Scroll<OrxScroll>
{
public:

private:
    //! Initialize the program
    virtual orxSTATUS Init ();
    //! Callback called every frame
    virtual orxSTATUS Run ();
    //! Exit the program
    virtual void      Exit ();
    virtual void      BindObjects ();
};

#endif // __ORXSCROLL_H_
