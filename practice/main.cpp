#include "stdlib.h"
#include "PcapLiveDeviceList.h"
#include "PlatformSpecificUtils.h"
#include<iostream>
#include<string.h>
		
struct B{
    int a[2];
    float b;
    int c[2];
};

unsigned char *A;

struct PacketStats{

	void printStruct(B& iface)
	{
    std::cout << iface.a[0] <<std::endl;
    std::cout << iface.a[1] << std::endl;
    std::cout << iface.b << std::endl;
    std::cout << iface.c[0] <<std::endl;
    std::cout << iface.c[1] <<std::endl;
	}	
	
};

PacketStats stats;

static void onPacketArrives(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
	
	PacketStats* stats = (PacketStats*)cookie;

	unsigned char *temp;
	pcpp::Packet parsedPacket(packet);


	for (pcpp::Layer* curLayer = parsedPacket.getFirstLayer(); curLayer->getNextLayer()!= NULL; curLayer = curLayer->getNextLayer())
{
	temp=curLayer->getLayerPayload(); 
}	
	A=temp;
   	B interface;
   
    std::cout<<&A<<std::endl;
    memcpy(&interface, A, sizeof(interface));
    stats->printStruct(interface);	
}




/**
* main method of the application
*/
int main(int argc, char* argv[])

{


	std::string interfaceIPAddr = "192.168.1.4";


	pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr.c_str());

	if (dev == NULL)
	{
		printf("Cannot find interface with IPv4 address of '%s'\n", interfaceIPAddr.c_str());
		exit(1);
	}

	// open the device before start capturing/sending packets
	if (!dev->open())
	{
		printf("Cannot open device\n");
		exit(1);
	}

printf("\nStarting async capture...\n");

// start capture in async mode. Give a callback function to call to whenever a packet is captured and the stats object as the cookie
dev->startCapture(onPacketArrives, &stats);
PCAP_SLEEP(1);

// stop capturing packets
dev->stopCapture();
// print results



}
