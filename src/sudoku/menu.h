#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include "screen.h"

/** \brief The object representing the main menu screen.
 */

class Menu : public Screen {
 public:

  /** \brief Handles any user input on this screen.
   *
   * \param event Is the user input event to be handled.
   */

  void handleEvent(SDL_Event* event);

  static Menu* getInstance();
 private:
  Menu(std::initializer_list<GUIComponent*> c) : Screen{c} {}

  /** \brief The GUI actions that can be taken by the user on this screen, in this case buttons that can be clicked.
   */

  enum class Action {continueGame, loadGame, settings, newGame, eightQueens, quit};

  static Menu* menu;
};

#endif // MENU_H_INCLUDED
