#include "BtConn.hpp"
#include "BtSocket.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>
#include <bluetooth/rfcomm.h>

#include <errno.h>

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

namespace { bool debug = false; }

#define DOUT if ( debug ) cout << __FILE__

namespace gui
{

BtConn::BtConn( const bdaddr_t ba )
{
	sockaddr_rc adr;
	adr.rc_family  = AF_BLUETOOTH;
	adr.rc_channel = 1;
	adr.rc_bdaddr  = ba;
	DOUT << " trying BT connection\n";
	cout << "prepare to provide a pin\n";
	if ( s.connect( adr ) != -1 )
		throw runtime_error( "something is horribly wrong!"
			"\n\nRUN!\n\n RUN FAST!\n\n" );
	if ( errno != EINPROGRESS )
	{
		cout << "errno " << errno << endl;
		throw runtime_error("rfcomm layer "
				"connection failed");
	}
	DOUT << ": waiting for Bluetooth connection\n";
	switch ( waitForConnection() )
	{
		case  0: cout << "btconn select timed out\n";
		case -1: throw runtime_error( "select" );
	}
	DOUT << ": bluetooth connection established\n";
}

size_t BtConn::read( void *buf, size_t count )
{ return s.read( buf, count ); }

size_t BtConn::write( const void *buf, size_t count )
{ return s.write( buf, count ); }

// erstmal würg-around
/* man 2 select:
 * If timeout is NULL (no timeout), select() can block indefinitely.
 */
int BtConn::waitForConnection()
{
	FD_ZERO( &set );
	FD_SET( s.socket(), &set );
	return s.select( 0, &set, 0 );
}

int BtConn::writePossible( int sec )
{
	timeval t = { sec, 0 };
	FD_ZERO( &set );
	FD_SET( s.socket(), &set );
	return s.select( 0, &set, &t );
}

//TODO: besser beschreiben
int BtConn::nextReadPossible()
{
	timeval t = { 0, 100000 };
	FD_ZERO( &set );
	FD_SET( s.socket(), &set );
	return s.select( &set, 0, &t );
}

int BtConn::readPossible( int sec )
{
	timeval t = { sec, 0 };
	FD_ZERO( &set );
	FD_SET( s.socket(), &set );
	return s.select( &set, 0, &t );
}

}
