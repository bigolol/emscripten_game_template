::set this to the location of emsd_env
call D:\emsdk\emsdk_env.bat 
::generate only js, supply your own html
::call emcc main.cpp --bind -s WASM=1 -s  -o main.js --preload-file assets --use-preload-plugins
::generate html by emscripten
call emcc main.cpp -s WASM=1 -s -o build/main.html
