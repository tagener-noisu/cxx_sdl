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

#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "exceptions.h"
#include "resource.h"
//-------------------------------------------------------------------

namespace SDL {

class BaseRenderer_ : public Resource<SDL_Renderer> {
protected:
	BaseRenderer_(SDL_Renderer* r) :Resource {r} {}

public:
	inline int clear() {
		return SDL_RenderClear(this->res);
	}

	inline int copy(
		SDL_Texture* t,
		const SDL_Rect* src,
		const SDL_Rect* dst)
	{
		return SDL_RenderCopy(this->res, t, src, dst);
	}

	inline void present() {
		SDL_RenderPresent(this->res);
	}

	inline void destroy() {
		if (this->res) {
			SDL_DestroyRenderer(this->res);
			this->res = nullptr;
		}
	}

	inline int get_info(SDL_RendererInfo* info) {
		return SDL_GetRendererInfo(this->res, info);
	}

	inline int get_output_size(int* w, int* h) {
		return SDL_GetRendererOutputSize(this->res, w, h);
	}
};

template<class ErrorHandler = Throw>
class Renderer : public BaseRenderer_ {
	ErrorHandler handle_error;
public:
	Renderer(SDL_Renderer* r) :BaseRenderer_ {r} {
		if (!this->valid()) handle_error();
	}

	Renderer(SDL_Window* w, int i, Uint32 flags)
	:BaseRenderer_ {SDL_CreateRenderer(w, i, flags)}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Renderer(Renderer&& other)
	:BaseRenderer_ {nullptr}
	{
		std::swap(other.res, this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	template<typename T>
	Renderer(Renderer<T>&& other)
	:BaseRenderer_ {nullptr}
	{
		std::swap(other.get(), this->res);
		if (!this->valid()) handle_error("Move from invalid object");
	}

	Renderer(const Renderer&) =delete;

	Renderer& operator=(const Renderer&) =delete;

	~Renderer() { this->destroy(); }
};

template<>
class Renderer<NoChecking> : public BaseRenderer_ {
public:
	Renderer(SDL_Renderer* r) :BaseRenderer_ {r} {}

	Renderer(SDL_Window* w, int i, Uint32 flags)
	:BaseRenderer_ {SDL_CreateRenderer(w, i, flags)}
	{
	}

	Renderer(Renderer&& other)
	:BaseRenderer_ {nullptr}
	{
		std::swap(other.res, this->res);
	}

	template<typename T>
	Renderer(Renderer<T>&& other)
	:BaseRenderer_ {nullptr}
	{
		std::swap(other.get(), this->res);
	}

	Renderer(const Renderer&) =delete;

	Renderer& operator=(const Renderer&) =delete;

	~Renderer() { this->destroy(); }
};

using SafeRenderer = Renderer<Throw>;
using UnsafeRenderer = Renderer<NoChecking>;

} // namespace
//-------------------------------------------------------------------
#endif
