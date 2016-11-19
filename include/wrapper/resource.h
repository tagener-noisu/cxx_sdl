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

	inline operator T*() { return res; }

protected:
	T* res;
};

} // namespace
//-------------------------------------------------------------------
#endif
