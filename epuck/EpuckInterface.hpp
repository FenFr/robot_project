#ifndef	EPUCKINTERFACE_HPP__
#define	EPUCKINTERFACE_HPP__

#include <string>
using std::string;

#include "EpuckTypes.hpp"

namespace gui {

class EpuckImage;	// reference used in EpuckInterface

using gui::robots::epuck::IntFeld;
using gui::robots::epuck::led::LEDState;

class EpuckInterface
{
public:
	virtual ~EpuckInterface() { }
	virtual void reset() = 0;

	// camera
	virtual IntFeld<5> cameraMode() = 0;	// default answer: i,1,40,40,8,3200
	virtual EpuckImage &cameraShot() = 0;

	// drive
	virtual void setMotorSpeed( int left, int right ) = 0;
	virtual IntFeld<2> getMotorSpeed() = 0;
	virtual void setMotorPositionCounter( int left, int right ) = 0;
	virtual IntFeld<2> getMotorPositionCounter() = 0;
	virtual void stopRobot() = 0;

	// leds
	virtual void setBodyLED( LEDState state ) = 0;
	virtual void setFrontLED( LEDState state ) = 0;
	virtual void setLED( int number, LEDState state ) = 0;

	// misc.
	virtual int getSelectorPosition() = 0;
	virtual string getHelpText() = 0;
	virtual string getVersion() = 0;

	// Sound
	virtual void playSound( int sampleNumber ) = 0;
	virtual IntFeld<3> getMicrophones() = 0;

	// Sensors
	virtual void calibrateProximitySensors() = 0;
	virtual IntFeld<8> getProximitySensors() = 0;
	virtual IntFeld<8> getLightSensors() = 0;
	virtual IntFeld<3> getAccelerometer() = 0;
};

}

#endif
