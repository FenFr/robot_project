#ifndef	HINKI_BTCONN_HPP__
#define	HINKI_BTCONN_HPP__

#include "BtSocket.hpp"
#include <bluetooth/bluetooth.h>	// bdaddr_t

namespace gui
{

class BtConn
{
	BtSocket	s;
	fd_set	set;

	int waitForConnection();
public:
	BtConn( const bdaddr_t bluetoothAddress );
	int readPossible( int seconds );
	int nextReadPossible();
	int writePossible( int seconds );
	size_t read( void *buf, size_t count );
	size_t write( const void *buf, size_t count );
};

}

#endif
