#ifndef	HINKI_BTSOCKET_HPP__
#define	HINKI_BTSOCKET_HPP__

#include <sys/types.h>	// size_t

struct sockaddr_rc;

namespace gui
{

class BtSocket
{
	int sock;
public:
	BtSocket();
	~BtSocket();
	int socket() const;
	int connect( sockaddr_rc &zieladresse );
	int select( fd_set *r, fd_set *w, timeval *t );
	size_t read( void *buf, size_t count );
	size_t write( const void *buf, size_t count );
};

}

#endif
