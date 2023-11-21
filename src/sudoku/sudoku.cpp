#include "sudoku.h"
#include "button.h"
#include "application.h"
#include "menu.h"
#include "grid.h"

void Sudoku::handleEvent(SDL_Event* event) {
  for (auto component : getComponents()) {
    switch (static_cast<Action>(component->handleEvent(event))) {
    case Action::backMenu:
      Application::getInstance()->setScreen(Menu::getInstance());
      break;
    case Action::solve:
      Grid::getInstance()->solve();
      break;
    case Action::generateSudoku:
      Grid::getInstance()->generates();
      break;
    case Action::load:
      Grid::getInstance()->load();
      break;
    case Action::save:
      Grid::getInstance()->save();
      break;
    case Action::benchmark:
      Grid::getInstance()->benchmark();
      break;
    case Action::none: // grid selection and number entering
      break;
    }
  }
}

Sudoku* Sudoku::getInstance() {
  if (!sudoku) {
    sudoku = new Sudoku({
      new Button(1000, 200, static_cast<int>(Action::backMenu), "Back"),
      new Button(1000, 400, static_cast<int>(Action::solve), "Solve"),
      new Button(1000, 300, static_cast<int>(Action::generateSudoku), "Generate"),
      new Button(1000, 500, static_cast<int>(Action::load), "Load"),
      new Button(1000, 600, static_cast<int>(Action::save), "Save"),
      new Button(1000, 700, static_cast<int>(Action::benchmark), "Benchmark"),
      Grid::getInstance()
    });
  }
  return sudoku;
}

Sudoku* Sudoku::sudoku = nullptr;
