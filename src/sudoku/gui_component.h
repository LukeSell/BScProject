#ifndef GUI_COMPONENT_H_INCLUDED
#define GUI_COMPONENT_H_INCLUDED
#include <SDL.h>

/** \brief The object that is a base class for all GUI components.
 */

class GUIComponent {
 public:
  virtual ~GUIComponent() {}

  /** \brief Handles the user input event.
   *
   * \param event Is a user input event.
   * \return No action to be taken if the sub class does not override the base class method.
   */

  virtual int handleEvent(SDL_Event* event) {
    return -1;
  }

  /** \brief The sub class must implement a method to render the GUI components on the screen.
   */

  virtual void render() = 0;
};

#endif // GUI_COMPONENT_H_INCLUDED
