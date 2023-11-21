#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "gui_component.h"

/** \brief Object that is used to create buttons to display and click on, so that the user may navigate and use the application.
 */

class Button : public GUIComponent {
 public:
  /** \brief Creates a button.
   *
   * \param x Is the x position to draw on screen.
   * \param y Is the y position to draw on screen.
   * \param a Is the action the button does when clicked on.
   * \param t Is the text the button displays.
   */

  Button(const int x, const int y, const int a, const char* t) : boundingBox{x, y, 400, 100}, tempBoundingBox{0, 0, 400, 100}, centreBoundingBox{0, 0, 0, 0}, action{a}, text{t}, surface{nullptr}, texture{nullptr}, tempTexture{nullptr} {}

  /** \brief Handles any button clicks, by checking if the button has been clicked and then returning the action to be performed.
   *
   * \param event Is the user event that has happened.
   * \return Is the action to be performed by the application.
   *
   */

  int handleEvent(SDL_Event* event);

  /** \brief Renders the button to the screen by first drawing a box for the button and then drawing the buttons text on top.
   */

  void render();

 private:
  SDL_Rect boundingBox; // where to draw on screen
  SDL_Rect tempBoundingBox; // where to draw on texture
  SDL_Rect centreBoundingBox; // where to draw text
  int action; // what this button does
  const char* text; // the text the button displays
  SDL_Surface* surface;
  SDL_Texture* texture;
  SDL_Texture* tempTexture;
};

#endif // BUTTON_H_INCLUDED
