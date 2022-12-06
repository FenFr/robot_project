#include "EpuckBtLook.hpp"

#include <unistd.h>	// close

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

#include <bluetooth/bluetooth.h>	// bdaddr_t

namespace { bool debug = false; }

#define DOUT if ( debug ) cout << __FILE__ << ": "

namespace gui
{
	bdaddr_t str2ba( const char *macAddress )
	{
		bdaddr_t ba;
		str2ba( macAddress, &ba );
		return ba;
	}

	bdaddr_t lookupEpuck( const EpuckID id )
	{
		const char	*macAddress=0;
		switch( id )
		{
			case 1433: macAddress = "10:00:E8:52:BF:35"; break;
			case 1031: macAddress = "10:00:E8:52:BC:49"; break;
			case 1033: macAddress = "10:00:E8:52:C7:63"; break;
			case 2386: macAddress = "10:00:E8:AD:79:FC"; break;
			case 2477: macAddress = "10:00:E8:AD:79:BA"; break;
			case 2534: macAddress = "10:00:E8:AD:75:8C"; break;
			case 2539: macAddress = "10:00:E8:AD:75:A0"; break;
			default: throw runtime_error("Internal Error!"
						" No such Epuck known.\n");
		}

		DOUT << "macAddress " << macAddress << endl;
		return str2ba( macAddress );
	}
}

#include <bluetooth/hci.h>	// hci_lib.h, abartig
#include <bluetooth/hci_lib.h>	// hci_get_route
#include <malloc.h>		// free

namespace gui {

bdaddr_t scanForEpuck( const EpuckID robotID )
{
	// bluetooth adapter address, 0 if any
	// specify with devId = hci_devid( "00:02:78:75:16:CD" );
	int devId = hci_get_route( 0 );
	if ( devId < 0 )
		throw runtime_error( "can't get bt adapter id" );
	int so = hci_open_dev( devId );
	if ( so < 0 )
		throw runtime_error( "can't open bt adapter" );
	cout << "scanning bluetooth:\n";
	int length = 4;	// times 1.28 seconds
	inquiry_info *info = 0;
	int max_devices = 15;	// ?
	// lap ??, returned array, flag
	int devicesCount = hci_inquiry( devId, length,
				max_devices, 0, &info, 0 );
	bdaddr_t adr;
	if ( devicesCount < 0 )
		throw runtime_error( "can't query bluetooth" );

	for ( int i = 0; i < devicesCount; i++ )
	{
		char addrString[19];
		char addrFriendlyName[256];
		adr = (info+i)->bdaddr;
		ba2str( &adr, addrString );
		cout << addrString << " ";
		if ( hci_read_remote_name( so, &adr, 256,
				 addrFriendlyName, 0 ) < 0 )
			continue;
		cout << addrFriendlyName << endl;
		if ( strncmp( "e-puck_", addrFriendlyName, 7 ) )
			continue;
		// check for correct robotId
		int id;
		if ( sscanf( addrFriendlyName + 7, "%d", & id ) &&
				id == robotID )
		{
			cout << "found epuck "<< id << endl;
			free( info );
			close( so );
			return adr;
		}
	}
	throw runtime_error( "kein Epuck gefunden" );
}

}
