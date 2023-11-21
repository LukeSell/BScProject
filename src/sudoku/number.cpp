#include "number.h"
#include <SDL_ttf.h>
#include "application.h"

Number::~Number() {
  SDL_DestroyTexture(texture);
}

void Number::render(SDL_Rect boundingBox) {
  SDL_Rect centreBoundingBox;
  SDL_Renderer* renderer = Application::getInstance()->getRenderer();
  centreBoundingBox.x = boundingBox.x + ((boundingBox.w - width) / 2);
  centreBoundingBox.y = boundingBox.y + ((boundingBox.h - height) / 2);
  centreBoundingBox.w = width;
  centreBoundingBox.h = height;
  SDL_RenderCopy(renderer, texture, nullptr, &centreBoundingBox);
}

int Number::getNumber() {
  return number;
}
