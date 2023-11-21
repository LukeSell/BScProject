#include "number_factory.h"
#include <SDL_ttf.h>
#include "application.h"
#include <SDL.h>
#include <string>

NumberFactory* NumberFactory::getInstance() {
  if (!numberFactory) {
    numberFactory = new NumberFactory();
  }
  return numberFactory;
}

Number* NumberFactory::getNumber(int number) {
  if (numbers.find(number) == numbers.end()) { // if number is not in map
    SDL_Surface* tempSurface;
    SDL_Renderer* renderer = Application::getInstance()->getRenderer();
    TTF_Font* font = Application::getInstance()->getFont();
    tempSurface = TTF_RenderText_Blended(font, (!number ? " " : std::to_string(number).c_str()), {0, 0, 0, 255}); // if zero represent as empty
    numbers.emplace(number, new Number(number, SDL_CreateTextureFromSurface(renderer, tempSurface), tempSurface->w, tempSurface->h));
    SDL_FreeSurface(tempSurface);
  }
  return numbers[number];
}

NumberFactory* NumberFactory::numberFactory = nullptr;
