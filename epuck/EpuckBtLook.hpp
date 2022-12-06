#include "EpuckTypes.hpp"		// EpuckID
using gui::robots::epuck::EpuckID;

#include <bluetooth/bluetooth.h>	// bdaddr_t

namespace gui {

// fest verdrahtete MAC-Adresse
bdaddr_t lookupEpuck( const EpuckID id );

// der Epuck wird anhand seiner Nummer gesucht, und dann wird seine
// MAC-Adresse gelesen.
bdaddr_t scanForEpuck( const EpuckID id );

}
