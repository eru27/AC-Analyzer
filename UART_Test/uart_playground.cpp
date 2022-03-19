
#include "UART.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

#define DEV "/dev/ttyUSB0"
#define BAUDRATE 115200

#define DEBUG(var) do { cout << #var << " = " << var << endl; } while(false)

struct sample_packet
{
	uint8_t  a[6];
} __attribute__((packed));



UART u
(
	DEV,
	BAUDRATE
);



int main(int argc, char** argv) 
{
	while(1)
	{
		uint8_t x = u.read<uint8_t>();
		DEBUG((int)x);
		// magic number 0xff, 0xff, 0xff, 0x00
	}
	

	// sample_packet p = u.read<sample_packet>();

	return 0;
}
