SYS := $(shell gcc -dumpmachine)

CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lraylib

SOURCE_DIR = src/
SOURCE = $(wildcard $(SOURCE_DIR)/*.cpp)

BUILD_DIR = bin/
ASSET_DIR = assets/
EXECUTABLE = GroundZero
PLATFORM = unknown

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw
  PLATFORM = linux
else ifneq (, $(findstring mingw, $(SYS)))
  # Windows
  LDFLAGS += -lglfw3 -lgdi32
  WINICON = $(ASSET_DIR)icon.res
  PLATFORM = win32
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = g++-7
  CFLAGS += -Iinclude -mmacosx-version-min=10.11
  LDFLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL lib/libraylib.a
  ICON = icon.icns
  PLATFORM = macOS
endif

all:
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$(EXECUTABLE) $(SOURCE) $(LDFLAGS) $(WINICON)

define INFO
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleExecutable</key>
  <string>$(EXECUTABLE)</string>
  <key>CFBundleIconFile</key>
  <string>$(ICON)</string>
</dict>
</plist>
endef
export INFO

genapp: all
ifeq ($(PLATFORM), macOS)
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/Resources;
	@touch $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@echo "$$INFO" > $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@cp $(BUILD_DIR)$(EXECUTABLE) $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS/$(EXECUTABLE);
	@cp $(ASSET_DIR)$(ICON) $(BUILD_DIR)$(EXECUTABLE).app/Contents/resources/$(ICON);
endif

run: all
	@$(BUILD_DIR)$(EXECUTABLE)
