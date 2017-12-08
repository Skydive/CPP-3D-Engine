Q = @
CC = g++
CXXVERSION = -std=c++1z

# General Options
PROJECT_OUTDIR = bin
PROJECT_CFLAGS := $(CPPVERSION) -g -pipe -fPIC -Wall -mtune=native -O2
PROJECT_LFLAGS := -pipe

# Engine
ENGINE_NAME := Engine
ENGINE_OBJDIR := obj/$(ENGINE_NAME)
ENGINE_SRCDIR := src/$(ENGINE_NAME)

ENGINE_PACKAGES = gl glu glew glfw3 openal freealut assimp
ENGINE_CFLAGS := $(PROJECT_CFLAGS) $(shell pkg-config $(ENGINE_PACKAGES) --cflags)
ENGINE_LFLAGS := $(PROJECT_LFLAGS) $(shell pkg-config $(ENGINE_PACKAGES) --libs)
ENGINE_LFLAGS := $(ENGINE_LFLAGS) -lfreeimage -shared

ENGINE_CPP := $(wildcard $(ENGINE_SRCDIR)/*.cpp)
ENGINE_OBJ := $(addprefix $(ENGINE_OBJDIR)/,$(notdir $(ENGINE_CPP:.cpp=.o)))
ENGINE_OUT := $(PROJECT_OUTDIR)/lib$(ENGINE_NAME).so

# Game
GAME_NAME := Game
GAME_OBJDIR := obj/$(GAME_NAME)
GAME_SRCDIR := src/$(GAME_NAME)
GAME_INCDIR := $(ENGINE_SRCDIR)

GAME_CFLAGS := $(PROJECT_CFLAGS) -I $(GAME_INCDIR)
GAME_LFLAGS := $(PROJECT_LFLAGS) -L $(PROJECT_OUTDIR) -l$(ENGINE_NAME) -Wl,-rpath=.

GAME_CPP := $(wildcard $(GAME_SRCDIR)/*.cpp)
GAME_OBJ := $(addprefix $(GAME_OBJDIR)/,$(notdir $(GAME_CPP:.cpp=.o)))
GAME_OUT := $(PROJECT_OUTDIR)/$(GAME_NAME)

all: Engine Game gen

Engine: $(ENGINE_OBJ)
	@echo "	LD $(ENGINE_OUT)"
	$(Q)mkdir -p $(PROJECT_OUTDIR)
	$(Q)$(CC) $(ENGINE_OBJ) -o $(ENGINE_OUT) $(ENGINE_LFLAGS)

$(ENGINE_OBJDIR)/%.o: $(ENGINE_SRCDIR)/%.cpp
	@echo "	CC $<"
	$(Q)mkdir -p $(ENGINE_OBJDIR)
	$(Q)$(CC) -c $< -o $@ $(ENGINE_CFLAGS)


Game: $(GAME_OBJ)
	@echo "	LD $(GAME_OUT)"
	$(Q)mkdir -p $(PROJECT_OUTDIR)
	$(Q)$(CC) $(GAME_OBJ) -o $(GAME_OUT) $(GAME_LFLAGS)

$(GAME_OBJDIR)/%.o: $(GAME_SRCDIR)/%.cpp
	@echo "	CC $<"
	$(Q)mkdir -p $(GAME_OBJDIR)
	$(Q)$(CC) -c $< -o $@ $(GAME_CFLAGS)

gen:
	$(shell python gen/generate.py)

.PHONY: clean

clean:
	rm $(ENGINE_OBJDIR)/* $(GAME_OBJDIR)/*
