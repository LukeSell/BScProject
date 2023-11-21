#include "eight_queens.h"
#include "button.h"
#include "application.h"
#include "menu.h"
#include "grid_eight_queens.h"

void EightQueens::handleEvent(SDL_Event* event) {
  for (auto component : getComponents()) {
    switch (static_cast<Action>(component->handleEvent(event))) {
    case Action::backMenu:
      Application::getInstance()->setScreen(Menu::getInstance());
      break;
    case Action::solve:
      GridEightQueens::getInstance()->solve(0, 0);
      break;
    case Action::none:
      break;
    }
  }
}

EightQueens* EightQueens::getInstance() {
  if (!eightQueens) {
    eightQueens = new EightQueens({
      new Button(900, 200, static_cast<int>(Action::backMenu), "Back"),
      new Button(900, 300, static_cast<int>(Action::solve), "Solve"),
      GridEightQueens::getInstance()
    });
  }
  return eightQueens;
}

EightQueens* EightQueens::eightQueens = nullptr;
