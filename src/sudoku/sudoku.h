#ifndef SUDOKU_H_INCLUDED
#define SUDOKU_H_INCLUDED

#include "screen.h"

/** \brief The object representing the sudoku screen.
 */

class Sudoku : public Screen {
 public:

  /** \brief Handles any user input on this screen.
   *
   * \param event Is the user input event to be handled.
   */

  void handleEvent(SDL_Event* event);

  static Sudoku* getInstance();
 private:
  Sudoku(std::initializer_list<GUIComponent*> c) : Screen{c} {}

  /** \brief The GUI actions that can be taken by the user on this screen, in this case buttons that can be clicked and the sudoku grid that can be interacted with.
   */

  enum class Action {none, backMenu, solve, generateSudoku, load, save, benchmark};

  static Sudoku* sudoku;
};

#endif // SUDOKU_H_INCLUDED
