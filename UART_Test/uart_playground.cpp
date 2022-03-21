
#include "UART.hpp"
#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

#define DEV "/dev/ttyUSB1"
#define BAUDRATE 115200

#define DEBUG(var) do { cout << #var << " = " << var << endl; } while(false)

struct sample_packet
{
	uint8_t  a[6];
} __attribute__((packed));

void print_packet(sample_packet packet)
{
	for (int i = 0; i < 6; i++)
	{
		cout << (int) packet.a[i] << " ";
	}
	cout << endl;
}

UART u
(
	DEV,
	BAUDRATE
);

enum fsm_states {FF1, FF2, FF3, OO4, JUNK};

int main(int argc, char** argv) 
{
	fsm_states fsm = JUNK;
	while(1)
	{
		sample_packet packet;

		uint8_t x = u.read<uint8_t>();
		//DEBUG((int) x);
		// magic number 0xff, 0xff, 0xff, 0x00
		//cout << fsm << endl;
		//DEBUG((int) x);
		if (fsm == FF1)
		{
			if (x == 0xff)
			{
				fsm = FF2;
			}
			else
			{
				fsm = JUNK;
			}
		}
		else if (fsm == FF2)
		{
			if (x == 0xff)
			{
				fsm = FF3;
			}
			else
			{
				fsm = JUNK;
			}
		}
		else if (fsm == FF3)
		{
			if (x == 0xff)
			{
				fsm = FF3;
			}
			else if (x == 0x00)
			{
				fsm = OO4;
			}
			else
			{
				fsm = JUNK;
			}
		}
		else if (fsm == OO4)
		{
			packet.a[0] = x;

			for (int i = 1; i < 6; i++)
			{
				x = u.read<uint8_t>();
				packet.a[i] = x;
			}
			
			print_packet(packet);
			x = u.read<uint8_t>();
			if (x == 0xff)
			{
				fsm = FF1;
			}
			else
			{
				fsm = JUNK;
			}
		}
		else
		{
			if (x == 0xff)
			{
				fsm = FF1;
			}
		}
	}
	

	// sample_packet p = u.read<sample_packet>();

	return 0;
}
