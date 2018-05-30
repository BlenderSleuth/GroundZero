CC = clang++
SYS := $(shell $(CC) -dumpmachine)

CFLAGS = -std=c++11 -Wall
LDFLAGS = -lraylib

SRC_DIR = src/
SRC = $(wildcard $(SRC_DIR)/*.cpp)

TMP_DIR = tmp/
BUILD_DIR = bin/
ASSET_DIR = assets/
EXECUTABLE = GroundZero
PLATFORM = unknown

DEBUGGER = lldb

ifneq (, $(findstring linux, $(SYS)))
	# Linux
	LDFLAGS += -lglfw
	PLATFORM = linux
else ifneq (, $(findstring w64, $(SYS)))
	# Windows
	CFLAGS += -I"C:/Program Files/raylib/include" -I"C:/Program Files/GLFW/include"
	LDFLAGS += -L"C:/Program Files/raylib/lib" -L"C:/Program Files/GLFW/lib" -lglfw3 -lgdi32 -static -Wl,--allow-multiple-definition
	WINICON = $(ASSET_DIR)icon.res
	EXECUTABLE := $(EXECUTABLE).exe
	PLATFORM = windows
else ifneq (, $(findstring apple, $(SYS)))
	# macOS
	CFLAGS += -mmacosx-version-min=10.10
	LDFLAGS += -lglfw3 -framework CoreVideo -framework IOKit -framework Cocoa -framework OpenGL
	ICON = icon.icns
	PLATFORM = macOS
	DEBUGGER = PATH=/usr/bin /usr/bin/lldb
endif


all:
	@rm -f $(BUILD_DIR)$(EXECUTABLE)
	@$(CC) $(CFLAGS) -o $(BUILD_DIR)$(EXECUTABLE) $(SRC) $(LDFLAGS) $(WINICON)


debug: all
	 @$(DEBUGGER) $(BUILD_DIR)$(EXECUTABLE)

run: all
	@mkdir -p $(TMP_DIR)
	@$(BUILD_DIR)$(EXECUTABLE) > $(TMP_DIR)output.txt

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
	@rm -rf $(BUILD_DIR)$(EXECUTABLE).app;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS;
	@mkdir -p $(BUILD_DIR)$(EXECUTABLE).app/Contents/resources;
	@touch $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@echo "$$INFO" > $(BUILD_DIR)$(EXECUTABLE).app/Contents/Info.plist;
	@cp $(BUILD_DIR)$(EXECUTABLE) $(BUILD_DIR)$(EXECUTABLE).app/Contents/MacOS/$(EXECUTABLE);
	@cp $(ASSET_DIR)$(ICON) $(BUILD_DIR)$(EXECUTABLE).app/Contents/resources/$(ICON);
endif
