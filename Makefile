SYS := $(shell gcc -dumpmachine)

CC = g++
CFLAGS = -std=c++11 -Wall -Wextra
LDFLAGS = -lraylib

SOURCE_DIR = src/
SOURCE = $(wildcard $(SOURCE_DIR)/*.cpp)

BUILD_DIR = bin/
ASSET_DIR = assets/
EXECUTABLE = GroundZero

PLATFORM =

ifneq (, $(findstring linux, $(SYS)))
  # Linux, link against glfw
  LDFLAGS += -lglfw
  PLATFORM = linux
else ifneq (, $(findstring mingw, $(SYS)))
  # Windows
  LDFLAGS += -lglfw3 -lgdi32
  OTHER += $(ASSET_DIR)winicon
  PLATFORM = win32
else ifneq (, $(findstring apple, $(SYS)))
  # macOS, use gcc not clang
  CC = g++-7
  CFLAGS += -Iinclude
  LDFLAGS = -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL lib/libraylib.a -mmacosx-version-min=10.11
  PLATFORM = macOS
endif

all:
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$(EXECUTABLE) $(SOURCE) $(LDFLAGS) $(OTHER)

define INFO
<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE plist PUBLIC "-//Apple//DTD PLIST 1.0//EN" "http://www.apple.com/DTDs/PropertyList-1.0.dtd">
<plist version="1.0">
<dict>
  <key>CFBundleExecutable</key>
  <string>$(EXECUTABLE)</string>
  <key>CFBundleIconFile</key>
  <string>icon.icns</string>
</dict>
</plist>
endef
export INFO

genapp: all
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/Resources;
	@touch $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@echo "$$INFO" > $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@cp $(BUILD_DIR)$(EXECUTABLE) $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS/$(EXECUTABLE);
	@cp $(ASSET_DIR)icon.icns $(BUILD_DIR)$(EXECUTABLE).app/Contents/resources/icon.icns;

run: all
	@$(BUILD_DIR)$(EXECUTABLE)
