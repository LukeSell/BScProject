#include "button.h"
#include <iostream>
#include <SDL_ttf.h>
#include "application.h"

int Button::handleEvent(SDL_Event* event) {
  if (event->type == SDL_MOUSEBUTTONUP) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    if (x >= boundingBox.x && x < boundingBox.x + boundingBox.w && y >= boundingBox.y && y < boundingBox.y + boundingBox.h) { // inside the buttons box
      return action;
    }
  }
  return -1; // not something that is an enum
}

void Button::render() {
  SDL_Renderer* renderer = Application::getInstance()->getRenderer();
  if (!texture) {
    surface = TTF_RenderText_Blended(Application::getInstance()->getFont(), text, {0, 0, 0, 255});
    centreBoundingBox.x = boundingBox.x + ((boundingBox.w - surface->w) / 2);
    centreBoundingBox.y = boundingBox.y + ((boundingBox.h - surface->h) / 2);
    centreBoundingBox.w = surface->w;
    centreBoundingBox.h = surface->h;
    tempTexture = SDL_CreateTexture(Application::getInstance()->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 400, 100);
    SDL_SetRenderTarget(renderer, tempTexture);
    SDL_SetRenderDrawColor(renderer, 175, 175, 175, 255);
    SDL_RenderFillRect(renderer, &tempBoundingBox); // draw buttons box
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(renderer, &tempBoundingBox);
    SDL_SetRenderTarget(renderer, nullptr);
    texture = SDL_CreateTextureFromSurface(renderer, surface); // buttons text
  }
  SDL_RenderCopy(renderer, tempTexture, nullptr, &boundingBox);
  SDL_RenderCopy(renderer, texture, nullptr, &centreBoundingBox);
}
