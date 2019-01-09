# argparse - library to parse arguments
# Copyright (C) 2019  Bruno Mondelo

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

.PHONY: all clean dist testdrivers

AUXFILES := Makefile README.md LICENSE
PROJDIRS := src include

SRCFILES := $(shell find $(PROJDIRS) -type f -name "*.cpp")
HDRFILES := $(shell find $(PROJDIRS) -type f -name "*.hpp")

OBJFILES := $(patsubst %.cpp,%.o,$(SRCFILES))
TSTFILES := $(patsubst %.cpp,%_t,$(SRCFILES))
LIBFILES := libargparse.a

DEPFILES := $(patsubst %.cpp,%.d,$(SRCFILES))
TSTDEPFILES := $(patsubst %,%.d,$(TSTFILES))

ALLFILES := $(AUXFILES) $(SRCFILES) $(HDRFILES)

WARNINGS := -Wall -Wextra -pedantic -Wshadow -Wpointer-arith -Wcast-align \
            -Wwrite-strings -Wmissing-declarations -Wredundant-decls \
            -Winline -Wno-long-long -Wconversion -Wcast-qual \
            -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 \
            -Winit-self -Wlogical-op -Wmissing-include-dirs -Wnoexcept \
            -Wold-style-cast -Woverloaded-virtual -Wsign-conversion \
            -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 \
            -Wswitch-default -Wundef -Werror
CPPFLAGS := -std=c++14 $(WARNINGS)

all: $(LIBFILES)

clean:
	-@$(RM) $(wildcard $(OBJFILES) $(TSTFILES) $(LIBFILES) argparse.tar.gz)

dist:
	@tar czf argparse.tar.gz $(ALLFILES)

testdrivers: $(TSTFILES)

-include $(DEPFILES) $(TSTDEPFILES)

%.o: %.cpp Makefile
	@$(CXX) $(CPPFLAGS) -Iinclude -MMD -MP -c $< -o $@

%_t: %.cpp
	@$(CXX) $(CPPFLAGS) -Iinclude -DTEST $< -o $@

test: $(OBJFILES)
	@$(CXX) $(CPPFLAGS) -Iinclude $^ -o $@

libargparse.a: $(OBJFILES)
	@ar rcs $@ $(OBJFILES)
