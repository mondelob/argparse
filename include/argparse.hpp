/* argparse.hpp - parser of arguments (header)
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

#ifndef argparse__
#define argparse__

#include <string>
#include <vector>
#include <argoption>

#define END_OF_ARGUMENTS -1
/* Returned when last argument is reached */

#define POSITIONAL_ARGUMENT '*'
/* Returned when a positional argument is found */

#define UNKNOWN_ARGUMENT '?'
/* Returned when an unknown argument is found */

#define MISSING_ARGUMENT '$'
/* Returned when an argument is required by an option */

class argparse {
  private:
    std::vector<std::string>::size_type iteration;
    /* Actual iteration of arguments */
    argoption *opt;
    /* Actual option */
    int shortoption;
    /* Actual short option */
    std::string longoption;
    /* Actual long option */
    std::string argument;
    /* Actual argument */
    std::string positional;
    /* Actual positional argument */
    std::string unknown;
    /* Actual unknown argument */
    bool is_multiple;
    /* Set when the argument is multiple */
    std::string multiple;
    /* String with multiple options */
    std::vector<std::string> arguments;
    /* Vector of arguments */
    std::vector<argoption> options;
    /* Vector of possible options */
    argoption *parse(int sopt);
    /* Parses the option */
    argoption *parse(std::string lopt);
    /* Parses the option */
    int next_multiple(void);
    /* Parses the next multiple argument */
    int next_option(std::string arg);
    /* Parses the option */
    int next_iteration(void);
    /* Parses the next iteration */
  public:
    argparse(int argc, char *argv[], struct option *opts);
    /* Constructor */
    int getshortoption(void);
    /* Returns the actual short option */
    std::string getlongoption(void);
    /* Returns the actual long option */
    std::string getargument(void);
    /* Returns the actual argument */
    std::string getpositional(void);
    /* Returns the actual positional argument */
    std::string getunknown(void);
    /* Returns the actual unknown argument */
    int next(void);
    /* Parses the next argument */
};
/* Class defining an argument parser */

#endif
