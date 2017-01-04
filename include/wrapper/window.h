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

#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "exceptions.h"
#include "resource.h"
//-------------------------------------------------------------------

namespace SDL {

class Window : public Resource<SDL_Window> {
public:
	Window(SDL_Window* w) :Resource {w} {}

	Window(SDL_Window* w, ErrorHandler& handle_error) :Resource {w}
	{
		if (!this->valid())
			handle_error("Window created from null pointer");
	}

	Window(const char* title, int x, int y, int w, int h, Uint32 flags)
	:Resource {SDL_CreateWindow(title, x, y, w, h, flags)}
	{
	}

	Window(
		const char* title,
		int x,
		int y,
		int w,
		int h,
		Uint32 flags,
		ErrorHandler& handle_error)
		:Resource {SDL_CreateWindow(title, x, y, w, h, flags)}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Window(Window&& other)
	:Resource {nullptr}
	{
		std::swap(this->resource(), other.resource());
	}

	Window(const Window&) =delete;

	Window& operator=(const Window&) =delete;

	inline SDL_Renderer* get_renderer() {
		return SDL_GetRenderer(Resource::get());
	}
};

} // namespace
//-------------------------------------------------------------------
#endif
