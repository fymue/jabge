CC = g++
CFLAGS = -Wall -Wextra
RELEASE_FLAGS = -O3 -DNDEBUG
DEBUG_FLAGS = -g
ENGINE_INCLUDE_FLAGS = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/src/ -I$(CURDIR)/engine/external/
APP_INCLUDE_FLAGS = -I$(CURDIR)/engine/ -I$(CURDIR)/engine/external/
BUILD_MACROS="-dBUILD_ENGINE"

ENGINE_BIN_DIR = $(CURDIR)/engine/bin
ENGINE_SRC_DIR = $(CURDIR)/engine/src
ENGINE_TARGET= libengine.so

APP_BIN_DIR = $(CURDIR)/app/bin
APP_SRC_DIR = $(CURDIR)/app/src
APP_TARGET = app

SHELL = /bin/sh

ENGINE_SRC_FILES := $(wildcard $(ENGINE_SRC_DIR)/*.cpp)
ENGINE_OBJ_FILES := $(patsubst %.cpp,%.o,$(ENGINE_SRC_FILES))

APP_SRC_FILES := $(wildcard $(APP_SRC_DIR)/*.cpp)
APP_OBJ_FILES := $(patsubst %.cpp,%.o,$(APP_SRC_FILES))

all: build_engine

# compile engine (.o files will be stored in engine/src)
$(ENGINE_SRC_DIR)/%.o : $(ENGINE_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(ENGINE_INCLUDE_FLAGS) \
	$(DEBUG_FLAGS) -o $@ -c $<

# link engine to shared/dynamic library (engine/bin/libengine.so)
build_engine: $(ENGINE_OBJ_FILES)
	$(CC) -o $(ENGINE_BIN_DIR)/$(ENGINE_TARGET) -shared $(ENGINE_OBJ_FILES)

# compile app (.o files will be stored in app/src)
$(APP_SRC_DIR)/%.o : $(APP_SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -fPIC $(APP_INCLUDE_FLAGS) \
	$(DEBUG_FLAGS) -o $@ -c $<

# build app (app/bin/app) (LD_LIBRARY_PATH still needs to be set)
build_app: $(APP_OBJ_FILES)
	$(CC) -lengine -L$(ENGINE_BIN_DIR) \
	-o $(APP_BIN_DIR)/$(APP_TARGET) $(APP_INCLUDE_FLAGS) $(APP_OBJ_FILES)

clean:
	rm -rf $(ENGINE_BIN_DIR)/$(ENGINE_TARGET) \
	$(ENGINE_SRC_DIR)/*.o $(APP_SRC_DIR)/*.o \
	$(APP_BIN_DIR)/$(APP_TARGET)
	
.PHONY: all clean
