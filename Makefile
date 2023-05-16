CC = g++
CFLAGS = -Wall -Wextra -O3 -DNDEBUG
DEBUG_FLAGS = -Wall -Wextra -g
LDFLAGS = -lboost_serialization
SHELL = /usr/bin/sh
CMAKE = /usr/bin/cmake

BUILD_MACROS = -DBUILD_ENGINE

ENGINE_BIN_DIR = $(CURDIR)/engine/bin
ENGINE_SRC_DIR = $(CURDIR)/engine/src
ENGINE_EXT_DIR = $(CURDIR)/engine/external
ENGINE_TARGET  = libengine.so
ENGINE_LIBRARY = $(ENGINE_BIN_DIR)/$(ENGINE_TARGET)

ENGINE_SRC_FILES := $(wildcard $(ENGINE_SRC_DIR)/*.cpp)
ENGINE_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_SRC_FILES))

# default: release mode
all: build_engine

# if debug target is called, CFLAGS variable is overwritten with DEBUG_FLAGS
debug: CFLAGS = $(DEBUG_FLAGS)

debug: build_engine

###### GLFW ######

GLFW_DIR = $(ENGINE_EXT_DIR)/glfw
GLFW_MAKEFILE = $(GLFW_DIR)/build/src/Makefile
GLFW_LIBRARY_DIR = $(GLFW_DIR)/build/src/
GLFW_LINKER_FLAGS = -L/usr/local/lib64 -Wl,-rpath $(GLFW_LIBRARY_DIR) \
                    -L$(GLFW_LIBRARY_DIR) -lglfw3 -lrt -lm -ldl
GLFW_INCLUDE_FLAGS   = -I$(GLFW_DIR)/include

# configure glfw (for Wayland) (generates Makefile using cmake)
configure_glfw:
	$(CMAKE) -S $(GLFW_DIR) -B $(GLFW_DIR)/build
# -D GLFW_USE_WAYLAND=1

# build static glfw library and generate header files
build_glfw: configure_glfw
	cd $(GLFW_DIR)/build && make -j 4 && cd -

###### \GLFW #####


###### GLAD ######

GLAD_DIR = $(ENGINE_EXT_DIR)/glad
GLAD_SRC_DIR = $(GLAD_DIR)/src
GLAD_INCLUDE_FLAGS = -I$(GLAD_DIR)/include

GLAD_SRC_FILES := $(wildcard $(GLAD_SRC_DIR)/*.c)
GLAD_OBJ_FILES := $(patsubst %.c,%.o,$(GLAD_SRC_FILES))

# compile GLAD
$(GLAD_SRC_DIR)/%.o : $(GLAD_SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(GLAD_INCLUDE_FLAGS) -fPIC -o $@ -c $<

###### \GLAD #####


###### IMGUI ######

IMGUI_DIR = $(ENGINE_EXT_DIR)/imgui
IMGUI_INCLUDE_FLAGS = -I$(IMGUI_DIR)

IMGUI_SRC_FILES := $(wildcard $(IMGUI_DIR)/*.cpp)
IMGUI_OBJ_FILES := $(patsubst %.cpp,%.o,$(IMGUI_SRC_FILES))

# compile IMGUI
$(IMGUI_DIR)/%.o : $(IMGUI_DIR)/%.cpp
	$(CC) $(CFLAGS) $(IMGUI_INCLUDE_FLAGS) -fPIC -o $@ -c $<

###### \IMGUI #####


##### ENGINE WINDOW CLASSES ######

ENGINE_WINDOW_DIR = $(ENGINE_SRC_DIR)/window
ENGINE_WINDOW_SRC_FILES := $(wildcard $(ENGINE_WINDOW_DIR)/*.cpp)
ENGINE_WINDOW_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_WINDOW_SRC_FILES))
ENGINE_OBJ_FILES += $(ENGINE_WINDOW_OBJ_FILES)

# compile platform-specific window implementations (.o files will be stored in engine/src/window)
$(ENGINE_WINDOW_DIR)/%.o : $(ENGINE_WINDOW_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(BUILD_MACROS) -o $@ -c $<

##### \ENGINE WINDOW CLASSES #####

##### ENGINE LAYER CLASSES ######

ENGINE_LAYER_DIR = $(ENGINE_SRC_DIR)/layer
ENGINE_LAYER_SRC_FILES := $(wildcard $(ENGINE_LAYER_DIR)/*.cpp)
ENGINE_LAYER_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_LAYER_SRC_FILES))
ENGINE_OBJ_FILES += $(ENGINE_LAYER_OBJ_FILES)

# compile layer implementations (.o files will be stored in engine/src/layer)
$(ENGINE_LAYER_DIR)/%.o : $(ENGINE_LAYER_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(BUILD_MACROS) -o $@ -c $<

##### \ENGINE WINDOW CLASSES #####

##### ENGINE IMGUI OPENGL RENDERER ######

ENGINE_OPENGL_DIR = $(ENGINE_SRC_DIR)/opengl
ENGINE_OPENGL_SRC_FILES := $(wildcard $(ENGINE_OPENGL_DIR)/*.cpp)
ENGINE_OPENGL_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_OPENGL_SRC_FILES))
ENGINE_OBJ_FILES += $(ENGINE_OPENGL_OBJ_FILES)

# compile ImGUI OPENGL renderer (.o files will be stored in engine/src/opengl)
$(ENGINE_OPENGL_DIR)/%.o : $(ENGINE_OPENGL_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(BUILD_MACROS) -o $@ -c $<

##### \ENGINE IMGUI OPENGL RENDERER #####


##### ENGINE SHARED LIBRARY ######

PRECOMPILED_HEADER_SRC = $(ENGINE_SRC_DIR)/enginepch.h
PRECOMPILED_HEADER_TARGET = $(ENGINE_SRC_DIR)/enginepch.h.gch

# precompile a header file with many common includes
$(PRECOMPILED_HEADER_TARGET) : $(PRECOMPILED_HEADER_SRC)
	$(CC) $(CFLAGS) -x c++-header \
	-fPIC -c $(PRECOMPILED_HEADER_SRC)

ENGINE_INCLUDE_FLAGS = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/src/ \
                       -I$(CURDIR)/engine/external/ \
					   $(GLFW_INCLUDE_FLAGS) \
					   $(GLAD_INCLUDE_FLAGS) \
					   $(IMGUI_INCLUDE_FLAGS)

# compile engine (.o files will be stored in engine/src)
$(ENGINE_SRC_DIR)/%.o : $(ENGINE_SRC_DIR)/%.cpp $(PRECOMPILED_HEADER_TARGET) build_glfw
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(BUILD_MACROS) -o $@ -c $<

# link engine to shared/dynamic library (engine/bin/libengine.so)
build_engine: $(GLAD_OBJ_FILES) $(IMGUI_OBJ_FILES) $(ENGINE_OBJ_FILES)
	$(CC) -o $(ENGINE_LIBRARY) -shared $^ \
	$(GLFW_LINKER_FLAGS) $(LDFLAGS)

##### \ENGINE SHARED LIBRARY #####


##### SANDBOX APP ######

APP_BIN_DIR = $(CURDIR)/app/bin
APP_SRC_DIR = $(CURDIR)/app/src
APP_TARGET  = app

APP_SRC_FILES := $(wildcard $(APP_SRC_DIR)/*.cpp)
APP_OBJ_FILES := $(patsubst %.cpp,%.o,$(APP_SRC_FILES))

APP_INCLUDE_FLAGS = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/src \
                    -I$(CURDIR)/engine/external/

APP_LINKER_FLAGS = -Wl,-rpath $(ENGINE_BIN_DIR) -lengine -L$(ENGINE_BIN_DIR)

debug_app : CFLAGS = $(DEBUG_FLAGS)

debug_app : build_app

# compile app (.o files will be stored in app/src)
$(APP_SRC_DIR)/%.o : $(APP_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(APP_INCLUDE_FLAGS) -o $@ -c $<

# build app (app/bin/app)
build_app: $(APP_OBJ_FILES)
	$(CC) $(CFLAGS) \
	-o $(APP_BIN_DIR)/$(APP_TARGET) $(APP_INCLUDE_FLAGS) $^ \
	$(APP_LINKER_FLAGS)

##### \SANDBOX APP #####


clean:
	rm -rf \
	$(ENGINE_LIBRARY) \
	$(ENGINE_OBJ_FILES) \
	$(PRECOMPILED_HEADER_TARGET) \
	$(APP_BIN_DIR)/$(APP_TARGET) \
	$(APP_OBJ_FILES) \
	$(GLAD_OBJ_FILES) \
	$(IMGUI_OBJ_FILES)

clean_app:
	rm -rf $(APP_BIN_DIR)/$(APP_TARGET) $(APP_OBJ_FILES)
	
.PHONY: all clean clean_app
