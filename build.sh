
SDL_FLAGS=$(/usr/local/bin/sdl2-config --cflags  --libs --static-libs)
gcc src/*.c -Iinclude/ $SDL_FLAGS # -g -fsanitize=address,undefined -fno-omit-frame-pointer