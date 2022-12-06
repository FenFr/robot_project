#include "EpuckBt.hpp"
#include "BtConn.hpp"		// For bluetooth communication
#include "EpuckBtLook.hpp"	// lookupEpuck

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>	// strlen

#include <string>
using std::string;

namespace { int debuglevel = 0; }

#define DOUT( comparelevel ) if ( debuglevel >= comparelevel ) cout << __FILE__ << ": "

namespace gui
{
	void EpuckBt::write( const char *cmd )
	{
		unsigned int len = strlen( cmd );
		if ( *cmd < 0 )	// assumes that char is signed
			len++;	// binary mode must send the trailing '\0'
		if ( bt->write( cmd, len ) < len )
			throw runtime_error("failed to send command to epuck");
		DOUT( 1 ) << "wrote " << cmd;
	}

// TODO: use std::string
	int EpuckBt::read( char *s, int len )
	{ return bt->read( s, len ); }

	int EpuckBt::nextReadPossible()
	{ return bt->nextReadPossible(); }

	int EpuckBt::readPossible( int sec )
	{
		DOUT( 1 ) << "read possible? ";
		int r = bt->readPossible( sec );
		if ( r < 0 ) throw runtime_error( "select failed" );
		if ( r == 0 )
			throw runtime_error( "select timed out" );
		return r;
	}

	string EpuckBt::kommando( const char *cmd, int sec )
	{
		write( cmd );
		DOUT( 1 ) << "trying " << cmd << endl;
		const int maxLen = 10000;
		char *b = new char[maxLen+1];
		string antwort;
		int	offs = 0;
		if( readPossible( sec ) )
		{
			int r;
			do
			{
				// TODO: read into string
				r = read( b+offs, maxLen - offs );
				DOUT( 3 ) << r;
				for ( int j = offs; j < offs+r; j++ )
					antwort += b[j];
			}
			while( r && (offs+=r) < maxLen && nextReadPossible() );
		}
		DOUT( 2 ) << offs << " zeichen:\n" << antwort;
		delete[] b;
		return antwort;
	}

	void EpuckBt::garbageRead()
	{
		/* Initially (when?), the robot answers with
		 * "z,Command not found\n" and even with cryptic
		 * rubbish (never seen), so lets skip these lines
		 * directly at startup (reset?). The actual command
		 * to sent for that doesn't matter. */
		DOUT( 1 ) << "garbage read\n";
		string s = kommando( "A\n", 1 );
		DOUT( 1 ) << s;
	}

	EpuckBt::EpuckBt( const EpuckID id, bool search )
	{
		if ( search == true )
			bt = new BtConn( scanForEpuck( id ) );
		else
			bt = new BtConn( lookupEpuck( id ) );
		DOUT( 1 ) << "Epuck Bluetooth connection established\n";
		garbageRead();
	}

	EpuckBt::~EpuckBt()
	{
		delete bt;
		DOUT( 1 ) << "Epuck Bluetooth connection closed\n";
	}
}
