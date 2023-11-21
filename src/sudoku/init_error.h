#ifndef INIT_ERROR_H_INCLUDED
#define INIT_ERROR_H_INCLUDED
#include <exception>
#include <string>
#include <SDL.h>

/** \brief Error thrown if SDL libraries cannot be initialized or the window and renderer cannot be created.
 *
 */

class InitError : public std::exception {
  std::string msg;
 public:
  InitError();
  InitError(const std::string &);
  virtual ~InitError() throw();
  virtual const char* what() const throw();
};

#endif // INIT_ERROR_H_INCLUDED
