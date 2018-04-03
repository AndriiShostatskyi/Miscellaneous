#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <fcntl.h>
#include <limits.h>
#include <pcap.h>
#include <stdbool.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include <signal.h>
#include <sys/signal.h>
#include <time.h>
#include <netinet/ip_icmp.h>

// Sturcture of the shared mammory for processes
struct shared_region
{
	struct Node *root;
	char buf[100];
	bool run;
};

void start_daemon();

void stop_daemon();

void show_ifaces();

void select_iface();

void show_ip_stat();

struct shared_region *open_mshared();

unsigned int _hash(char *st);

char * _unhash(unsigned intg_ip);

static void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer);

static void foriking(char *devname);
