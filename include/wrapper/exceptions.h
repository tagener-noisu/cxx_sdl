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

#ifndef SDL_EXCEPTIONS_H
#define SDL_EXCEPTIONS_H 1
//-------------------------------------------------------------------
#include <string>
//-------------------------------------------------------------------

namespace SDL {

class Error : public std::exception {
public:
	Error() =default;
	Error(const std::string& s) :msg{s} {}
	Error(std::string&& s) :msg{std::move(s)} {}

	const char* what() const noexcept override {
		return msg.c_str();
	}
private:
	std::string msg;
};


// Interface for the error handling classes
struct ErrorHandler {
	virtual void operator()(std::string) const =0;
};

// Error handler used as template argument for wrapper classes
// Throws SDL::Error
struct Throw : public ErrorHandler {
	Throw() =default;

	void operator()(std::string msg ="") const override {
		throw Error {msg};
	}
};

// Error handler used as template argument for wrapper classes
// Does nothing
struct NoThrow {};

} //namespace
//-------------------------------------------------------------------
#endif
