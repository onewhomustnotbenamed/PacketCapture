#include "stdlib.h"
#include "PcapLiveDeviceList.h"
#include "PlatformSpecificUtils.h"
#include <iostream>
#include <iomanip>
#include <cstring>

using std::cout;
using std::endl;
using std::hex;
using std::setfill;
using std::setw;

using u64 = unsigned long long;


		
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
    std::cout<<std::endl;
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
   	memcpy(&interface, A, sizeof(interface));
    stats->printStruct(interface);	

    /*
   	cout<<"The data is:";
   	//HEX
   	cout << hex << setfill('0');  
    auto *ptr = reinterpret_cast<unsigned char *>(temp);
    for (int i = 0; i < sizeof(parsedPacket); i++, ptr++) {
        if (i % sizeof(u64) == 0) {
            cout << endl;
        }
        cout << setw(2) << static_cast<unsigned>(*ptr) << " ";
    }

    */
    cout<<endl<<"-------------------------------------------------------"<<endl;
   
      
}




//MAIN
int main(int argc, char* argv[])

{


	std::string interfaceIPAddr = "192.168.1.4";


	pcpp::PcapLiveDevice* dev = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDeviceByIp(interfaceIPAddr.c_str());

	if (dev == NULL)
	{
		printf("Cannot find interface with IPv4 address of '%s'\n", interfaceIPAddr.c_str());
		exit(1);
	}

	
	if (!dev->open())
	{
		printf("Cannot open device\n");
		exit(1);
	}

printf("\nStarting async capture...\n");


dev->startCapture(onPacketArrives, &stats);
PCAP_SLEEP(30);


dev->stopCapture();




}

