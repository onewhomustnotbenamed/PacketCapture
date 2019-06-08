#include<iostream>
#include<cstring>

using namespace std;

struct B{
    int a[2];
    float b;
    int c[2];
};

void printStruct(B& iface)
{
    cout << iface.a[0] << endl;
    cout << iface.a[1] << endl;
    cout << iface.b << endl;
    cout << iface.c[0] << endl;
    cout << iface.c[1] << endl;
}



int main(){
    B interface;
    unsigned char byte[20];
    for(int i=0;i<20;i++)
        byte[i]=0x01;
    memcpy(&interface, byte, sizeof(interface));
    printStruct(interface);
}
