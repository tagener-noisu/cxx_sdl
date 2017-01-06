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

class Texture : public Resource<SDL_Texture> {
public:
	Texture(SDL_Texture* t) :Resource {t} {}

	Texture(SDL_Texture* t, ErrorHandler& handle_error) :Resource {t}
	{
		if (!this->valid())
			handle_error("Texture created from null pointer");
	}

	Texture(SDL_Renderer* r, Uint32 format, int access, int w, int h)
	:Resource {SDL_CreateTexture(r, format, access, w, h)}
	{
	}

	Texture(
		SDL_Renderer* r,
		Uint32 format,
		int access,
		int w,
		int h,
		ErrorHandler& handle_error)
	:Resource {SDL_CreateTexture(r, format, access, w, h)}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Texture(SDL_Renderer* r, SDL_Surface* s)
	:Resource {SDL_CreateTextureFromSurface(r, s)}
	{
	}

	Texture(SDL_Renderer* r, SDL_Surface* s, ErrorHandler& handle_error)
	:Resource {SDL_CreateTextureFromSurface(r, s)}
	{
		if (!this->valid()) handle_error(SDL_GetError());
	}

	Texture(Texture&& other)
	:Resource {nullptr}
	{
		std::swap(this->resource(), other.resource());
	}

	Texture(const Texture&) =delete;

	Texture& operator=(const Texture&) =delete;

	inline int query(Uint32* format, int* access, int* w, int* h) {
		return SDL_QueryTexture(Resource::get(), format, access, w, h);
	}

	inline int query(
		Uint32* format,
		int* access,
		int* w,
		int* h,
		ErrorHandler& handle_error)
	{
		int status = SDL_QueryTexture(Resource::get(), format, access, w, h);
		if (status != 0)
			handle_error(SDL_GetError());
		return status;
	}

	// TODO: write overloads with error handlers
	inline int set_color_mod(Uint8 r, Uint8 g, Uint8 b) {
		return SDL_SetTextureColorMod(Resource::get(), r, g, b);
	}

	inline int get_color_mod(Uint8* r, Uint8* g, Uint8* b) {
		return SDL_GetTextureColorMod(Resource::get(), r, g, b);
	}

	inline int set_alpha_mod(Uint8 alpha) {
		return SDL_SetTextureAlphaMod(Resource::get(), alpha);
	}

	inline int get_alpha_mod(Uint8* alpha) {
		return SDL_GetTextureAlphaMod(Resource::get(), alpha);
	}

	inline int set_blend_mode(SDL_BlendMode bm) {
		return SDL_SetTextureBlendMode(Resource::get(), bm);
	}

	inline int get_blend_mode(SDL_BlendMode* bm) {
		return SDL_GetTextureBlendMode(Resource::get(), bm);
	}
};

} //namespace
//-------------------------------------------------------------------
#endif
