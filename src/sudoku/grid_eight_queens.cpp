#include "grid_eight_queens.h"
#include "number_factory.h"
#include <memory>
#include "application.h"

void GridEightQueens::load() {
  SDL_Rect boundingBox;
  boundingBox.w = 100;
  boundingBox.h = 100;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      boundingBox.x = j * 100;
      boundingBox.y = i * 100;
      grids[i][j] = std::make_shared<GridEntry>(GridEntry(NumberFactory::getInstance()->getNumber(0), 0, 0, 0, false, boundingBox));
    }
  }
}

GridEightQueens* GridEightQueens::getInstance() {
  if (!gridEightQueens) {
    gridEightQueens = new GridEightQueens();
  }
  return gridEightQueens;
}

void GridEightQueens::render() {
  SDL_Renderer* renderer = Application::getInstance()->getRenderer();
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      grids[i][j]->render();
    }
  }
  for (int i = 1; i < 8; i++) {
    SDL_RenderDrawLine(renderer, i * 100, 0, i * 100, 800);
    SDL_RenderDrawLine(renderer, 0, i * 100, 800, i * 100);
  }
}

bool GridEightQueens::isConflicts() {
  int counterRow[2];
  int counterColumn[2];
  int counterDiagonal[2];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 2; j++) {
      counterRow[j] = 0;
      counterColumn[j] = 0;
    }
    for (int j = 0; j < 8; j++) {
      if ((++counterRow[grids[i][j]->getNumber()] == 2) &&
          (grids[i][j]->getNumber() != 0)) {
        return true;
      } else if ((++counterColumn[grids[j][i]->getNumber()] == 2) &&
                 (grids[j][i]->getNumber() != 0)) {
        return true;
      }
    }
  }
  for (int i = 0; i < 7; i++) {
    counterDiagonal[0] = 0;
    counterDiagonal[1] = 0;
    for (int j = 0; j < (8 - i); j++) {
      if ((++counterDiagonal[grids[j][i + j]->getNumber()] == 2) &&
          (grids[j][i + j]->getNumber() != 0)) {
        return true;
      }
    }
    counterDiagonal[0] = 0;
    counterDiagonal[1] = 0;
    for (int j = 0; j < (8 - i); j++) {
      if ((++counterDiagonal[grids[7 - j][i + j]->getNumber()] == 2) &&
          (grids[7 - j][i + j]->getNumber() != 0)) {
        return true;
      }
    }
  }
  for (int i = 1; i < 7; i++) {
    counterDiagonal[0] = 0;
    counterDiagonal[1] = 0;
    for (int j = 0; j < (i + 1); j++) {
      if ((++counterDiagonal[grids[i - j][j]->getNumber()] == 2) &&
          (grids[i - j][j]->getNumber() != 0)) {
        return true;
      }
    }
    counterDiagonal[0] = 0;
    counterDiagonal[1] = 0;
    for (int j = 0; j < (8 - i); j++) {
      if ((++counterDiagonal[grids[i + j][j]->getNumber()] == 2) &&
          (grids[i + j][j]->getNumber() != 0)) {
        return true;
      }
    }
  }
  return false;
}

bool GridEightQueens::solve(const int n, const int counterQueens) {
  if (n == 64 && counterQueens == 8) { // end of the chessboard, all queens have been placed in valid positions
    return true;
  } else if (n == 64) { // end of the chessboard, could not place all queens in valid positions
    return false;
  }
  grids[n / 8][n % 8]->setNumber(1); // place a queen
  if (!isConflicts()) {
    if (solve(n + 1, counterQueens + 1)) {
      return true;
    } else {
      if (grids[n / 8][n % 8]->getNumber()) {
        grids[n / 8][n % 8]->setNumber(0);
        return solve(n + 1, counterQueens);
      } else {
        return false;
      }
    }
  } else {
    grids[n / 8][n % 8]->setNumber(0);
    return solve(n + 1, counterQueens);
  }
}

GridEightQueens* GridEightQueens::gridEightQueens = nullptr;
