# SDL wrapper library for C++11

A sdl wrapper library organized as header files.
Work in progress, any forms of contribution are welcome.

## Features
* Wrapper classes using RAII
* Wrapper classes use conversion operators so they can be used in vanilla
SDL functions
* Functions that works on an object become members of the corresponding class
e.g. `SDL_RendererClear` can be called like this: `r.clear()` where `r` is an
instance of the class `SDL::Renderer` (member functions use lowercase with
underscores as a naming policy `object.long_func_name`)
* Global functions e.g. `SDL\_Delay` are now in namespace and can be
accessed like that: `SDL::Delay` (case is the same `SDL::DoSomethingUseful`)
* All functions inlined
* Custom error handling with functors accepted by overloaded functions
_functor is an object with an overloaded operator()()_
* Default error handlers

## How to:
1. Download or clone
2. `#include` `"sdl\_wrapper.h"`, `"sdl\_image.h"` etc.
3. Add `include/` to your compiler include path, e.g. `g++ test.cpp -Iinclude`
4. Compile
