#include "EpuckDummy.hpp"
#include "EpuckImage.hpp"

#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

namespace gui
{
	EpuckDummy::EpuckDummy()
	{ cout << "simulating epuck" << endl; }

	void EpuckDummy::reset()
	{ cout << "Epuck reset\n"; }
	void EpuckDummy::setBodyLED(LEDState state)
	{ cout << "BodyLED " << state << endl; }
	void EpuckDummy::setFrontLED(LEDState state)
	{ cout << "FrontLED " << state << endl; }
	void EpuckDummy::setLED(int number, LEDState state)
	{ cout << "LED " << number << ": " << state; }

	void EpuckDummy::setMotorSpeed(int left, int right)
	{ cout << "Motor l " << left << ", r " << right << endl; }
	IntFeld<2> EpuckDummy::getMotorSpeed()
	{ cout << "kein Motor da\n"; return IntFeld<2>(); }
	void EpuckDummy::setMotorPositionCounter(int left, int right)
	{
		cout << "Motorposition l " << left << ", r " << right;
		cout << endl;
	}
	IntFeld<2> EpuckDummy::getMotorPositionCounter()
	{ cout << "kein Motor da\n"; return IntFeld<2>(); }
	void EpuckDummy::stopRobot()
	{ cout << "steht\n"; }

	void EpuckDummy::calibrateProximitySensors()
	{ cout << "Proximity Sensors calibrated\n"; }
	IntFeld<8> EpuckDummy::getProximitySensors()
	{ return IntFeld<8>(); }
	IntFeld<8> EpuckDummy::getLightSensors()
	{ return IntFeld<8>(); }
	IntFeld<3> EpuckDummy::getAccelerometer()
	{ return IntFeld<3>(); }
	
	EpuckImage &EpuckDummy::cameraShot()
	{
		cout << "Bild\n";
		return *(new EpuckImage());
	}
	IntFeld<5> EpuckDummy::cameraMode()
	{ return IntFeld<5>(); }
	void EpuckDummy::playSound(int sampleNo)
	{ cout << "Lärm Nummer " << sampleNo << endl; }
	IntFeld<3> EpuckDummy::getMicrophones()
	{ return IntFeld<3>(); }

	int EpuckDummy::getSelectorPosition()
	{ return 0; }

	string EpuckDummy::getHelpText()
	{ return "Hilfe !!!\n"; }
	string EpuckDummy::getVersion()
	{ return "version 0\n"; }
}
