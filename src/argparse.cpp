/* argparse.hpp - parser of arguments (source)
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

#include <argparse>

argparse::argparse(int argc, char *argv[], struct option *opts) {
  int i;
  struct option last;

  this->iteration = 0;
  this->opt = nullptr;
  this->shortoption = -1;
  this->longoption = "";
  this->argument = "";
  this->positional = "";
  this->is_multiple = false;
  this->multiple = "";

  for (i = 1; i < argc; i++)
    this->arguments.push_back(argv[i]);

  i = 0;
  last = OPTION_END;
  while (opts[i].opt_short != last.opt_short ||
    opts[i].opt_long != last.opt_long || opts[i].opt_arg != last.opt_arg ||
    opts[i].opt_flag != last.opt_flag) {
    this->options.push_back(argoption(opts[i]));
    i++;
  }
}
/* Constructor */

argoption *
argparse::parse(int sopt) {
  std::vector<argoption>::size_type i;

  i = 0;
  while (i < this->options.size() && !(this->options[i].check(sopt)))
    i++;

  if (i >= this->options.size())
    return nullptr;

  return &(this->options[i]);
}
/* Parses the option */

argoption *
argparse::parse(std::string lopt) {
  std::vector<argoption>::size_type i;

  i = 0;
  while (i < this->options.size() && !(this->options[i].check(lopt)))
    i++;

  if (i >= this->options.size())
    return nullptr;

  return &(this->options[i]);
}
/* Parses the option */

int
argparse::next_multiple(void) {
  int rval;
  std::string sopt;
  argoption *actopt;

  sopt = this->multiple.at(0);
  actopt = this->parse(this->multiple.at(0));

  if (this->multiple.length() > 1) {
    this->multiple = this->multiple.substr(1);
  }
  else {
    this->is_multiple = false;
    this->multiple = "";
  }

  if (actopt == nullptr) {
    rval = UNKNOWN_ARGUMENT;
    this->unknown = "-" + sopt;
  }
  else {
    this->opt = actopt;
    rval = actopt->getshortoption();
    this->shortoption = rval;
    this->longoption = actopt->getlongoption();
    if (actopt->has_argument()) {
      if (this->is_multiple || this->iteration >= this->arguments.size()) {
        rval = MISSING_ARGUMENT;
      }
      else {
        this->argument = this->arguments[this->iteration];
        this->iteration++;
      }
    }
  }

  return rval;
}
/* Parses the next multiple argument */

int
argparse::next_option(std::string arg) {
  int rval;
  argoption *actopt;
  bool sopt;

  rval = 0;

  if (arg.at(1) != '-') {
    if (arg.length() > 2) {
      this->is_multiple = true;
      this->multiple = arg.substr(2);
    }
    actopt = this->parse(arg.at(1));
    sopt = true;
  }
  else {
    if (arg.length() <= 2) {
      rval = POSITIONAL_ARGUMENT;
      this->positional = arg;
    }
    else {
      actopt = this->parse(arg.substr(2));
      sopt = false;
    }
  }

  if (rval != POSITIONAL_ARGUMENT && actopt == nullptr) {
    rval = UNKNOWN_ARGUMENT;
    if (sopt)
      this->unknown = "-" + arg.substr(1, 1);
    else
      this->unknown = "--" + arg.substr(2);
  }
  else if (rval != POSITIONAL_ARGUMENT) {
    rval = actopt->getshortoption();
    this->opt = actopt;
    this->shortoption = rval;
    this->longoption = actopt->getlongoption();
    if (actopt->has_argument()) {
      if (this->is_multiple ||
        (this->iteration + 1) >= this->arguments.size()) {
        rval = MISSING_ARGUMENT;
      }
      else {
        this->iteration++;
        this->argument = this->arguments[this->iteration];
      }
    }
  }

  return rval;
}
/* Parses the option */

int
argparse::next_iteration(void) {
  int rval;
  std::string arg;

  if (this->iteration >= this->arguments.size())
    return END_OF_ARGUMENTS;

  arg = this->arguments[this->iteration];

  if (arg.at(0) != '-' || arg.length() <= 1) {
    rval = POSITIONAL_ARGUMENT;
    this->positional = arg;
  }
  else {
    rval = this->next_option(arg);
  }

  this->iteration++;

  return rval;
}
/* Parses the next iteration */

int
argparse::getshortoption(void) {
  return this->shortoption;
}
/* Returns the actual short option */

std::string
argparse::getlongoption(void) {
  return this->longoption;
}
/* Returns the actual long option */

std::string
argparse::getargument(void) {
  return this->argument;
}
/* Returns the actual argument */

std::string
argparse::getpositional(void) {
  return this->positional;
}
/* Returns the actual positional argument */

std::string
argparse::getunknown(void) {
  return this->unknown;
}
/* Returns the actual unknown argument */

int
argparse::next(void) {
  int rval;

  this->opt = nullptr;
  this->shortoption = -1;
  this->longoption = "";
  this->argument = "";
  this->positional = "";
  this->unknown = "";

  if (this->is_multiple)
    rval = this->next_multiple();
  else
    rval = this->next_iteration();

  if (this->opt != nullptr)
    this->opt->set();

  return rval;
}
/* Parses the next argument */

#ifdef TEST

int
main(void) {
  int nerr;

  nerr = 0;

  return nerr;
}

#endif
