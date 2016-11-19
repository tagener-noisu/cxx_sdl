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

#ifndef SDL_TEXTURE_H
#define SDL_TEXTURE_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "resource.h"
#include "exceptions.h"
//-------------------------------------------------------------------

namespace SDL {

class BaseTexture_ : public Resource<SDL_Texture> {
protected:
	BaseTexture_(SDL_Texture* t) :Resource {t} {}

public:
	inline int query(Uint32* format, int* access, int* w, int* h) {
		return SDL_QueryTexture(this->res, format, access, w, h);
	}

	inline void destroy() {
		SDL_DestroyTexture(this->res);
		this->res = nullptr;
	}
};

template<class ErrorHandler = Throw>
class Texture : public BaseTexture_ {
	ErrorHandler handle_error;
public:
	Texture(SDL_Texture* t)
	:BaseTexture_ {t}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Texture(Texture&& other)
	:BaseTexture_ {nullptr}
	{
		std::swap(other.res, this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	template<typename T>
	Texture(Texture<T>&& other)
	:BaseTexture_ {nullptr}
	{
		std::swap(other.get(), this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	Texture(const Texture&) =delete;

	Texture& operator=(const Texture&) =delete;

	~Texture() { if (this->res) this->destroy(); }
};

template<>
class Texture<NoChecking> : public BaseTexture_ {
public:
	Texture(SDL_Texture* t)
	:BaseTexture_ {t}
	{
	}

	Texture(Texture&& other)
	:BaseTexture_ {nullptr}
	{
		std::swap(other.res, this->res);
	}

	template<typename T>
	Texture(Texture<T>&& other)
	:BaseTexture_ {nullptr}
	{
		std::swap(other.get(), this->res);
	}

	Texture(const Texture&) =delete;

	Texture& operator=(const Texture&) =delete;

	~Texture() { if (this->res) this->destroy(); }
};

using SafeTexture = Texture<Throw>;
using UnsafeTexture = Texture<NoChecking>;

} //namespace
//-------------------------------------------------------------------
#endif
