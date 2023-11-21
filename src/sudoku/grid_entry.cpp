#include "grid_entry.h"
#include "number_factory.h"
#include <iostream>
#include "application.h"

void GridEntry::render() {
  SDL_Renderer* renderer = Application::getInstance()->getRenderer();
  number->render(boundingBox);
  if (isLocked()) {
    SDL_SetRenderDrawColor(renderer, 85, 85, 85, 125);
    SDL_RenderFillRect(renderer, getBoundingBox());
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  }
}

void GridEntry::setNumber(const int n) {
  number = NumberFactory::getInstance()->getNumber(n);
}

int GridEntry::getNumber() {
  return number->getNumber();
}

void GridEntry::setLocked(const bool l) {
  locked = l;
}

bool GridEntry::isLocked() {
  return locked;
}

SDL_Rect* GridEntry::getBoundingBox() {
  return &boundingBox;
}
