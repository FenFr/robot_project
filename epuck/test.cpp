#include <iostream>
using std::cout;
using std::endl;

int usage( char *progname )
{
	cout << progname << " <robot number>\n\n";
	cout << "The robot's number can be found on the package.\n";
	cout << "Use 0 for a dummy interface.\n\n";
	return 1;
}

//TODO: combine into one hpp
#include "EpuckInterface.hpp"
using gui::EpuckInterface;

#include "EpuckImage.hpp"
#include "EpuckTypes.hpp"
namespace epuck = gui::robots::epuck;

int epucktest( EpuckInterface *e )
{
	namespace led = epuck::led;
	using led::Toggle;
	using led::Off;
	using epuck::IntFeld;

	cout << e->getVersion();

	e->setBodyLED(Toggle);

	cout << "Selector position is " << e->getSelectorPosition() << endl;

	e->setMotorSpeed(100,-100);
	IntFeld<2> speed = e->getMotorSpeed();
	speed.print( "Speed: " );

	IntFeld<3> accel = e->getAccelerometer();
	accel.print( "Accel: " );

	e->setFrontLED(Toggle);

	cout << "Calibrating proximity sensors...";
	cout.flush();
	e->calibrateProximitySensors();

	for (int i = 0; i < 8; i++)
		e->setLED(i, Toggle);
	cout << endl;

	IntFeld<8> prox = e->getProximitySensors();
	prox.print( "Proximity sensor: " );

	IntFeld<8> light = e->getLightSensors();
	light.print( "Light sensor: " );

	e->setMotorPositionCounter(1000,100);
	IntFeld<2> pos = e->getMotorPositionCounter();
	pos.print( "Motor position: " );

	e->stopRobot();

	e->cameraMode().print();
	cout << "Requesting camera image...";
	gui::EpuckImage image = e->cameraShot();
	cout << "done." << endl;
	image.hexdump();

	e->playSound(3);
	IntFeld<3> micro = e->getMicrophones();
	micro.print( "Microphone levels: " );
	e->playSound(0);

	cout << e->getHelpText();

	e->setFrontLED(Off);
	e->setBodyLED(Off);

	return 0;
}

//TODO: make c++
#include <cstdlib>		// atoi
#include <cstring>		// strcmp

// epuck interface implementations
#include "epuck.hpp"		// real epuck, blocking io, the default
using epuck::Epuck;
#include "if_nonblock.hpp"	// real epuck, nonblocking io
using epuck::EpuckNonBlock;
#include "EpuckDummy.hpp"	// for dummy epuck simulation
using gui::EpuckDummy;

int main( int argc, char **argv )
{
	using epuck::EpuckID;	// EpuckTypes.hpp

	// first argument is the epuck id to use
	if ( argc < 2 || argc > 3 ) return usage( argv[0] );

	// optional second argument selects non-blocking io
	bool nonblock = false;
	if ( argc > 2 )
		if( string( argv[2] ) == string( "nonblock" ) )
			nonblock = true;

	EpuckID id = atoi( argv[1] );
	EpuckInterface *epuck;
	if ( id )
		if ( nonblock )
			epuck = new EpuckNonBlock( id );
		else
			epuck = new Epuck( id );
	else
		epuck = new EpuckDummy;
	try
	{ epucktest( epuck ); }
	catch( std::runtime_error e )
	{
		delete epuck;
		throw e;
	}
	delete epuck;

	return 0;
}
