#ifndef GRID_ENTRY_H_INCLUDED
#define GRID_ENTRY_H_INCLUDED
#include <SDL.h>
#include "number.h"

/** \brief An entry represents a square on the grid or chessboard, it handles rendering of the squares value, as well as any overlays that might be rendered on this square.
 */

class GridEntry {
 public:
  GridEntry(Number* n, int r, int c, int b, bool l, SDL_Rect bB) : number{n}, row{r}, column{c}, box{b}, locked{l}, boundingBox{bB} {}

  bool operator < (const GridEntry &gridEntry) {
    return countPossibleValues < gridEntry.countPossibleValues;
  }

  /** \brief Renders the squares value and if it is a locked square a grey overlay.
   */

  void render();

  void setNumber(const int n);

  int getNumber();

  int getRow() {
    return row;
  }

  int getColumn() {
    return column;
  }

  int getBox() {
    return box;
  }

  void setLocked(const bool l);

  bool isLocked();

  SDL_Rect* getBoundingBox();

 private:
  Number* number; // the number in this square
  int row; // this squares row
  int column; // this squares column
  int box; // this squares box
  bool locked; // if the square is an initial value
  SDL_Rect boundingBox; // the squares box
  int countPossibleValues; // the amount of possible numbers this square can be in respect to the constraints on this square
};

#endif // GRID_ENTRY_H_INCLUDED
