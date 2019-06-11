#include "stdlib.h"
#include "PcapFileDevice.h"
#include<iostream>
#include<string.h>
#include "Packet.h"

		
struct B{
    int a[2];
    float b;
    int c[2];
};

unsigned char *A;
void printStruct(B& iface)
	{
    std::cout << iface.a[0] << std::endl;
    std::cout << iface.a[1] << std::endl;
    std::cout << iface.b << std::endl;
    std::cout << iface.c[0] << std::endl;
    std::cout << iface.c[1] << std::endl;
	}	

static void onPacket(pcpp::RawPacket* packet)
{
	
	pcpp::Packet parsedPacket(packet);
	unsigned char *temp;

	for (pcpp::Layer* curLayer = parsedPacket.getFirstLayer(); curLayer->getNextLayer()!= NULL; curLayer = curLayer->getNextLayer())
{
	                  
	temp=curLayer->getLayerPayload();
	
}
	A=temp;
   B interface;
   
     std::cout<<&A<<std::endl;
    memcpy(&interface, A, sizeof(interface));
    printStruct(interface);	

	
}



//main
int main(int argc, char* argv[])

{


	pcpp::IFileReaderDevice* rea = pcpp::IFileReaderDevice::getReader("1_packet.pcap");


	if (rea == NULL)
	{
		printf("Cannot determine reader for file type\n");
		exit(1);
	}


	if (!rea->open())
	{
		printf("Cannot open input.pcap for reading\n");
		exit(1);
	}

	pcpp::RawPacket rawPacket;
	if (!rea->getNextPacket(rawPacket))
	{	
		printf("Couldn't read the first packet in the file\n");
		return 1;
	}

	rea->close();
	//pcpp::Packet parsedPacket(&rawPacket);
	onPacket(&rawPacket);



}
