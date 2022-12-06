#include "BtSocket.hpp"

#include <unistd.h>		// read, write, close
#include <sys/types.h>		// see man 2 socket
#include <sys/socket.h>		// socket
#include <bluetooth/bluetooth.h>// BTPROTO_RFCOMM
#include <bluetooth/rfcomm.h>	// sockaddr_rc

#include <errno.h>	// errno

//TODO: provide specialized exception
#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

namespace gui
{

BtSocket::BtSocket()
{
	sock = ::socket( AF_BLUETOOTH,
		SOCK_STREAM|SOCK_NONBLOCK, BTPROTO_RFCOMM );
	if( sock != -1 ) return;
	cout << "errno" << errno << endl;
	throw runtime_error( "Bluetooth socket "
				"creation failed" );
}

BtSocket::~BtSocket() { close( sock ); }

int BtSocket::connect( sockaddr_rc &a )
{
	return ::connect( sock,
			reinterpret_cast<sockaddr *>( &a ),
			sizeof( a ) );
}

int BtSocket::select( fd_set *r, fd_set *w, timeval *t )
{ return ::select( sock + 1, r, w, 0, t ); }

size_t BtSocket::read( void *buf, size_t count )
{ return ::read( sock, buf, count ); }

size_t BtSocket::write( const void *buf, size_t count )
{ return ::write( sock, buf, count ); }

int BtSocket::socket() const { return sock; }

}
