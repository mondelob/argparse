/* argoption.hpp - defines an option type (source)
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

#include <argoption>

argoption::argoption(int sopt, std::string lopt, bool arg, bool *flag) {
  this->shortoption = sopt;
  if (lopt == "")
    this->has_longoption = false;
  else
    this->has_longoption = true;
  this->longoption = lopt;
  this->argument = arg;
  this->to_flag = flag;
}
/* Constructor */

argoption::argoption(struct option &opt) : argoption(opt.opt_short,
  opt.opt_long, opt.opt_arg, opt.opt_flag) {
}
/* Constructor */

int
argoption::getshortoption(void) {
  return this->shortoption;
}
/* Returns the short option */

std::string
argoption::getlongoption(void) {
  return this->longoption;
}
/* Returns the long option */

bool
argoption::has_argument(void) {
  return this->argument;
}
/* Returns true if option requires an argument */

bool
argoption::check(int sopt) {
  if (sopt != this->shortoption)
    return false;

  return true;
}
/* Checks if it's the same argument */

bool
argoption::check(std::string lopt) {
  if (!this->has_longoption)
    return false;

  if (lopt != this->longoption)
    return false;

  return true;
}
/* Checks if it's the same argument */

void
argoption::set(void) {
  if (this->to_flag != nullptr)
    *(this->to_flag) = true;
}
/* Sets the flags when the argument has been found */

#ifdef TEST

int
main(void) {
  int nerr;
  struct option opt;
  argoption *argopt;
  bool flag;

  nerr = 0;

  flag = false;

  opt.opt_short = 'a';
  opt.opt_long = "aaa";
  opt.opt_arg = false;
  opt.opt_flag = &flag;

  argopt = new argoption(opt);

  if (argopt.getshortoption() != 'a')
    nerr++;

  if (argopt.getlongoption() != "aaa")
    nerr++;

  if (argopt.has_argument())
    nerr++;

  if (!(argopt.check('a')) || argopt.check('b'))
    nerr++;

  if (!(argopt.check("aaa")) || argopt.check("bbb"))
    nerr++;

  argopt.set();
  if (!flag)
    nerr++;

  delete argopt;

  return nerr++;
}

#endif
