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

class BaseWindow_ {
};

template<class ErrorHandler = Throw>
class Window : public BaseWindow_, public Resource<SDL_Window> {
	ErrorHandler handle_error;
public:
	Window(const char* title, int x, int y, int w, int h, Uint32 flags)
	:Resource {SDL_CreateWindow(title, x, y, w, h, flags)}
	{
		if (!this->valid()) handle_error();
	}

	Window(Window&& other)
	:Resource {nullptr}
	{
		std::swap(other.res, this->res);
		if (!this->valid()) handle_error();
	}

	template<class T>
	Window(Window<T>&& other)
	:Resource {nullptr}
	{
		this->res = other.get();
		other.reset();
		if (!this->valid()) handle_error();
	}

	Window(const Window&) =delete;

	Window& operator=(const Window&) =delete;

	~Window() { if (this->res) destroy(); }

	inline void destroy() {
		SDL_DestroyWindow(this->res);
		this->res = nullptr;
	}
};

template<>
class Window<NoChecking> : public BaseWindow_, public Resource<SDL_Window> {
public:
	Window(const char* title, int x, int y, int w, int h, Uint32 flags)
	:Resource {SDL_CreateWindow(title, x, y, w, h, flags)}
	{
	}

	Window(Window&& other)
	:Resource {nullptr}
	{
		std::swap(other.res, this->res);
	}

	template<class T>
	Window(Window<T>&& other)
	:Resource {nullptr}
	{
		this->res = other.get();
		other.reset();
	}

	Window(const Window&) =delete;

	Window& operator=(const Window&) =delete;

	~Window() { if (this->res) destroy(); }

	inline void destroy() {
		SDL_DestroyWindow(this->res);
		this->res = nullptr;
	}
};

} // namespace
//-------------------------------------------------------------------
#endif
