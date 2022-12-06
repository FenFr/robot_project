#include "if_block.hpp"
#include "BtSocketBlock.hpp"
#include "EpuckTypes.hpp"	// IntFeld

#include <stdexcept>
using std::runtime_error;

#include <iostream>
using std::cout;

#include "debug-out.hpp"	// DOUT
#include "kommando.hpp"		// baueKommando

namespace gui {
namespace robots {
namespace epuck {

EpuckBlock::EpuckBlock( const EpuckID id )
: bt( id )
{
	// TODO: extract from firmware source code
	helptextlength = 24;
	if ( id == 2539 ) helptextlength = 26;
}

template <char c, int n>
IntFeld<n> EpuckBlock::befehl( string d )
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
IntFeld<n> EpuckBlock::befehl( string d, int w1 )
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
IntFeld<n> EpuckBlock::befehl( string d, int w1, int w2 )
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

void EpuckBlock::reset() { befehl<'r',0>( "reset Epuck" ); }

IntFeld<3> EpuckBlock::getAccelerometer()
{ return befehl<'a',3>( "read acceleration" ); }

void EpuckBlock::setBodyLED(LEDState state)
{ befehl<'b',0>( "set body LED", state ); }

int EpuckBlock::getSelectorPosition()
{ return befehl<'c',1>( "read selector" ).data[0]; }

void EpuckBlock::setMotorSpeed(int left, int right)
{ befehl<'d',0>( "set motor speed", left, right ); }

IntFeld<2> EpuckBlock::getMotorSpeed()
{ return befehl<'e',2>( "get motor speed" ); }

void EpuckBlock::setFrontLED(LEDState state)
{ befehl<'f',0>( "set front LED", state ); }

string EpuckBlock::getHelpText()
{
	char c = 'h';
	string k = baueKommando( c );
	return bt.kommando( k.c_str(), helptextlength );
}

IntFeld<5> EpuckBlock::cameraMode()
{ return befehl<'i',5>( "get camera mode" ); }

EpuckImage &EpuckBlock::cameraShot()
{
	char c = 'i';
	string k = baueBinaerKommando( c );
	bt.write( k.c_str() );

	// das format bekomme ich mit cameraMode() raus.
	// standard: 3 byte header followed by raw 40x40 rgb565 image
	string s = bt.read( 3 + 40*40*2 );
	return *(new EpuckImage( s ));
}

void EpuckBlock::calibrateProximitySensors()
{
	char c = 'k';
	string k = baueKommando( c );
	string s = bt.kommando( k.c_str(), 2 );
	string v = "k, Starting calibration -"
		" Remove any object in sensors range\r\n"
		"k, Calibration finished\r\n";
	if ( s != v )
		throw runtime_error("Triggering calibration failed");
}

void EpuckBlock::setLED(int number, LEDState state)
{
	if ( number < 0 || number > 7 )
		throw runtime_error( "no such LED" );
	befehl<'l',0>( "set LED", number, state );
}

IntFeld<8> EpuckBlock::getProximitySensors()
{ return befehl<'n',8>( "read proximity values" ); }

IntFeld<8> EpuckBlock::getLightSensors()
{ return befehl<'o',8>( "read light sensors" ); }

void EpuckBlock::setMotorPositionCounter(int left, int right)
{ befehl<'p',0>( "set motor position counter", left, right ); }

IntFeld<2> EpuckBlock::getMotorPositionCounter()
{ return befehl<'q',2>( "read motor position" ); }

void EpuckBlock::stopRobot() { befehl<'s',0>( "stop robot" ); }

void EpuckBlock::playSound( int sampleNo )
{ befehl<'t',0>( "play sound", sampleNo ); }

IntFeld<3> EpuckBlock::getMicrophones()
{ return befehl<'u',3>( "get microphone values" ); }

// TODO: return hwversion in int
string EpuckBlock::getVersion()
{
	char c = 'v';
	string k = baueKommando( c );
	string s = bt.kommando( k.c_str(), 2 );
	string v( 1, c );
	v += ",Version 1.2.2 August 2008 GCtronic\r\nHW version: ";
	if ( s.substr( 0, v.size() ) != v )
		throw runtime_error("Reading version failed");
	return s.substr( 2 );
}

}}}
