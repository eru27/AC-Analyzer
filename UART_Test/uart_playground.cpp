
#include "UART.hpp"
#include "hdf5_write.cpp"
//#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>
using namespace std;

#define DEV "/dev/ttyUSB2"
#define BAUDRATE 115200

#define DEBUG(var) do { cout << #var << " = " << var << endl; } while(false)

struct sample_packet
{
	uint32_t magic;
  	uint16_t  val_array[6];
} __attribute__((packed));

UART u
(
	DEV,
	BAUDRATE
);

enum fsm_states {FF1, FF2, FF3, OO4, JUNK};

void find_magic_word()
{
	fsm_states fsm = JUNK;
	uint8_t x;

	while(fsm != OO4)
	{
		x = u.read<uint8_t>();

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

	for (int i = 0; i < 6; i++)
	{
		u.read<uint16_t>();
	}
}

int main(int argc, char** argv) 
{
	sample_packet packet;
	uint16_t x;
	while(1)
	{
		packet = u.read<sample_packet>();

		if (packet.magic != 0x00ffffff) //little endian
		{
			// magic number 0xff, 0xff, 0xff, 0x00
			find_magic_word();
			cout << "ERROR\n";
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				cout << (int) packet.val_array[i] << " ";
			}
		}

		cout << endl;	
	}

	return 0;
}
