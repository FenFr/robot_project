//TODO: sinnvolle eigene ausnahmen definieren
#include <stdexcept>
using std::runtime_error;

namespace gui {
namespace robots {
namespace epuck {

string baueBinaerKommando( char c );
string baueKommando( char c );
string baueKommando( char c, int w1 );
string baueKommando( char c, int w1, int w2 );

}}}
