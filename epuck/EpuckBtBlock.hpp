#ifndef	HINKI_EPUCKBTBLOCK_HPP__
#define	HINKI_EPUCKBTBLOCK_HPP__
#include "EpuckTypes.hpp"
using gui::robots::epuck::EpuckID;

#include "BtConnBlock.hpp"

#include <string>
using std::string;

namespace gui
{

class EpuckBtBlock
{
	BtConnBlock *bt;
	char buffer[10000];	// not sure about the size

	void garbageRead();
public:
	void write( const char *cmd );
	char *read( unsigned int len );
	EpuckBtBlock( const EpuckID id, bool search = 0 );
	~EpuckBtBlock();
	// most commands return a single line answer
	string kommando( const char *cmd, int numAnswerLines = 1 );
};

}

#endif
