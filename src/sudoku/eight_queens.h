#ifndef EIGHT_QUEENS_H_INCLUDED
#define EIGHT_QUEENS_H_INCLUDED

#include "screen.h"

/** \brief The object representing the eight queens screen.
 */

class EightQueens : public Screen {
 public:

   /** \brief Handles any user input on this screen.
    *
    * \param event Is the user input event to be handled.
    */

  void handleEvent(SDL_Event* event);

  static EightQueens* getInstance();
 private:
  EightQueens(std::initializer_list<GUIComponent*> c) : Screen{c} {}

  /** \brief The GUI actions that can be taken by the user on this screen, in this case buttons that can be clicked.
   */

  enum class Action {none, backMenu, solve};

  static EightQueens* eightQueens;
};

#endif // EIGHT_QUEENS_H_INCLUDED
