/*
 The MIT License (MIT)

 Copyright (c) 2016 tagener-noisu

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
*/

#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "wrapper/exceptions.h"
#include "wrapper/window.h"
#include "wrapper/renderer.h"
//-------------------------------------------------------------------

namespace SDL {

template<class ErrorHandler =Throw>
class Sdl {
	ErrorHandler handle_error;
public:
	Sdl(Uint32 flags =0) {
		if (SDL_Init(flags) != 0) handle_error(SDL_GetError());
	}

	~Sdl() {
		SDL_Quit();
	}
};

template<>
class Sdl<NoThrow> {
	int st;
public:
	Sdl(Uint32 flags =0) :st {SDL_Init(flags)} {}

	int state() const { return st; }

	~Sdl() {
		SDL_Quit();
	}
};
} //namespace
//-------------------------------------------------------------------
#endif
