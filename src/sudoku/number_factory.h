#ifndef NUMBER_FACTORY_H_INCLUDED
#define NUMBER_FACTORY_H_INCLUDED
#include "number.h"
#include <map>

/** \brief Stores the numbers used as values in entries and allows them to be requested so that they can be rendered in assigned entries.
 */

class NumberFactory {
 public:
  static NumberFactory* getInstance();

  Number* getNumber(int number);
 private:
  NumberFactory() : numbers{} {}

  static NumberFactory* numberFactory;

  std::map<int, Number*> numbers; // stores the numbers to be used as values in entries on the grid

};

#endif // NUMBER_FACTORY_H_INCLUDED
