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

class Renderer : public Resource<SDL_Renderer> {
public:
	enum Driver {
		ANY=-1
	};
	Renderer(SDL_Renderer* r) :Resource {r} {}

	Renderer(SDL_Renderer* r, ErrorHandler& handle_error) :Resource {r}
	{
		if (!this->valid())
			handle_error("Renderer created from null pointer");
	}

	Renderer(SDL_Window* w, int i, Uint32 flags)
	:Resource {SDL_CreateRenderer(w, i, flags)}
	{
	}

	Renderer(SDL_Window* w, int i, Uint32 flags, ErrorHandler& handle_error)
	:Resource {SDL_CreateRenderer(w, i, flags)}
	{
		if (!this->valid())
			handle_error(SDL_GetError());
	}

	Renderer(Renderer&& other)
	:Resource {nullptr}
	{
		std::swap(this->resource(), other.resource());
	}

	Renderer(const Renderer&) =delete;

	Renderer& operator=(const Renderer&) =delete;

	inline int clear() {
		return SDL_RenderClear(Resource::get());
	}

	inline int clear(ErrorHandler& handle_error) {
		int status = SDL_RenderClear(Resource::get());
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline int copy(
		SDL_Texture* t,
		const SDL_Rect* src,
		const SDL_Rect* dst)
	{
		return SDL_RenderCopy(Resource::get(), t, src, dst);
	}

	inline int copy(
		SDL_Texture* t,
		const SDL_Rect* src,
		const SDL_Rect* dst,
		ErrorHandler& handle_error)
	{
		int status = SDL_RenderCopy(Resource::get(), t, src, dst);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline int copy_ex(
		SDL_Texture* t,
		const SDL_Rect* src,
		const SDL_Rect* dst,
		double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip)
	{
		return SDL_RenderCopyEx(Resource::get(), t, src, dst, angle,
			center, flip);
	}

	inline int copy_ex(
		SDL_Texture* t,
		const SDL_Rect* src,
		const SDL_Rect* dst,
		double angle,
		const SDL_Point* center,
		const SDL_RendererFlip flip,
		ErrorHandler& handle_error)
	{
		int status = SDL_RenderCopyEx(Resource::get(), t, src, dst,
				angle, center, flip);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline void present() {
		SDL_RenderPresent(Resource::get());
	}

	inline void fill_rect(const SDL_Rect* r) {
		SDL_RenderFillRect(Resource::get(), r);
	}

	inline int set_draw_color(
		Uint8 r,
		Uint8 g,
		Uint8 b,
		Uint8 a)
	{
		return SDL_SetRenderDrawColor(Resource::get(), r, g, b, a);
	}

	inline int set_draw_color(
		Uint8 r,
		Uint8 g,
		Uint8 b,
		Uint8 a,
		ErrorHandler& handle_error)
	{
		int status = SDL_SetRenderDrawColor(Resource::get(), r, g, b, a);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline int get_draw_color(
		Uint8* r,
		Uint8* g,
		Uint8* b,
		Uint8* a)
	{
		return SDL_GetRenderDrawColor(Resource::get(), r, g, b, a);
	}

	inline int get_draw_color(
		Uint8* r,
		Uint8* g,
		Uint8* b,
		Uint8* a,
		ErrorHandler& handle_error)
	{
		int status = SDL_GetRenderDrawColor(Resource::get(), r, g, b, a);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline int get_info(SDL_RendererInfo* info) {
		return SDL_GetRendererInfo(Resource::get(), info);
	}

	inline int get_info(
		SDL_RendererInfo* info,
		ErrorHandler& handle_error)
	{
		int status = SDL_GetRendererInfo(Resource::get(), info);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	inline int get_output_size(int* w, int* h) {
		return SDL_GetRendererOutputSize(Resource::get(), w, h);
	}

	inline int get_output_size(
		int* w,
		int* h,
		ErrorHandler& handle_error)
	{
		int status = SDL_GetRendererOutputSize(Resource::get(), w, h);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}
};

} // namespace
//-------------------------------------------------------------------
#endif
