#ifndef	EPUCK_IF_BLOCK_HPP__
#define	EPUCK_IF_BLOCK_HPP__

#include "EpuckInterface.hpp"
#include "EpuckBtBlock.hpp"
#include "EpuckTypes.hpp"	// IntFeld
#include "EpuckImage.hpp"

#include <string>
using std::string;

namespace gui {
namespace robots {
namespace epuck {

class EpuckBlock: public EpuckInterface
{
	EpuckBtBlock bt;
	int	helptextlength;

	template <char c, int n>
	IntFeld<n> befehl( string d );
	template <char c, int n>
	IntFeld<n> befehl( string d, int w1 );
	template <char c, int n>
	IntFeld<n> befehl( string d, int w1, int w2 );

public:
	EpuckBlock( const EpuckID );
	void reset();

	// camera
	IntFeld<5> cameraMode();
	EpuckImage &cameraShot();

	// drive
	//TODO: change return types to objects
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
