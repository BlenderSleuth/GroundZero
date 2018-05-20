# How to build Ground Zero

### Dependencies:
- Build Environment: 
	+ Windows:

	   Download [MSYS2](https://www.msys2.org/) and follow the instructions to install it. You will need clang from the installed pacman.
	+ macOS:

	   Guess what, you'll need Xcode :)
	+ Linux:

	   Install clang from your local package manager (or from source if you really want to).

- [GLFW](https://github.com/glfw/glfw) and [Raylib](https://github.com/raysan5/raylib):
Download both of these repos. First build GLFW by running `cmake .` then `make`. I recommend installing with `[sudo] make install` to a directory in your PATH. This should build and install the static version.
Then you need to build raylib, so run `cmake . -DUSE_EXTERNAL_GLFW=TRUE -Dglfw3_dir='PATH/TO/GLFW'`, then `make`, and if you like `[sudo] make install`.

Then, so long as everything is in the right spot (at least in the path), run `make run` in GroundZero.