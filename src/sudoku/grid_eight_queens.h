#ifndef GRID_EIGHT_QUEENS_H_INCLUDED
#define GRID_EIGHT_QUEENS_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "grid_entry.h"
#include <memory>
#include "gui_component.h"

/** \brief Object that represent the chessboard for eight queens.
 */

class GridEightQueens : public GUIComponent {
 public:
  static GridEightQueens* getInstance();

  /** \brief Loads the initial state of the chessboard.
   */

  void load();

  /** \brief Renders the chessboard with Queens as ones.
   */

  void render();

  /** \brief Tests if any Queens can attack each other.
   * \return True if a Queen can attack another Queen.
   *
   */

  bool isConflicts();

  /** \brief Attempts to solve the eight queens problem, by placing eight queens on a chessboard, so that no queen can attack another queen, using a backtracking, recursive search.
   *
   * \param n Is the next index, which refers to the next square on the chessboard.
   * \param counterQueens Is the amount of Queens currently placed on the chessboard.
   * \return True if the eight queens problem has been solved, false if it cannot.
   *
   */

  bool solve(const int n, const int counterQueens);

 private:
  GridEightQueens() {}

  static GridEightQueens* gridEightQueens;
  std::shared_ptr<GridEntry> grids[8][8]; // the chessboard
};

#endif // GRID_EIGHT_QUEENS_H_INCLUDED
