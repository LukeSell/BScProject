#include "application.h"
#include "init_error.h"
#include <string>
#include <memory>
#include <iostream>

void Application::init(const int width, const int height, const Uint32 window_flags) {
  if (SDL_Init(SDL_INIT_TIMER | SDL_INIT_VIDEO)) { // also includes events subsystem
    throw InitError();
  }
  if (TTF_Init()) {
    throw InitError();
  }
  if (SDL_CreateWindowAndRenderer(width, height, window_flags, &window, &renderer)) {
    throw InitError();
  }
  SDL_SetWindowTitle(window, "Project");
  SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND); // allows transparent overlays
  font = TTF_OpenFont("C:\\Windows\\Fonts\\Arial.ttf", 40);
  running = true;
}

Application* Application::getInstance() {
  if (!application) {
    application = new Application();
  }
  return application;
}

void Application::render() {
  //clear the screen
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

  currentScreen->render();

  // update the screen
  SDL_RenderPresent(renderer);
}

void Application::handleEvents() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
    case SDL_QUIT:
      running = false;
      break;
    default:
      currentScreen->handleEvent(&event);
      break;
    }
  }
}

void Application::clean() {
  TTF_CloseFont(font);
  SDL_DestroyWindow(window);
  SDL_DestroyRenderer(renderer);
  TTF_Quit();
  SDL_Quit();
}

SDL_Renderer* Application::getRenderer() {
  return renderer;
}

TTF_Font* Application::getFont() {
  return font;
}

bool Application::isRunning() {
  return running;
}

void Application::setRunning(bool r) {
  running = r;
}

void Application::setScreen(Screen* cS) {
  currentScreen = cS;
}

Application* Application::application = nullptr;
