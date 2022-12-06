#include "BtSocketBlock.hpp"
#include <unistd.h>			// close
#include <sys/types.h>
#include <sys/socket.h>
#include <bluetooth/bluetooth.h>	// bdaddr_t
#include <bluetooth/rfcomm.h>		// sockaddr_rc

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

#include <errno.h>

namespace gui
{

BtSocketBlock::BtSocketBlock()
{
	sock = ::socket( AF_BLUETOOTH, SOCK_STREAM,
			BTPROTO_RFCOMM );
	if( sock != -1 ) return;
	cout << "errno " << errno << endl;
	throw runtime_error( "Bluetooth socket creation failed" );
}

BtSocketBlock::~BtSocketBlock() { close( sock ); }

int BtSocketBlock::connect( sockaddr_rc &a )
{
	return ::connect( sock,
			reinterpret_cast<sockaddr *>( &a ),
			sizeof( a ) );
}

size_t BtSocketBlock::read( void *buf, size_t count )
{ return ::read( sock, buf, count ); }

size_t BtSocketBlock::write( const void *buf, size_t count )
{ return ::write( sock, buf, count ); }

int BtSocketBlock::socket() const { return sock; }

}
