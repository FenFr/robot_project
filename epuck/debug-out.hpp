#ifndef	HINKI_DEBUG_OUT_HPP__
#define	HINKI_DEBUG_OUT_HPP__

#include <iostream>
using std::cout;

namespace {

bool debug = false;

class : public std::ostream {
public:
	template <typename T>
	std::ostream &operator<<(T operand)
	{
		if ( !debug ) return *this;
		return cout << __FILE__ << ": " << operand;
	}
} DOUT;

}

#endif
