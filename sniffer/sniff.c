
#include "avltree.h"
#include "sniff.h"

typedef struct shared_region SH;

/* Function that saves the selected device (iface) in a file and deletes the previos one together with its previous statistics
  (could be saved in other files named after the device (iface)), but it's not required) */
void select_iface(char* iface){
	printf("Checking if iface %s exists ...\n" , iface);
	char errbuf[100];

	if (!pcap_open_live(iface , 65536 , 1 , 0 , errbuf))
	{
		fprintf(stderr, "Couldn't find iface %s.\n%s\n" , iface , errbuf);
		exit(EXIT_FAILURE);
	}
	else
	{
		// Clear the previous device (iface) name and save the new one
		FILE *fp = fopen("device.txt", "w");
		if(!fputs(iface, fp))
		{
			printf("Error selecting device (iface) for sniffing.\n");
			exit(EXIT_FAILURE);
		}
		fclose(fp);

		// Clear the previous statistics
		if ((chdir("/")) < 0) exit(EXIT_FAILURE);
		fp = fopen("ips_stat.txt", "w+");
		fclose(fp);

		printf("Iface %s successfully selected for sniffing.\n", iface);
	}
}

// Function prints all the devices (ifaces) that can be selected for sniffing
void show_ifaces(){
	  pcap_if_t *alldevicep , *device;
    char errbuf[100];

    printf("\nFinding available devices ... ");
    if(pcap_findalldevs( &alldevicep , errbuf))
        printf("Error finding devices : %s" , errbuf), exit(EXIT_FAILURE);

    printf("Done\nAvailable Devices are :\n");
    for(device = alldevicep ; device; device = device->next)
        printf("%s - %s\n", device->name , device->description);
}

// Helper function to convert string IP to integer IP
unsigned int _hash(char *st) {
  char *str = strdup(st), *pch = NULL;
  unsigned int intg_ip = 0, cnt = 0, num = 16777216;

  for (pch = strtok (str,"."); pch; pch = strtok (NULL, "."), intg_ip += cnt / 10 * num, num /= 256)
    for(cnt = 0;*pch; cnt += ((unsigned int)*pch++ - 48), cnt *= 10);

  return intg_ip;
}

// Helper function to convert integer IP to string IP
char * _unhash(unsigned intg_ip) {
  char *str = (char*) malloc(sizeof(char) * 32);
  int i = 0;

  i = sprintf(str,"%d",(intg_ip / (256 * 256 * 256)) % 256);
  str[i++] = '.';

  i += sprintf(str + i,"%d",(intg_ip / (256 * 256)) % 256);
  str[i++] = '.';

  i += sprintf(str + i,"%d",(intg_ip / 256) % 256);
  str[i++] = '.';

  i += sprintf(str + i,"%d", intg_ip % 256);
  str[i] = '\n';

  return str;
}

// Helper function to get the shared mammory for processes
SH *mshared()
{
	static SH* ptr = NULL;
	if(!ptr)
	{
		int fd = shm_open("/my_daemon", O_CREAT | O_RDWR, S_IRUSR);

	  if (fd == -1) {
	    printf("Error creating shared memory.\n");
			return NULL;
		}

	  if (ftruncate(fd, sizeof(SH)) == -1) {
	    printf("Error creating shared memory.\n");
			return NULL;
		}

	  ptr = mmap(NULL, sizeof(SH),PROT_EXEC | PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	  if (ptr == MAP_FAILED) {
	    printf("Error creating shared memory.\n");
			return NULL;
		}
  }
	return ptr;
}

// Function that upon the start of the daemon loads statistics from previous processes
static void get_ips_from_file()
{
	SH* ptr = mshared();
	struct Node *temp = NULL;
	FILE *fp = fopen("ips_stat.txt", "r");

	if(fp)
	{
		char str[32];
		while(fgets(str, 32, fp))
		{
			*(strchr(str, '\n')) = 0;
			ptr->root = insert(ptr->root, _hash(str));
			temp = _find(ptr->root, _hash(str));
			fgets(str, 32, fp);
			temp->cnt = atoi(str);
			//printf("%s  %d \n", _unhash(temp->ip), temp->cnt); // Uncommnet to see what is being loaded - for testing purposes only
		}
	}
	else
	{
		printf("Error loading previous statistics upon start.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
}

// Listens to SIGTERM signal, calls the function that saves statistics from AVL tree in a file, and shuts the daemon down
static void handle_term_sig(int signum)
{
	SH* ptr = mshared();
	FILE *fp = fopen("ips_stat.txt", "w+");
	fclose(fp);
	preOrder(ptr->root); // Call the function that saves statistics from AVL tree
	ptr->run = false;
	exit(EXIT_SUCCESS);
}

// Listens to SIGUSR1 to get statisitcs for given IP
static void handle_user_sig(int signum)
{
	if(signum == SIGUSR1)
	{
		SH* ptr = mshared();
		int *p = (int*)ptr->buf;
		struct Node* n = _find(ptr->root, _hash(ptr->buf));
		if(n)
			*p = n->cnt;
		else
			*p = -1;
	}
}

static void process_packet(u_char *args, const struct pcap_pkthdr *header, const u_char *buffer)
{
  //Get the IP Header part of this packet, excluding the ethernet header
  struct iphdr *iph = (struct iphdr*)(buffer + sizeof(struct ethhdr));
	struct sockaddr_in src;
	src.sin_addr.s_addr = iph->saddr;
	char p[32];
	inet_ntop(AF_INET, &src.sin_addr, p, 32);

	static SH* ptr = NULL;
	if(!ptr) ptr = mshared();

	struct Node* temp = _find(ptr->root, _hash(p)); // Search for IP and increament number of incoming packets - runs in O(log N)
	if(!temp) // If not found, the we have a new IP and need to create new node for it
		ptr->root = insert(ptr->root, _hash(p));
	else
	  temp->cnt++; // If found, increament

	// If linked to the terminal and uncommented, the part below is responsible for printing the statisitcs in process; only for testing purposes
	/* temp = _find(ptr->root, _hash(p));
	printf("%s  %d \n", _unhash(temp->ip), temp->cnt); */
}

// Function that's called after start command and forks the daemon for sniffing
static void foriking(char *devname)
{
	/*Open the shared memmory for processes (it's needed, for example, when we search for IP statisitcs in AVL tree,
	while the daemon is running, and send it to the other process) */
	SH* ptr = mshared();
	ptr->run = true, ptr->root = NULL;
	char buf[100];

	pid_t process_id = 0, sid = 0;

	if ((process_id = fork()) < 0) // Checking for fork() failure
		printf("Fork failed!\n"), exit(EXIT_FAILURE);

	if (process_id > 0) // Killing parent proces
		exit(EXIT_SUCCESS);

  umask(0); // Change file mask

  if ((sid = setsid()) < 0) //Create a new signature id for our child
		exit(EXIT_FAILURE);

  if ((chdir("/")) < 0) // Changing directory - if cannot find the directory, exit with failure.
		exit(EXIT_FAILURE);

	FILE *fp = fopen("/run/my_daemon.pid", "w"); // Open PID file and save pid of the current daemon process
	sprintf(buf,"%d", getpid());
  fputs(buf, fp), fclose(fp);

  // Handle catching SIGTERM to the current daemon process to shut down gracefully
  struct sigaction action;
  memset(&action, 0, sizeof(struct sigaction));
  action.sa_handler = handle_term_sig;
  sigaction(SIGTERM, &action, NULL);

  // Handle catching SIGUSR1 to the daemon process to get statisitcs for given IP
	struct sigaction action2;
  memset(&action2, 0, sizeof(struct sigaction));
  action2.sa_handler = handle_user_sig;
  sigaction(SIGUSR1, &action2, NULL);

	printf("\nOpening device %s for sniffing ... " , devname);
	pcap_t *hand = pcap_open_live(devname , 65536 , 1 , 0 , buf); //Open the device (iface) for sniffing
	if (!hand)
		fprintf(stderr, "Couldn't open device %s : %s\n" , devname , buf), exit(EXIT_FAILURE);
	else printf("Done.\n");

  // Load statisitcs from previous processes of the daemon
	get_ips_from_file();

	//Close standard file descriptors
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

	// Finally, put sniffing in a loop
  pcap_loop(hand, -1, process_packet , NULL);
}

// Function that gets statisitcs for show [ip] count command. Works when the daemon is either running or stopped
void show_ip_stat(char * ipd)
{
	SH* ptr = mshared(); // In case the daemon is running and we need to access the buffer for interprocess communication

  // If running, then get statistics from AVL tree and put it in the buffer; will do it in O(log N)
	if(ptr && ptr->run)
  {
		FILE *fp = fopen("/run/my_daemon.pid", "r+");
	  char str[10];
		fgets(str, 10, fp);
		fclose(fp);
		strcpy(ptr->buf, ipd);
		char waiting_change = ptr->buf[0];

		if(!kill((pid_t)atoi(str), SIGUSR1)) // This signal catches a handler in the daemon, which then searches for IP and number of incoming packets in AVL tree
		{
			time_t startTime = time(NULL);
			while(waiting_change == ptr->buf[0]) // Whait until the statistics is found and put in the buffer
			{
				if(time(NULL) - startTime > 30) // If waits too long, then something went wrong.
				printf("Error sending user signal to get statistics for given IP.\n"),
				exit(EXIT_FAILURE);
			}
			int *p = (int*)ptr->buf;
			if(*p != -1)
				printf("Number of packets from %s: %d\n", ipd, *p);
			else printf("Error getting statistics for given IP.\n");
		}
		else // Failed to send singal
		{
			printf("Error sending user signal to get statistics for given IP.\n");
		  exit(EXIT_FAILURE);
		}
	}
	else {
		// If not running, then get statistics from the file that stores it
		if ((chdir("/")) < 0) exit(EXIT_FAILURE);
		FILE* fp = fopen("ips_stat.txt", "r");
		char buf[32];

		while (fgets(buf, 32, fp)) // Go through all IPs in the file and find the rigt one; however, it will be in O(N)
		{
			if(strstr(buf, ipd)) // If found, get the next line - number of packets associated with that IP
			{
				fgets(buf, 32, fp);
				printf("Number of packets from %s: %u\n", ipd, atoi(buf));
				fclose(fp);
				exit (EXIT_SUCCESS);
			}
		}

		printf("Couldn't find statistics for given IP address.\n");
		exit(EXIT_FAILURE);
	}
}

// Function that starts the daemon
void start_daemon()
{
	FILE *fp;
	char buf[32];
  fp = fopen("device.txt", "r"); // Open the file that keeps the name of the device (ficae) to sniff
  if(!fp)
		printf("Error opening the file that stores the name of the device (ifance) to sniff.\n"), exit(EXIT_FAILURE);

	if(!fgets(buf, 32, fp))
		printf("Error reading the name of the device (ifance) to sniff. Possibly, device (iface) for sniffing isn't selected.\n"), exit(EXIT_FAILURE);

	fclose(fp);
	foriking(strtok(buf, "\n")); // Fork sniffing of the device (iface)
}

void stop_daemon()
{
	SH* ptr = mshared();
	if(ptr->run)
	{
		FILE *fp = fopen("/run/my_daemon.pid", "r+");
	  char str[10];
		fgets(str, 10, fp);
		fclose(fp);
		if(!kill( (pid_t)atoi(str), SIGTERM))
			printf("Successfully sent terminating daemon process signal.\n");
	} else printf("Daemon is not running.\n");
}
