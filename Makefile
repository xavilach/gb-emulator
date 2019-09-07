# Executable
EXECUTABLE      := gb-emulator

# Directories
SRCDIR      := src
INCDIR      := inc
BUILDDIR    := obj
BINDIR   	:= bin
RESDIR      := res

# Extensions
SRCEXT      := cc
DEPEXT      := d
OBJEXT      := o

# Path to SDL2 library
SDL2_DIR	:= "/c/SDL2-2.0.9/i686-w64-mingw32"
SDL2_LIBDIR := $(SDL2_DIR)/lib
SDL2_INCLUDE_DIRS := $(SDL2_DIR)/include
SDL2_LDLIBS := -lSDL2main -lSDL2 -mwindows
SDL2_LDFLAGS := -L${SDL2_LIBDIR}

# Path to SDL2 TTF library
SDL2_TTF_DIR	:= "/c/SDL2-2.0.9/i686-w64-mingw32"
SDL2_TTF_LIBDIR := $(SDL2_TTF_DIR)/lib
SDL2_TTF_INCLUDE_DIRS := $(SDL2_TTF_DIR)/include
SDL2_TTF_LDLIBS := -lSDL2_ttf
SDL2_TTF_LDFLAGS := -L${SDL2_TTF_LIBDIR}

# Path to SDL2 Mixer library
SDL2_MIXER_DIR	:= "/c/SDL2-2.0.9/i686-w64-mingw32"
SDL2_MIXER_LIBDIR := $(SDL2_MIXER_DIR)/lib
SDL2_MIXER_INCLUDE_DIRS := $(SDL2_MIXER_DIR)/include
SDL2_MIXER_LDLIBS := -lSDL2_mixer
SDL2_MIXER_LDFLAGS := -L${SDL2_MIXER_LIBDIR}

# Linker flags
LDLIBS		:= -lmingw32 -mconsole ${SDL2_LDLIBS} ${SDL2_TTF_LDLIBS} ${SDL2_MIXER_LDLIBS}
LDFLAGS		:=  ${SDL2_LDFLAGS} ${SDL2_TTF_LDFLAGS} ${SDL2_MIXER_LDFLAGS}

# Compiler flags
CPPFLAGS	:= -MMD -MP -I$(INCDIR) -I$(SDL2_INCLUDE_DIRS) -I/usr/local/include
CXXFLAGS	:= -std=c++17 -g -Wall -Weffc++ -Wextra -Wsign-conversion -Werror -pedantic-errors

#---------------------------------------------------------------------------------
SOURCES     := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS     := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

# Default
all: resources $(BINDIR)/$(EXECUTABLE)

# Run
run: $(BINDIR)/$(EXECUTABLE)
	$(BINDIR)/$(EXECUTABLE)

# Rebuild
rebuild: cleaner all

# Copy Resources from Resources Directory to EXECUTABLE Directory
resources: directories
	@cp ./$(RESDIR)/* $(BINDIR)/

# Create build and binary directories
directories:
	@mkdir -p $(BINDIR)
	@mkdir -p $(BUILDDIR)

# Clean
clean:
	@$(RM) -rf $(BUILDDIR)

cleaner: clean
	@$(RM) -rf $(BINDIR)

# Link
$(BINDIR)/$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

# Compile
$(BUILDDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

.PHONY: all run rebuild clean cleaner resources directories

# Pull in dependency info for *existing* object files
-include $(OBJECTS:.$(OBJEXT)=.$(DEPEXT))
