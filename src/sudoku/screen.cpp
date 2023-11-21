#include "screen.h"

Screen::~Screen() {
}

void Screen::render() {
  for (auto component : components) {
    component->render();
  }
}
