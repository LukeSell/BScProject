#ifndef SCREEN_H_INCLUDED
#define SCREEN_H_INCLUDED
#include <forward_list>
#include <initializer_list>
#include "gui_component.h"
#include <SDL.h>

/** \brief The object that is a base class for all screens.
 */

class Screen {
 public:
  virtual ~Screen();

  /** \brief Renders all GUI components onto the screen.
   */

  void render();

  /** \brief The sub class must implement a method to handle user input events on the screen.
   *
   * \param event Is the user input event to be handled.
   */

  virtual void handleEvent(SDL_Event* event) = 0;

 protected:
  Screen(std::initializer_list<GUIComponent*> c) : components{c} {}

  std::forward_list<GUIComponent*> getComponents() {
    return components;
  }

 private:
  std::forward_list<GUIComponent*> components;
};

#endif // SCREEN_H_INCLUDED
