CC = g++
CFLAGS = -Wall -Wextra
RELEASE_FLAGS = -O3 -DNDEBUG
DEBUG_FLAGS   = -g

BUILD_MACROS = -DBUILD_ENGINE

ENGINE_BIN_DIR = $(CURDIR)/engine/bin
ENGINE_SRC_DIR = $(CURDIR)/engine/src
ENGINE_EXT_DIR = $(CURDIR)/engine/external
ENGINE_TARGET  = libengine.so
ENGINE_LIBRARY_DIR = $(ENGINE_BIN_DIR)/$(ENGINE_TARGET)

APP_BIN_DIR = $(CURDIR)/app/bin
APP_SRC_DIR = $(CURDIR)/app/src
APP_TARGET  = app

SHELL = /bin/sh

ENGINE_SRC_FILES := $(wildcard $(ENGINE_SRC_DIR)/*.cpp)
ENGINE_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_SRC_FILES))

APP_SRC_FILES := $(wildcard $(APP_SRC_DIR)/*.cpp)
APP_OBJ_FILES := $(patsubst %.cpp,%.o,$(APP_SRC_FILES))

PRECOMPILED_HEADER = $(ENGINE_SRC_DIR)/enginepch.h

GLFW_DIR = $(ENGINE_EXT_DIR)/glfw
GLFW_MAKEFILE = $(GLFW_DIR)/build/src/Makefile
GLFW_LIBRARY_DIR = $(GLFW_DIR)/build/src/
GLFW_LINKER_FLAGS = -L/usr/local/lib64 -Wl,-rpath $(GLFW_LIBRARY_DIR) \
                    -L$(GLFW_LIBRARY_DIR) -lglfw3 -lrt -lm -ldl

GLFW_INCLUDE_FLAGS = -I$(GLFW_DIR)/include
ENGINE_INCLUDE_FLAGS = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/src/ \
                       -I$(CURDIR)/engine/external/ $(GLFW_INCLUDE_FLAGS)
APP_INCLUDE_FLAGS    = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/external/

APP_LINKER_FLAGS = -Wl,-rpath $(ENGINE_BIN_DIR) -lengine -L$(ENGINE_BIN_DIR)

all: build_engine

# precompile a header file with many common includes
precompile_header: $(PRECOMPILED_HEADER)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) -x c++-header \
	-fPIC -o $(PRECOMPILED_HEADER).gch -c $(PRECOMPILED_HEADER)

# configure glfw (for Wayland) (generates Makefile using cmake)
configure_glfw:
	cmake -S $(GLFW_DIR) -B $(GLFW_DIR)/build -D GLFW_USE_WAYLAND=1

# build static glfw library and generate header files
build_glfw: configure_glfw
	cd $(GLFW_DIR)/build && make -j 4 && cd -

# compile engine (.o files will be stored in engine/src)
$(ENGINE_SRC_DIR)/%.o : $(ENGINE_SRC_DIR)/%.cpp precompile_header build_glfw
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(DEBUG_FLAGS) $(BUILD_MACROS) -o $@ -c $<

# link engine to shared/dynamic library (engine/bin/libengine.so)
build_engine: $(ENGINE_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) \
	-o $(ENGINE_LIBRARY_DIR) \
	$(GLFW_LINKER_FLAGS) -shared $<

# compile app (.o files will be stored in app/src)
$(APP_SRC_DIR)/%.o : $(APP_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(APP_INCLUDE_FLAGS) \
	$(DEBUG_FLAGS) -o $@ -c $<

# build app (app/bin/app) (LD_LIBRARY_PATH still needs to be set)
build_app: $(APP_OBJ_FILES)
	$(CC) $(CFLAGS) $(DEBUG_FLAGS) $(APP_LINKER_FLAGS) \
	-o $(APP_BIN_DIR)/$(APP_TARGET) $(APP_INCLUDE_FLAGS) $<

clean:
	rm -rf $(ENGINE_BIN_DIR)/$(ENGINE_TARGET) \
	$(ENGINE_SRC_DIR)/*.o $(APP_SRC_DIR)/*.o \
	$(ENGINE_SRC_DIR)/enginepch.h.gch \
	$(APP_BIN_DIR)/$(APP_TARGET)
	
.PHONY: all clean
