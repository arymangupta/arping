#include<stdio.h>
//#include<libnet.h>
#include"libnet.h"
int main(){
	char* ifname;
	char ebuf[100];	
	libnet_init(LIBNET_LINK,(char*)ifname, ebuf);
}
