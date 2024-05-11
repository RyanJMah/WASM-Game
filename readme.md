# WASM Valley

A stardew valley clone for fun. Wanted to try out game dev and also web assembly, so
two birds in one stone here.

Can run both natively, and on the browser.

## Dependencies

* `python3`
* `sdl2`
* `wabt`
* `entr`

First, set up wasm compiler and install script dependencies.

```bash
source ./scripts/emcc_setup.sh

pip3 install -r requirements.txt
```

### MacOS

```bash
brew install sdl2 wabt entr
```

### Debian Linux

```bash
sudo apt install libsdl2-dev wabt entr
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

Run `./serve_wasm.sh` then go to http://localhost:8080 on your browser.

```bash
./scripts/serve_wasm.sh
```

### Native

```bash
./build/main
```
