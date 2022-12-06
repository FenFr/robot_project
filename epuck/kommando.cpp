//TODO: sinnvolle eigene ausnahmen definieren
#include <stdexcept>
using std::runtime_error;

#include "debug-out.hpp"	// DOUT

#include <string>
using std::string;

#include <cstdio>		// sprintf

static char uppercase( char c )
{
	if ( c < 'a' || c > 'z' )
		throw runtime_error( "Kein Kleinbuchstabe" );
	return c - 'a' + 'A';
}

namespace gui {
namespace robots {
namespace epuck {

string baueBinaerKommando( char c )
{
	string s( 1, -uppercase( c ) );
	DOUT << -s[0];
	s += "\0\n";
	return s;
}

string baueKommando( char c )
{
	char cmd[1+0*(1+11)+1+1];
	sprintf( cmd, "%c\n", uppercase ( c ) );
	string s( cmd );
	return s;
}

string baueKommando( char c, int w1 )
{
	char cmd[1+1*(1+11)+1+1];
	sprintf( cmd, "%c,%d\n", uppercase ( c ), w1 );
	string s( cmd );
	return s;
}

string baueKommando( char c, int w1, int w2 )
{
	// maximum length of a dezimal 32 bit int:
	// 10 digits: -2^31 == -2*10^10
	// +1 sign => 11 chars.
	// +1 command char, +2 commas, +1 \n, +1 \0
	char cmd[1+2*(1+11)+1+1];
	sprintf( cmd, "%c,%d,%d\n", uppercase ( c ), w1, w2 );
	string s( cmd );
	return s;
}

}}}
