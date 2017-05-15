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

#ifndef SDL_SURFACE_H
#define SDL_SURFACE_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "resource.h"
#include "exceptions.h"
//-------------------------------------------------------------------

namespace SDL {

class Surface : public Resource<SDL_Surface> {
public:
	Surface(SDL_Surface* s) :Resource {s} {}

	Surface(SDL_Surface* s, ErrorHandler& handle_error) :Resource {s}
	{
		if (!this->valid())
			handle_error("Surface created from null pointer");
	}

	Surface(Surface&& other)
	:Resource {nullptr}
	{
		std::swap(this->resource(), other.resource());
	}

	Surface(const Surface&) =delete;
	Surface& operator=(const Surface&) =delete;
};

inline SDL_Surface* LoadBMP(const char* s) {
	return SDL_LoadBMP(s);
}

inline SDL_Surface* LoadBMP(const char* s, ErrorHandler&& error_handler) {
	auto surface = SDL_LoadBMP(s);
	if (surface == nullptr)
		error_handler(SDL_GetError());
	return surface;
}

} //namespace
//-------------------------------------------------------------------
#endif
