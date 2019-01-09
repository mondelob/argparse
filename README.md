# argparse

> small library to parse arguments

This is an small library to parse arguments built in C++. The usage of this
library is very similar to the usage of the getopt function.

The first step is to define an array with the options (or arguments) that you
need to parse. To define the arguments you should use the **option**. This
struct contains 4 elements:

* opt_short: integer number defining the short option (-a, -b, -h).
* opt_long: std::string defining the long option (--help, --verbose, --file). If
  this element is an empty string (""), the option is just short.
* opt_arg: boolean set when the option requires an argument.
* opt_flag: pointer to a boolean variable to set when the argument is found. If
  this element is null, the parser will not flag.

You must ALWAYS end this array of structs with an empty option. Example:

```c++
static bool is_verbose = false;

static struct option options[] = {
  {'h', "help", false, nullptr},
  {'f', "file", true, nullptr},
  {'n', "bytes", true, nullptr},
  {'s', "offset", true, nullptr},
  {'v', "verbose", false, &is_verbose},
  {0, "", false, nullptr}
};
```

To parse the arguments in main function, you should create the argument parser
and then parse the arguments with the *next* method. This method returns the
short option parsed or one of this special options:

* -1: reached the end of arguments.
* '*': found a positional argument. You can retrieve it with the *getpositional*
  method.
* '?': found an unknown option. You can retrieve it with the *getunknown*
  method.
* '$': missing the argument of one option.

Also you can use the following methods:

* getshortoption(void): returns an integer defining the actual option parsed.
* getlongoption(void): returns a string defining the actual option parsed.
* getargument(void): if the actual option parsed requires an argument, you can
  retrieve it using this method.
* getpositional(void): returns the actual positional argument.
* getunknown(void): returns the actual unknown argument.

An example with the options defined before:

```c++
int
main(int argc, char *argv[]) {
  int c;
  argparse parser(argc, argv, options);
  std::string longoption, fname, bytes, offset;
  
  while ((c = parser.next()) != -1) {
    switch (c) {
      case 'h':
        show_help(0);
        break;
      case 'f':
        fname = parser.getargument();
        break;
      case 'n':
        bytes = parser.getargument(); /* TODO: cast */
        break;
      case 's':
        offset = parser.getargument(); /* TODO: cast */
        break;
      /* case 'v':
        std::cout << "verbose mode on" << std::endl;
        break; */
      /* This case can be ignore, it just sets a flag */
      /* case '*':
        std::cout << "positional argument: " << parser.getpositional() <<
          std::endl;
        break; */
      /* Ignore positional arguments? */
      case '?':
        std::cerr << "unknown option " << parser.getunknown() << std::endl;
        show_help(1);
        break;
      case '$':
        std::cerr << "missing argument for option " <<
          static_cast<char>(parser.getshortoption()) << std::endl;
        show_help(2);
      default:
        break;
    }
  }

  if (is_verbose)
    std::cout << "verbose is ON" << std::endl;

  return 0;
}
```

Also you can use one of the following definitions returned by **next** method:

* END_OF_ARGUMENTS: there's no more arguments.
* POSITIONAL_ARGUMENT: there's a positional argument.
* UNKNOWN_ARGUMENT: unknown argument found.
* MISSING_ARGUMENT: missing argument for an option that requires an argument.

Full example:

```c++
#include <iostream>
#include <argparse>

static bool is_verbose = false;

static struct option options[] = {
  {'h', "help", false, nullptr},
  {'f', "file", true, nullptr},
  {'n', "bytes", true, nullptr},
  {'s', "offset", true, nullptr},
  {'v', "verbose", false, &is_verbose},
  {0, "", false, nullptr}
};

void show_help(int val);
/* Shows help and usage and exits */

void
show_help(int val) {
  if (val == 0) {
    std::cout << "Usage: test [-f|--file FILE] [-n|--bytes BYTES] \
[-s|--offset OFFSET] [-v|--verbose]" << std::endl;
    std::cout << "       test -h|--help" << std::endl;
    std::cout << std::endl;
    std::cout << "Tests this library" << std::endl;
    std::cout << "  -f, --file    does nothing with a file" << std::endl;
    std::cout << "  -h, --help    shows this message and exits" << std::endl;
    std::cout << "  -n, --bytes   a number" << std::endl;
    std::cout << "  -s, --offset  another number" << std::endl;
    std::cout << "  -v, --verbose sets verbose mode on" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  test -f /etc/passwd -b 100  Does absolutely nothing" <<
      std::endl;
    std::cout << "  test -s 100 -v              Nothing.." << std::endl;
    std::cout << std::endl;
    std::cout << "test  Copyright (C) 2018  Bruno Mondelo" << std::endl;
    std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details \
type `show w'." << std::endl;
    std::cout << "This is free software, and you are welcome to redistribute \
it" << std::endl;
    std::cout << "under certain conditions; type `show c' for details." << std::endl;
  }
  else {
    std::cerr << "Usage: test [-f|--file FILE] [-n|--bytes BYTES] \
[-s|--offset OFFSET] [-v|--verbose]" << std::endl;
    std::cerr << "       test -h|--help" << std::endl;
  }

  exit(val);
}
/* Shows help and usage and exits */

int
main(int argc, char *argv[]) {
  int c;
  argparse parser(argc, argv, options);
  std::string longoption, fname, bytes, offset;
  
  while ((c = parser.next()) != -1) {
    switch (c) {
      case 'h':
        show_help(0);
        break;
      case 'f':
        fname = parser.getargument();
        break;
      case 'n':
        bytes = parser.getargument(); /* TODO: cast */
        break;
      case 's':
        offset = parser.getargument(); /* TODO: cast */
        break;
      /* case 'v':
        std::cout << "verbose mode on" << std::endl;
        break; */
      /* This case can be ignore, it just sets a flag */
      /* case '*':
        std::cout << "positional argument: " << parser.getpositional() <<
          std::endl;
        break; */
      /* Ignore positional arguments? */
      case '?':
        std::cerr << "unknown option " << parser.getunknown() << std::endl;
        show_help(1);
        break;
      case '$':
        std::cerr << "missing argument for option " <<
          static_cast<char>(parser.getshortoption()) << std::endl;
        show_help(2);
      default:
        break;
    }
  }

  if (is_verbose)
    std::cout << "verbose is ON" << std::endl;

  return 0;
}
```