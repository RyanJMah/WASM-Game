# WASM Valley

A stardew valley clone for fun. Wanted to try out game dev and also web assembly, so
two birds in one stone here.

Can run both natively, and on the browser.

## Dependencies

* `python3`
* `sdl2`
* `wabt`

First, set up wasm compiler.

```bash
source ./emcc_setup.sh
```

### MacOS

```bash
brew install sdl2 wabt
```

### Debian Linux

```bash
sudo apt install libsdl2-dev wabt
```

## Build

```bash
# To build natively
export TARGET_PLATFORM=native

# To build for browser
export TARGET_PLATFORM=wasm

# For MacOS
export OS_TYPE=macos

# For Linux
export OS_TYPE=linux

make
```

Note:
* For compiling for wasm, make sure you source `setup_emcc.sh`
  first, it sets up some environment variables


## Run

### WASM

```bash
cd build

python3 -m http.server
```

For development, installing [entr](https://github.com/clibs/entr) is recommended.
It will auto-restart the server whenever you re-build.

```bash
cd build

ls --color=never | entr -r python3 -m http.server
```

### Native

```bash
./build/main
```

