#ifndef	EPUCK_TYPES_HPP__
#define	EPUCK_TYPES_HPP__

#include <iostream>	// std::cout
#include <string>	// std::string
#include <sstream>
using std::stringstream;
#include <stdexcept>
using std::runtime_error;

namespace gui {
namespace robots {
namespace epuck {

	typedef int EpuckID;

	using std::string;

	//TODO: these should be vectors
	template <int size>
	struct IntFeld{
		int data[size];
		IntFeld()
		{
			for ( int i = 0; i < size; i++ )
				data[i] = 0;
		}
	public:
		void print( const string &header = "" )
		{
			using std::cout;
			using std::endl;

			cout << header;
			for ( int i = 0; i < size; i++ )
				cout << data[i] << " ";
			cout << endl;
		}
	};

namespace {
void eatAndCheckNextChar( stringstream &s, char c )
{
	if ( s.get() != c )
		throw runtime_error( "wrong char" );
}
}

//iterate over p to assign result.data[i]
template <int n>
IntFeld<n> parseIntFeldN( string &p, char c )
{
	stringstream s( p );
	eatAndCheckNextChar( s, c );
	IntFeld<n> result;
	for ( int i = 0; i < n; i++ )
	{
		eatAndCheckNextChar( s, ',' );
		s >> result.data[i];
	}
	eatAndCheckNextChar( s, '\r' );
	eatAndCheckNextChar( s, '\n' );
	return result;
}

}}}

namespace gui {
namespace robots {
namespace epuck {
namespace led {

	enum LEDState
	{
		Off = 0,	// perhaps there's a better approach
		On,
		Toggle
	};

}}}}

#endif
