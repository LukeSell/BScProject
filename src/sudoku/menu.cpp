#include "menu.h"
#include "grid.h"
#include "application.h"
#include "sudoku.h"
#include "grid_eight_queens.h"
#include "eight_queens.h"
#include "button.h"
#include "application.h"
#include "grid.h"
#include "grid_eight_queens.h"
#include "eight_queens.h"
#include "sudoku.h"

void Menu::handleEvent(SDL_Event* event) {
  for (auto component : getComponents()) {
    switch (static_cast<Action>(component->handleEvent(event))) {
    case Action::continueGame:
      if (Grid::getInstance()->isInited()) {
        Application::getInstance()->setScreen(Sudoku::getInstance());
      }
      break;
    case Action::loadGame:
      break;
    case Action::settings:
      break;
    case Action::newGame:
      Application::getInstance()->setScreen(Sudoku::getInstance());
      Grid::getInstance()->init();
      break;
    case Action::eightQueens:
      Application::getInstance()->setScreen(EightQueens::getInstance());
      GridEightQueens::getInstance()->load();
      break;
    case Action::quit:
      Application::getInstance()->setRunning(false);
      break;
    }
  }
}

Menu* Menu::getInstance() {
  if (!menu) {
    menu = new Menu({
      new Button(760, 240, static_cast<int>(Action::continueGame), "Continue Game"),
      new Button(760, 440, static_cast<int>(Action::loadGame), "Not Implemented"),
      new Button(760, 640, static_cast<int>(Action::settings), "Not Implemented"),
      new Button(760, 340, static_cast<int>(Action::newGame), "New Game (Sudoku)"),
      new Button(760, 540, static_cast<int>(Action::eightQueens), "Eight Queens"),
      new Button(760, 740, static_cast<int>(Action::quit), "Quit")
    });
  }
  return menu;
}

Menu* Menu::menu = nullptr;
