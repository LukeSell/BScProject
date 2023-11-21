#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "grid_entry.h"
#include <memory>
#include <algorithm>
#include <random>
#include "gui_component.h"

/** \brief Object that represents the Sudoku grid.
 */

class Grid : public GUIComponent {
 public:
  static Grid* getInstance();

  /** \brief Initializes the Sudoku grid into the relevant data structure.
   */

  void init();

  bool isInited();

  /** \brief Sets all squares on the grid as empty.
   */

  void clearGrid();

  /** \brief Handles events to select squares and modify them.
   *
   * \param event Is the user event to be handled.
   */

  int handleEvent(SDL_Event* event);

  /** \brief Renders the grid, which is composed of entries, the selected square and the lines between squares.
   */

  void render();

  /** \brief Tests if the grid is valid when compared against the constraints of Sudoku.
   * \param n Is the index of the square to check the constraints of.
   * \return True if the constraints have been invalidated, otherwise false if the grid is valid.
   *
   */

  bool isConflicts(int n);

  /** \brief Attempts to solve the Sudoku, using a backtracking, recursive search.
   *
   * \param n Is the next index, which refers to the next square in the grid.
   * \return True if the Sudoku has been solved, false if it cannot be solved.
   *
   */

  bool solve(const int n = 0);

  /** \brief Tests if the current grid has more than one solution.
   *
   * \param n Is the next index, which refers to the next square in the grid.
   * \param counterSolutions Counts the number of solutions found so far.
   * \return True if the grid has more than one solution, false if the grid has a unique solution.
   */

  bool isNotUnique(const int n, int* counterSolutions);

  /** \brief Calls the recursive method with arguments.
   *
   * \return True if the grid has more than one solution, false if the grid has a unique solution.
   */

  bool isNotUnique() {
    int p = 0;
    return isNotUnique(0, &p);
  }

  /** \brief Generates a new Sudoku by randomly solving an empty grid and then randomly removing numbers while keeping the solution to the grid unique.
   *
   * \param depth Is the current amount of squares made empty.
   * \param w Is the indexes of squares to try and make empty.
   * \return True if a Sudoku of depth 50 could be generated, false if not.
   */

  bool generates(const int depth, const std::vector<int>& w);

  /** \brief Readies the grid for generating by clearing it and randomly solving it, before passing the arguments to the recursive generating method.
   *
   * \return True if a Sudoku of depth 50 could be generated, false if not.
   */

  bool generates();

  /** \brief Loads a Sudoku grid from a save file.
   */

  void load();

  /** \brief Saves a Sudoku grid to a save file.
   */

  void save();

  /** \brief Benchmarks the Sudoku solving algorithm and saves the times to a log file.
   */

  void benchmark();

 private:
  Grid() : boxSize{3}, unitSize{boxSize * boxSize}, boxesSize{unitSize * boxSize}, gridSize{boxesSize * boxSize}, boundingBoxSize{1000 / unitSize}, v(unitSize), rd{}, rng{rd()}, inited{false}, grids(gridSize), selected{} {}

  static Grid* grid;
  int boxSize; // the height and width of a box in squares
  int unitSize; // the amount of squares in a row or column or box
  int boxesSize; // the amount of squares in a row or column of boxes
  int gridSize; // the amount of squares in the grid
  int boundingBoxSize; // the size of a square on the grid
  std::vector<int> v; // the possible numbers that can go in a square to form a valid Sudoku grid
  std::random_device rd;
  std::default_random_engine rng;
  bool inited; // if a sudoku grid has been loaded
  std::vector<std::shared_ptr<GridEntry>> grids; // the sudoku grid
  std::weak_ptr<GridEntry> selected; // the selected square
};

#endif // GRID_H_INCLUDED
