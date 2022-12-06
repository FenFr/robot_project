#ifndef	HINKI_EPUCK_BTCONNBLOCK__
#define	HINKI_EPUCK_BTCONNBLOCK__

#include "BtSocketBlock.hpp"
#include "EpuckTypes.hpp"
using gui::robots::epuck::EpuckID;

#include <bluetooth/bluetooth.h>	// bdaddr_t

namespace gui
{

class BtConnBlock
{
	// implicit destructor implicitly closes the socket
	BtSocketBlock s;
public:
	BtConnBlock( const bdaddr_t ba );
	size_t readline( char *begin, size_t len );
	size_t read( char *begin, int len );
	size_t write( const char *begin, int len );
};

}

#endif
