#include "BtConnBlock.hpp"
#include "BtSocketBlock.hpp"

// For bluetooth communication
#include <sys/types.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

namespace { bool debug = false; }

#define	DOUT if ( debug ) cout << __FILE__

namespace gui
{

BtConnBlock::BtConnBlock( const bdaddr_t ba )
{
	sockaddr_rc adr;
	adr.rc_family  = AF_BLUETOOTH;
	adr.rc_channel = 1;
	adr.rc_bdaddr  = ba;
	DOUT << " trying BT connection\n";
	cout << "prepare to provide a pin\n";
	if ( s.connect( adr ) != 0 )
		throw runtime_error("rfcomm layer connection failed");
	DOUT << ": bluetooth connection established\n";
}

size_t BtConnBlock::read( char *begin, int len )
{ return s.read( begin, len ); }

size_t BtConnBlock::write( const char *begin, int len )
{ return s.write( begin, len ); }

size_t BtConnBlock::readline( char *begin, size_t l )
{
	size_t offs = 0;
	while ( offs < l && s.read( &begin[offs], 1 ) == 1 )
	{
		if( begin[offs++] == '\n' )
			return offs;
	}
	return 0;	// Error!
}

}
