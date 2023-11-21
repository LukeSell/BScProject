#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include "application.h"
#include "init_error.h"

/** \brief The main method that launches the application and runs the program loop, then closing the application when the user quits.
 */

int main(int argc, char** argv) {
  const int FPS = 30;
  const int DELAY = 1000.0f / FPS;
  Uint32 frameStart, frameTime;
  std::ios_base::sync_with_stdio(false);
  try {
    Application::getInstance()->init(1920, 1080, SDL_WINDOW_RESIZABLE);
    while (Application::getInstance()->isRunning()) {
      frameStart = SDL_GetTicks();
      Application::getInstance()->handleEvents();
      Application::getInstance()->render();
      frameTime = SDL_GetTicks() - frameStart;
      if (frameTime < DELAY) {
        SDL_Delay((int) (DELAY - frameTime));
      }
    }
    Application::getInstance()->clean();
    return 0;
  } catch (const InitError &err) {
    std::cerr << "Error while initializing SDL: "
              << err.what()
              << std::endl;
  }
  return 1;
}
