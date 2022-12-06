#ifndef	EPUCK_IF_DUMMY_HPP__
#define	EPUCK_IF_DUMMY_HPP__

#include "EpuckInterface.hpp"
#include "EpuckTypes.hpp"	// IntFeld
#include "EpuckImage.hpp"

#include <string>
using std::string;

namespace gui
{

class EpuckDummy : public EpuckInterface
{
public:
	EpuckDummy();
	void reset();

	// camera
	EpuckImage &cameraShot();
	IntFeld<5> cameraMode();

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

}

#endif
