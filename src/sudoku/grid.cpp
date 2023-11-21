#include "grid.h"
#include "number_factory.h"
#include <memory>
#include <iostream>
#include <numeric>
#include <fstream>
#include <chrono>
#include "application.h"

void Grid::init() {
  SDL_Rect boundingBox;
  boundingBox.w = boundingBoxSize;
  boundingBox.h = boundingBoxSize;

  // assign each square its value
  for (int i = 0; i < gridSize; i++) {
    boundingBox.x = (i % unitSize) * boundingBox.w;
    boundingBox.y = (i / unitSize) * boundingBox.h;
    grids[i] = std::make_shared<GridEntry>(
                 GridEntry(NumberFactory::getInstance()->getNumber(0),
                           i / unitSize,
                           i % unitSize,
                           (i / boxSize) - (boxSize * (i / unitSize)) + (boxSize * (i / boxesSize)),
                           false,
                           boundingBox));
  }
  selected = grids[0];
  std::iota(std::begin(v), std::end(v), 1);
  inited = true;
}

bool Grid::isInited() {
  return inited;
}

void Grid::clearGrid() {
  for (auto e : grids) {
    e->setLocked(false);
    e->setNumber(0);
  }
}

void Grid::load(){
  std::ifstream file{"default.save"};
  for (auto e : grids){
    int n;
    file >> n;
    e->setNumber(n);
    e->setLocked(n != 0);
  }
  file.close();
}

void Grid::save(){
  std::ofstream file{"default.save"};
  for (auto e : grids){
    file << e->getNumber() << " ";
  }
  file << std::endl;
  file.close();
}

void Grid::benchmark(){
  std::ofstream file{"benchmark.log"};
  double minTime = 10000;
  double maxTime = 0;
  double totalTime = 0;
  for (int i = 0; i < 100; i++){
    generates();
    auto startTime = std::chrono::steady_clock::now();
    solve();
    auto time = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(std::chrono::steady_clock::now() - startTime).count();
    file << time << "\n";
    minTime = std::min(minTime, time);
    maxTime = std::max(maxTime, time);
    totalTime += time;
  }
  file << "Time to Solve Sudoku (Run 100 Times):\n";
  file << "Minimum Time: " << minTime << "ms\n";
  file << "Average Time: " << totalTime / 100 << "ms\n";
  file << "Maximum Time: " << maxTime << "ms";
  file << std::endl;
  file.close();
}

Grid* Grid::getInstance() {
  if (!grid) {
    grid = new Grid();
  }
  return grid;
}

int Grid::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= 0 && x < (unitSize * boundingBoxSize) && y >= 0 && y < (unitSize * boundingBoxSize)) {
      if (!grids[((y / boundingBoxSize) * unitSize) + (x / boundingBoxSize)]->isLocked()) { // cannot select locked squares
        selected = grids[((y / boundingBoxSize) * unitSize) + (x / boundingBoxSize)];
      }
    }
  }
  if (event->type == SDL_KEYDOWN) {
    const Uint8* keyStates = SDL_GetKeyboardState(nullptr);
    if (auto tmp = selected.lock()) {
      for (int i = 30; i < 40; i++) {
        if (keyStates[i]) {
          tmp->setNumber((i - 29) % 10);
        }
      }
    }
  }
  return 0; // case none
}

void Grid::render() {
  SDL_Renderer* renderer = Application::getInstance()->getRenderer();
  for (auto e : grids) {
    e->render();
  }
  if (auto tmp = selected.lock()) {
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 125);
    SDL_RenderFillRect(renderer, tmp->getBoundingBox()); // green overlay for selected square
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  }
  for (int i = 1; i < (unitSize + 1); i++) {
    if (i % boxSize != 0) {
      for (int j = 0; j < (unitSize * 2); j++) {
        if (j % 2 == 0) { // dotted lines
          SDL_RenderDrawLine(renderer, i * boundingBoxSize, ((j * boundingBoxSize) / 2) + (boundingBoxSize / 4), i * boundingBoxSize, ((j * boundingBoxSize) / 2) + ((boundingBoxSize * 3) / 4));
          SDL_RenderDrawLine(renderer, ((j * boundingBoxSize) / 2) + (boundingBoxSize / 4), i * boundingBoxSize, ((j * boundingBoxSize) / 2) + ((boundingBoxSize * 3) / 4), i * boundingBoxSize);
        }
      }
    } else { // filled lines
      SDL_RenderDrawLine(renderer, i * boundingBoxSize, 0, i * boundingBoxSize, (unitSize * boundingBoxSize));
      SDL_RenderDrawLine(renderer, 0, i * boundingBoxSize, (unitSize * boundingBoxSize), i * boundingBoxSize);
    }
  }
}

bool Grid::isConflicts(int n) {
  int row = grids[n]->getRow();
  int column = grids[n]->getColumn();
  int box = grids[n]->getBox();
  std::vector<int> counterRow(unitSize + 1, 0);
  std::vector<int> counterColumn(unitSize + 1, 0);
  std::vector<int> counterBox(unitSize + 1, 0);
  for (int i = 0; i < unitSize; i++) { // if more than one occurrence, then not valid Sudoku
    int r = grids[i + (row * unitSize)]->getNumber();
    int c = grids[(i * unitSize) + column]->getNumber();
    int b = grids[(i % boxSize) + (unitSize * (i / boxSize)) + (boxSize * (box % boxSize)) + (boxesSize * (box / boxSize))]->getNumber();
    if (((++counterRow[r] == 2) && (r != 0))
        || ((++counterColumn[c] == 2) && (c != 0))
        || ((++counterBox[b] == 2) && (b != 0))) {
      return true;
    }
  }
  return false; // valid Sudoku
}

bool Grid::solve(const int n) {
  if (n == gridSize) { // end of the grid, all squares given numbers
    return true;
  }
  if (!grids[n]->isLocked()) {
    std::shuffle(std::begin(v), std::end(v), rng);
    auto tempv = v;
    for (int i : tempv) { // try all possible numbers
      grids[n]->setNumber(i);
      if (!isConflicts(n)) {
        if (solve(n + 1)) { // solve next
          grids[n]->setLocked(true);
          return true;
        }
      }
    }
  } else {
    return solve(n + 1); // solve next
  }
  grids[n]->setNumber(0); // backtrack
  return false;
}

bool Grid::isNotUnique(const int n, int* counterSolutions) {
  if (n == gridSize) { // end of the grid
    return ++*counterSolutions == 2;
  }
  if (!grids[n]->isLocked()) {
    for (int i = 1; i <= unitSize; i++) { // try all possible numbers
      grids[n]->setNumber(i);
      if (!isConflicts(n)) {
        if (isNotUnique(n + 1, counterSolutions)) { // solve next
          grids[n]->setNumber(0);
          return true;
        }
      }
    }
  } else {
    return isNotUnique(n + 1, counterSolutions); // solve next
  }
  grids[n]->setNumber(0); // backtrack
  return false;
}

bool Grid::generates() {
  clearGrid();
  solve();
  std::vector<int> w(gridSize);
  std::iota(std::begin(w), std::end(w), 0);
  std::shuffle(std::begin(w), std::end(w), rng);
  return generates(0, w);
}

bool Grid::generates(const int depth, const std::vector<int>& w) {
  if (depth == 50) {
    return true;
  }
  int numbersToRemove = 0;
  for (int i : w) { // try all possible squares
    int previousNumber = grids[i]->getNumber();
    numbersToRemove++;
    grids[i]->setLocked(false);
    grids[i]->setNumber(0);
    if (!isNotUnique()) {
      std::vector<int> tempw(w.begin() + numbersToRemove, w.end());
      std::shuffle(std::begin(tempw), std::end(tempw), rng);
      return generates(depth + 1, tempw);
    }
    grids[i]->setNumber(previousNumber);
    grids[i]->setLocked(true);
  }
  return false;
}

Grid* Grid::grid = nullptr;
