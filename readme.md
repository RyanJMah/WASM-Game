# WASM Valley

A stardew valley clone for fun. Wanted to try out game dev and also web assembly, so
two birds in one stone here.

Can run both natively, and on the browser.

## Dependencies

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

make
```

Note:
* For compiling for wasm, make sure you source `setup_emcc.sh`
  first, it sets up some environment variables


