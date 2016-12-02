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

class BaseSurface_ : public Resource<SDL_Surface> {
protected:
	BaseSurface_(SDL_Surface* s) :Resource {s} {}

	~BaseSurface_() { destroy(); }

public:
	void destroy() override {
		if (this->res) {
			SDL_FreeSurface(this->res);
			this->res = nullptr;
		}
	}
};

template<class ErrorHandler = Throw>
class Surface : public BaseSurface_ {
	ErrorHandler handle_error;
public:
	Surface(SDL_Surface* t)
	:BaseSurface_ {t}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Surface(Surface&& other)
	:BaseSurface_ {nullptr}
	{
		std::swap(other.res, this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	template<typename T>
	Surface(Surface<T>&& other)
	:BaseSurface_ {nullptr}
	{
		std::swap(other.get(), this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	Surface(const Surface&) =delete;

	Surface& operator=(const Surface&) =delete;
};

template<>
class Surface<NoChecking> : public BaseSurface_ {
public:
	Surface(SDL_Surface* t)
	:BaseSurface_ {t}
	{
	}

	Surface(Surface&& other)
	:BaseSurface_ {nullptr}
	{
		std::swap(other.res, this->res);
	}

	template<typename T>
	Surface(Surface<T>&& other)
	:BaseSurface_ {nullptr}
	{
		std::swap(other.get(), this->res);
	}

	Surface(const Surface&) =delete;

	Surface& operator=(const Surface&) =delete;
};

using SafeSurface = Surface<Throw>;
using UnsafeSurface = Surface<NoChecking>;

} //namespace
//-------------------------------------------------------------------
#endif
