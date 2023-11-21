#ifndef NUMBER_H_INCLUDED
#define NUMBER_H_INCLUDED
#include <SDL.h>

/** \brief An object that represents the value of an entry, stores the text representation of the number ready to be rendered to the screen.
 */

class Number {
 public:
   Number() = default;
  Number(int n, SDL_Texture* t, int w, int h) : number{n}, texture{t}, width{w}, height{h} {}
  ~Number();
  Number(Number&&) = default;
  Number& operator=(Number&&) = default;
  Number(const Number&) = default;
  Number& operator=(const Number&) = default;

  /** \brief Renders the number to the screen in the position of the respective entry.
   *
   * \param boundingBox Is the entries box so that the text representation of the number can be rendered in the correct position on the screen.
   */

  void render(SDL_Rect boundingBox);

  int getNumber();

 private:

  int number; // the int representation of this number
  SDL_Texture* texture; // the text representation of this number, ready to be rendered to the screen
  int width; // the textures width
  int height; // the textures height
};

#endif // NUMBER_H_INCLUDED
