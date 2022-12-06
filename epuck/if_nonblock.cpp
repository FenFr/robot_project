#include "if_nonblock.hpp"
#include "EpuckBt.hpp"		// For bluetooth communication
#include "EpuckTypes.hpp"	// IntFeld

//TODO: sinnvolle eigene ausnahmen definieren
#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;

#include <unistd.h>		// sleep
#include "debug-out.hpp"	// DOUT
#include "kommando.hpp"		// baueKommando

namespace gui {
namespace robots {
namespace epuck {

EpuckNonBlock::EpuckNonBlock( const EpuckID id )
: bt( id )
{ DOUT << "EpuckNonBlock object created\n"; }

template <char c, int n>
IntFeld<n> EpuckNonBlock::befehl( string d )
{
	string k = baueKommando( c );
	DOUT << d << ' ' << k;
	string s = bt.kommando( k.c_str() );
	DOUT << s;
	try { return parseIntFeldN<n>( s, c ); }
	catch ( const runtime_error &e )
	{
		cout << d << " failed\n";
		throw e;
	}
}

template <char c, int n>
IntFeld<n> EpuckNonBlock::befehl( string d, int w1 )
{
	string k = baueKommando( c, w1 );
	DOUT << d << ' ' << k;
	string s = bt.kommando( k.c_str() );
	DOUT << s;
	try { return parseIntFeldN<n>( s, c ); }
	catch ( const runtime_error &e )
	{
		cout << d << " failed\n";
		throw e;
	}
}

template <char c, int n>
IntFeld<n> EpuckNonBlock::befehl( string d, int w1, int w2 )
{
	string k = baueKommando( c, w1, w2 );
	DOUT << d << ' ' << k;
	string s = bt.kommando( k.c_str() );
	DOUT << s;
	try { return parseIntFeldN<n>( s, c ); }
	catch ( const runtime_error &e )
	{
		cout << d << " failed\n";
		throw e;
	}
}

void EpuckNonBlock::reset() { befehl<'r',0>( "reset Epuck" ); }

IntFeld<3> EpuckNonBlock::getAccelerometer()
{ return befehl<'a',3>( "read acceleration" ); }

void EpuckNonBlock::setBodyLED( LEDState state )
{ befehl<'b',0>( "set body LED", state ); }

// TODO: das muss immer 3 sein! testen!
int EpuckNonBlock::getSelectorPosition()
{ return befehl<'c',1>( "read selector" ).data[0]; }

void EpuckNonBlock::setMotorSpeed(int left, int right)
{ befehl<'d',0>( "set motor speed", left, right ); }

IntFeld<2> EpuckNonBlock::getMotorSpeed()
{ return befehl<'e',2>( "read motor speed" ); }

void EpuckNonBlock::setFrontLED( LEDState state )
{ befehl<'f',0>( "set front LED", state ); }

string EpuckNonBlock::getHelpText()
{
	char c = 'h';
	string k = baueKommando( c );
	return bt.kommando( k.c_str() );
}

IntFeld<5> EpuckNonBlock::cameraMode()
{ return befehl<'i',5>( "get camera mode" ); }

EpuckImage &EpuckNonBlock::cameraShot()
{
	char c = 'i';
	string k = baueBinaerKommando( c );
	string s = bt.kommando( k.c_str(), 20 );
	return *(new EpuckImage( s ));
}

void EpuckNonBlock::calibrateProximitySensors()
{
	char c = 'k';
	string k = baueKommando( c );
	string s = bt.kommando( k.c_str() );
	string v = "k, Starting calibration -"
		" Remove any object in sensors range\r\n";
	DOUT << __func__ << ' ' << s;
	if ( s != v )
		throw runtime_error("Triggering calibration failed");
	// für 6 sekunden jede sekunde pollen
	int i = 6;
	for ( s = ""; i > 0 && s != "k, Calibration finished\r\n"; i--, sleep( 1 ) )
		try { s += bt.kommando( "", 1 ); } catch ( ... ) { };
	if( i == 0 )
		throw runtime_error( "calibration timed out" );
}

void EpuckNonBlock::setLED(int number, LEDState state)
{
	if ( number < 0 || number > 7 )
		throw runtime_error( "no such LED" );
	befehl<'l',0>( "set LED", number, state );
}

IntFeld<8> EpuckNonBlock::getProximitySensors()
{ return befehl<'n',8>( "read proximity values" ); }

IntFeld<8> EpuckNonBlock::getLightSensors()
{ return befehl<'o',8>( "read light sensors" ); }

void EpuckNonBlock::setMotorPositionCounter(int left, int right)
{ befehl<'p',0>( "set motor position counter", left, right ); }

IntFeld<2> EpuckNonBlock::getMotorPositionCounter()
{ return befehl<'q',2>( "read motor position" ); }

void EpuckNonBlock::stopRobot()
{ befehl<'s',0>( "stop robot" ); }

void EpuckNonBlock::playSound( int sampleNo )
{ befehl<'t',0>( "play sound", sampleNo ); }

IntFeld<3> EpuckNonBlock::getMicrophones()
{ return befehl<'u',3>( "get microphone values" ); }

string EpuckNonBlock::getVersion()
{
	char c = 'v';
	string k = baueKommando( c );
	string s = bt.kommando( k.c_str() );
	string v( 1, c );	// Länge 1, mit c gefüllt
	v += ",Version 1.2.2 August 2008 GCtronic\r\nHW version: ";
	if ( s.substr( 0, v.size() ) != v )
		throw runtime_error("Reading version failed");
	return s.substr( 2 );
}

}}}
