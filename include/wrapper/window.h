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

	Window(const Window&) =delete;

	Window& operator=(const Window&) =delete;

	~Window() { if (this->res) destroy(); }

	inline void destroy() {
		SDL_DestroyWindow(this->res);
		this->res = nullptr;
	}
};

template<>
class Window<NoThrow> : public BaseWindow_, public Resource<SDL_Window> {
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
