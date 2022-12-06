#ifndef	EPUCKIMAGE_HPP__
#define	EPUCKIMAGE_HPP__
#include <iostream>	// cout
#include <iomanip>	// setw
#include <stdint.h>	// uint8_t

#include <string>
using std::string;

#include <stdexcept>
using std::runtime_error;

namespace gui
{
	class Pixel
	{
		uint8_t	red, green, blue;
	public:
		Pixel() { }
		Pixel( const uint8_t &r, const uint8_t &g, const uint8_t &b )
			: red(r), green(g), blue(b) { }
		Pixel( uint8_t high, uint8_t low )	// decode from rgb565
		{
			red = high & 0xF8;
			green = ((high & 0x7)<<5)|((low & 0xE0)>>3);
			blue = (low & 0x1F)<<3;
		}
		uint8_t	r() const { return red; }
		uint8_t	g() const { return green; }
		uint8_t	b() const { return blue; }
	};

	class PixelImage	// for future use
	{
		static const unsigned int	height = 40;
		static const unsigned int	width = 40;
		static const unsigned int	num_pixels = height * width;
		Pixel	p[height][width];
	public:
		PixelImage( char *buffer )
		{
			if( !buffer ) return;

			for( unsigned int y = 0; y < height; y++ )
				for( unsigned int x = 0; x < width; x++ )
				{
					unsigned int	i = (width*y+x)*2;
					p[y][x] = Pixel(buffer[i],buffer[i+1]);
				}
		}
	};

	class Position2D	//TODO
	{
		unsigned int	x, y;
	};

	class EpuckImage
	{
		// Image is 40x40 raw rgb int-values, each ranging from 0 to 255
		static const unsigned int	height = 40;
		static const unsigned int	width = 40;
		static const unsigned int	i_red = 0;
		static const unsigned int 	i_green = 1;
		static const unsigned int	i_blue = 2;
		int 				rgb[4800];	// perhaps char?
	public:
		EpuckImage() { }
		EpuckImage( string &s )
		{
	                // This checks for a color image, this is the default
	                // Sanity check:
			// Format must be Mode = 1, Width = 40, Height = 40
			if ( s.compare(0, 3, "\1\50\50", 3) )
        	                throw runtime_error("Weird epuck camera "
	                                        "settings. Reset epuck!\n");
			const char *buffer = s.c_str() + 3;
			for( int i=0; i < 3200; i+=2 )
			{
				setRGB( (i/2)%40,
					(i/2)/40,
					Pixel(buffer[i], buffer[i+1]) );
			}
		}

		// RGB could be a distinct class, xy also
		void setRGB(int x, int y, int r, int g, int b)
		{
			const int	i = (y*40+x)*3;
			rgb[i+i_red] = r;
			rgb[i+i_green] = g;
			rgb[i+i_blue] =b;
		}
		void setRGB( int x, int y, Pixel p )
		{
			const int	i = (y*40+x)*3;
			rgb[i+i_red] = p.r();
			rgb[i+i_green] = p.g();
			rgb[i+i_blue] = p.b();
		}
		void getRGB(int x, int y, int& r, int& g, int& b) const
		{
			const int	i = (y*40+x)*3;
			r = rgb[i+i_red];
			g = rgb[i+i_green];
			b = rgb[i+i_blue];
		}
		void hexdump() const
		{
			using std::cout;
			using std::hex;
			using std::dec;
			using std::endl;
			using std::setw;

			cout << hex << setw(2);
			for( unsigned int y=0; y<height; y++ )
			{
				for( unsigned int x=0; x<width; x++ )
				{
					int r,g,b;
					getRGB(x,y,r,g,b);
					cout << r << ',' << g << ',' << b;
					cout << " ";
				}
				cout << endl;
			}
			cout << dec;
		}
	};
}

#endif

