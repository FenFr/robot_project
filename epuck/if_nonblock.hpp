#ifndef	EPUCK_IF_NONBLOCK_HPP__
#define	EPUCK_IF_NONBLOCK_HPP__

#include "EpuckInterface.hpp"
#include "EpuckBt.hpp"
#include "EpuckTypes.hpp"	// IntFeld
#include "EpuckImage.hpp"

#include <string>
using std::string;

namespace gui {
namespace robots {
namespace epuck {

class EpuckNonBlock : public EpuckInterface
{
	EpuckBt bt;

	template <int n>
	IntFeld<n> befehlAufrufen ( string befehl );
	template <char c, int n>
	IntFeld<n> befehl( string description );
	template <char c, int n>
	IntFeld<n> befehl( string description, int w1 );
	template <char c, int n>
	IntFeld<n> befehl( string description, int w1, int w2 );

public:
	EpuckNonBlock( const EpuckID );
	void reset();

	// camera
	IntFeld<5> cameraMode();
	EpuckImage &cameraShot();

	// drive
	void setMotorSpeed( int left, int right );
	IntFeld<2> getMotorSpeed();
	void setMotorPositionCounter( int left, int right );
	IntFeld<2> getMotorPositionCounter();
	void stopRobot();

	// leds
	void setBodyLED( LEDState state );
	void setFrontLED( LEDState state );
	void setLED( int number, LEDState state );

	// info
	int getSelectorPosition();
	string getHelpText();
	string getVersion();

	// sound
	void playSound( int sampleNumber );
	IntFeld<3> getMicrophones();

	// sensors
	void calibrateProximitySensors();
	IntFeld<8> getProximitySensors();
	IntFeld<8> getLightSensors();
	IntFeld<3> getAccelerometer();
};

}}}

#endif
