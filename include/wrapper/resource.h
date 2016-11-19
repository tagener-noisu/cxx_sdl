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

#ifndef SDL_RESOURCE_H
#define SDL_RESOURCE_H 1
//-------------------------------------------------------------------
//-------------------------------------------------------------------

namespace SDL {

// A base class used as storage for sdl entities e.g. SDL_Window*,
// SDL_Surface* etc.
// Proper destruction should be completed in a descendant class.
//
// Provides operator T() so descendants could be used
// with plain sdl functions.
template<class T>
class Resource {
public:
	Resource(T* r) :res {r} {
	}

	bool valid() const { return res != nullptr; }

	T* get() { return res; }

	void reset() { res = nullptr; }

	inline operator T*() { return res; }

protected:
	T* res;
};

} // namespace
//-------------------------------------------------------------------
#endif
