#include"sniff.h"

int main(int argc, char *argv[])
{
  char buf[10];
	argv++;

  // CLI
  if(!*argv)
  {
    printf("No command entered.\n");
  }
  // Start
	else if(!strcmp(*argv, "start"))
	{
	   start_daemon();
	}
  // Select iface [iface] (select interface for sniffing)
  else if(!strcmp(*argv, "select") && !strcmp(*(argv+1), "iface"))
  {
    select_iface(*(argv+2));
  }
  // Show all devices (ifaces) available for sniffing
  else if(!strcmp(*argv, "show") && !strcmp(*(argv + 1), "ifaces"))
  {
    show_ifaces();
  }
  // Show [ip] count (printf number of packets received from ip address)
  else if(!strcmp(*argv, "show") && !strcmp(*(argv + 2), "count"))
  {
    show_ip_stat(*(argv + 1));
  }
  // Stop (packets are not sniffed)
	else if(!strcmp(*argv, "stop"))
	{
		stop_daemon();
	}
  // Help (show usage information)
  else if(!strcmp(*argv, "--help"))
	{
		FILE* fp = fopen("help.txt", "r");
    char buf[300];
    for(; fgets(buf, 300, fp); printf("%s", buf));
  }
  else
  {
    printf("Wrong command entered.\n");
  }
    return 0;
}
