/* argoption.hpp - defines an option type (header)
 * Copyright (C) 2019  Bruno Mondelo

 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef argoption__
#define argoption__

#include <string>

struct option {
  int opt_short;              /* Option short name */
  std::string opt_long;       /* Option long name */
  bool opt_arg;               /* Set when option requires an argument */
  bool *opt_flag;             /* Flag to set */
};
/* Structure to define an option */

#define OPTION_END {0, "", false, nullptr}

class argoption {
  private:
    int shortoption;
    /* Short option */
    bool has_longoption;
    /* Set when argument has a long option */
    std::string longoption;
    /* Long option */
    bool argument;
    /* Flag set when the option requires an argument */
    bool *to_flag;
    /* Pointer to variable to set */
  public:
    argoption(int sopt, std::string lopt, bool arg=false, bool *flag=nullptr);
    /* Constructor */
    argoption(struct option &opt);
    /* Constructor */
    int getshortoption(void);
    /* Returns the short option */
    std::string getlongoption(void);
    /* Returns the long option */
    bool has_argument(void);
    /* Returns true if option requires an argument */
    bool check(int sopt);
    /* Checks if it's the same argument */
    bool check(std::string lopt);
    /* Checks if it's the same argument */
    void set(void);
    /* Sets the flags when the argument has been found */
};
/* Class defining an option */

#endif
