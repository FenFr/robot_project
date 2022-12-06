#ifndef	HINKI_EPUCKBT_HPP__
#define	HINKI_EPUCKBT_HPP__

#include "EpuckTypes.hpp"
using gui::robots::epuck::EpuckID;

#include "BtConn.hpp"

#include <string>
using std::string;

#include <bluetooth/bluetooth.h>	// bdaddr_t

namespace gui
{

class EpuckBt
{
	BtConn	*bt;

	void write( const char *cmd );
	int read( char *s, int len );
	int readPossible( int seconds );
	int nextReadPossible();
	void garbageRead();
public:
	EpuckBt( const EpuckID id, bool search = 0 );
	~EpuckBt();
	string kommando( const char *befehl, int sec = 4 );
};

}

#endif
