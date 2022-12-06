#ifndef	HINKI_BTSTOCKETBLOCK__
#define	HINKI_BTSTOCKETBLOCK__

#include <sys/types.h>	// size_t

struct sockaddr_rc;

namespace gui
{

class BtSocketBlock
{
	int sock;
public:
	BtSocketBlock();
	~BtSocketBlock();
	int socket() const;
	int connect( sockaddr_rc &zieladresse );
	size_t read( void *buf, size_t count );
	size_t write( const void *buf, size_t count );
};

}

#endif
