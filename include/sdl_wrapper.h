#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H 1
//-------------------------------------------------------------------
#include <SDL.h>
#include "wrapper/exceptions.h"
#include "wrapper/window.h"
//-------------------------------------------------------------------

namespace SDL {

template<class ErrorHandler =Throw>
class SDL {
	ErrorHandler handle_error();
public:
	SDL(Uint32 flags =0) {
		if (SDL_Init(flags) != 0) handle_error(SDL_GetError());
	}

	~SDL() {
		SDL_Quit();
	}
};

template<>
class SDL<NoThrow> {
	int st;
public:
	SDL(Uint32 flags =0) :st {SDL_Init(flags)} {}

	int state() const { return st; }

	~SDL() {
		SDL_Quit();
	}
};
} //namespace
//-------------------------------------------------------------------
#endif
