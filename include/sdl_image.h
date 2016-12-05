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

#ifndef SDL_IMAGE_WRAPPER_H
#define SDL_IMAGE_WRAPPER_H 1
//-------------------------------------------------------------------
#include <SDL_image.h>
#include "wrapper/exceptions.h"
//-------------------------------------------------------------------

namespace SDL {
namespace IMG {

static_assert(SDL_IMAGE_MAJOR_VERSION == 2,
	"Only version 2.x of SDL_image is supported");

class SdlImage {
	int st;
public:
	SdlImage(int flags =0) :st {IMG_Init(flags)} {}

	int state() const { return st; }

	~SdlImage() {
		IMG_Quit();
	}
};

//-------------------------------------------------------------------

inline SDL_Surface* Load(const char* file) {
	return IMG_Load(file);
}

inline SDL_Surface* Load(const char* file, ErrorHandler& handle_error) {
	auto s = IMG_Load(file);
	if (s == nullptr)
		handle_error(SDL_GetError());
	return s;
}

} // namespace
} // namespace
//-------------------------------------------------------------------
#endif
