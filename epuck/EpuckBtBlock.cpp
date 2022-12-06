#include "EpuckBtBlock.hpp"
#include "EpuckBtLook.hpp"	// lookupEpuck
#include "BtConnBlock.hpp"

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;
using std::endl;

#include <cstring>	// strlen

namespace { int debuglevel = 0; }

#define DOUT( comparelevel ) if ( debuglevel >= comparelevel ) cout << __FILE__ << ": "

namespace gui
{
	void EpuckBtBlock::write( const char *cmd )
	{
		unsigned int len = strlen( cmd );
		if ( *cmd < 0 )	// assumes that char is signed
			len++;	// binary mode must send the trailing '\0'
		if ( bt->write( cmd, len ) < len )
			throw runtime_error("failed to send command to epuck");
		DOUT( 1 ) << "wrote " << cmd;
	}

	char *EpuckBtBlock::read( unsigned int len )
	{
		for ( unsigned int l = 0; l < len; )
		{
 			int tmp = bt->read( buffer+l, sizeof(buffer)-l );
			if ( tmp < 1 )
				throw runtime_error( "Bluetooth "
					"receiving failed" );
			l += tmp;
		}
		return buffer;
	}

	string EpuckBtBlock::kommando( const char *cmd, int numAnswerLines )
	{
		write( cmd );
		DOUT( 1 ) << "trying " << cmd << endl;
		const int maxLen = 10000;
		char *b = new char[maxLen+1];
		string antwort;
		int	offs = 0;
		for( int i = 0; i < numAnswerLines; i++ )
		{
			int tmp = bt->readline(&b[offs], maxLen-offs);
			if( tmp == 0 )
				throw runtime_error("Bluetooth receiving failed");
			offs += tmp;
			DOUT( 1 ) << "read line\n";
		}
		b[offs] = '\0';
		antwort = b;
		return antwort;
	}

	void EpuckBtBlock::garbageRead()
	{
		/* Initially, the robot answers with "z,Command not found\n"
		 * and even with cryptic rubbish, so lets skip these lines
		 * directly at startup. The actual command to sent for that
		 * purpose is opaque. */
		DOUT( 1 ) << "garbage read\n";
		for ( int i = 0; i < 3; i ++ )
		{
			string s = kommando("A\n" );
			DOUT( 1 ) << s;
		}
	}

	EpuckBtBlock::EpuckBtBlock( const EpuckID id, bool search )
	{
		if ( search == true )
			bt = new BtConnBlock( scanForEpuck( id ) );
		else
			bt = new BtConnBlock( lookupEpuck( id ) );
		DOUT( 1 ) << "Epuck Bluetooth connection established\n";
		garbageRead();
	}

	EpuckBtBlock::~EpuckBtBlock()
	{
		delete bt;
		DOUT( 1 ) << "Epuck Bluetooth connection closed\n";
	}
}
