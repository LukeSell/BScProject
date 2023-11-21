#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include "screen.h"
#include "menu.h"
#include <memory>

/** \brief Singleton object that handles all parts of running the program, these are rendering, handling events and cleaning up when the program closes.
 */


class Application {
 public:
  static Application* getInstance();

  /** \brief Initializes the SDL libraries and creates the window and renderer, as well as GUI buttons.
   *
   * \param width Is the width of the window.
   * \param height Is the height of the window.
   * \param window_flags Are any window flags that may be set.
   *
   */


  void init(int width, int height, Uint32 window_flags);

  /** \brief Renders all GUI elements onto the window.
   *
   */

  void render();

  /** \brief Handles all user events, these are mouse clicks and key presses, used for buttons and sudoku.
   */

  void handleEvents();

  /** \brief Cleans up the application by freeing any allocated resources and exiting SDL subsystems.
   */

  void clean();

  SDL_Renderer* getRenderer();

  TTF_Font* getFont();

  bool isRunning();

  void setRunning(bool r);

  void setScreen(Screen* cS);

 private:
  Application() : window{nullptr}, renderer{nullptr}, font{nullptr}, running{false}, currentScreen{Menu::getInstance()} {}

  static Application* application;
  SDL_Window* window;
  SDL_Renderer* renderer;
  TTF_Font* font;
  bool running; // if the program is currently running
  Screen* currentScreen; // the current screen
};

#endif // APPLICATION_H_INCLUDED
