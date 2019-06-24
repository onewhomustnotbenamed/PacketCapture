#include "pugixml-master/src/pugixml.hpp"
#include "pugixml-master/src/pugiconfig.hpp"
#include "stdlib.h"
#include "PcapLiveDeviceList.h"
#include "PlatformSpecificUtils.h"
#include <iostream>
#include <iomanip>
#include <cstring>
#include<string>


using std::cout;
using std::endl;
using std::hex;
using std::setfill;
using std::setw;

using u64 = unsigned long long;

using namespace std;

//XML FILE
pugi::xml_document doc;

pugi::xml_parse_result r = doc.load_file("packet.xml");


//USED VARAIABLES
int choice=0;
int s;
float f;
unsigned char *A;



struct PacketStats{

	void printStruct(int choice)
	{
    switch(choice)
    	{
    		case 0:
       			memcpy(&s,A,sizeof(s));
    			std::cout<<s<<std::endl;
    			A=A+4;
    			break;
    			
    		case 1:
    			memcpy(&f,A,sizeof(f));
    			std::cout<<f<<std::endl;
    			A=A+4;
    			break;
    			
    	}
	}	
	
};

PacketStats stats;


//FUNCTION CALLED UPON  CAPTURE
static bool onPacketArrivesBlockingMode(pcpp::RawPacket* packet, pcpp::PcapLiveDevice* dev, void* cookie)
{
	
	PacketStats* stats = (PacketStats*)cookie;

	unsigned char *temp;
	pcpp::Packet parsedPacket(packet);


	for (pcpp::Layer* curLayer = parsedPacket.getFirstLayer(); curLayer->getNextLayer()!= NULL; curLayer = curLayer->getNextLayer())
	{
		temp=curLayer->getLayerPayload(); 
	}	
	
	A=temp;
   
   	//memcpy(&interface, A, sizeof(interface));
   	 for (pugi::xml_node n = doc.child("packet").child("value"); n; n=n.next_sibling("value"))
    {	 
    	std::string s=n.attribute("type").value();
        if(s=="int")       
    	choice=0;
        
    	if(s=="float")
    	choice=1;
    
    	stats->printStruct(choice);
       
    }

    	
  
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
    return false;
   
      
}




//MAIN
int main(int argc, char* argv[])

{	


	std::string interfaceIPAddr = "192.168.1.7";

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

printf("\nStarting capture...\n");


dev->startCaptureBlockingMode(onPacketArrivesBlockingMode, &stats,1);




}
