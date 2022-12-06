#ifndef	EPUCK_HPP__
#define	EPUCK_HPP__

#include "if_block.hpp"
#include "EpuckTypes.hpp"	// EpuckID

namespace gui {
namespace robots {
namespace epuck {

class Epuck: public EpuckBlock
{
public:
	Epuck( const EpuckID id ) : EpuckBlock( id ) { }
};

}}}

#endif
