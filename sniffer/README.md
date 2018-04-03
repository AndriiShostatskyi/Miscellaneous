# About:
This is a daemon that sniffs packets from particular interface. It saves ip addresses of incoming packets and number of packets from each ip.

# Task:
Create a service that collects statistic about network traffic.

# Requirements:
1. A daemon should be implemented that sniffs packets from particular interface. It saves ip addresses of incoming packets and number of packets from each ip.
2. Time complexity for ip search should be log(N).
3. Statistic should be persistent through reboots.
4. Command line interface (cli) should be implemented - another process that interacts with the daemon.
5. The cli should support command:

    a. <b>start</b> (packets are being sniffed from now on)

    b. <b>stop</b> (packets are not sniffed)

    c. <b>show [ip] count </b>(printf number of packets received from ip address)

    d. <b>select iface [iface] </b>(select interface for sniffing)

    e.  <b>--help </b>(show usage information)

6. Daemon could be started independently as well as through the cli.
7. Build automation tool should be used (make for e.g.)
8. It’s up to you to make choice unless otherwise specified.

# Comments on the program:
-  This sniffer is written in C rather than C++ as the former is faster and the scale of the program isn't large enough to apply C++ and OOP. It's been tested on Ubuntu  14.04.5 LTS.
-  The daemon sniffs packets only from one particular interface at a time. The sniffing implementation is based on <i>libpcap</i>. I've read that <i>sock_row</i> and <i>setsockopt</i> functions could be also used, but <i>libpcap</i> appeared to me as easer to use.
-  The name of an interface to sniff is kept in a file; files are also used to save IP statistics when the daemon isn't running (load statistics from previous processes upon start, if any, and save statistics of the current process upon stopping) and process ids. When the user selects new interface to sniff, the name of the previous interface and IP statistics are replaced.
-  AVL tree is used as data structure for keeping statistics (IP addresses and number of incoming packets) while the daemon is running (map from STL, C++, would also be a good choice). It allows for O(log N) to both search number of incoming packets from given IP address and insert new IP address (important when sniffing from pseudo interface "any" or from other interface with many IP addresses). Simple binary search could be also used, but sorting and insertion in O(N) would inhibit the program. 
-  IP is stored in AVL tree as <i>unsigned int</i> after conversion from string (or, to be more correct, array of chars) (e.g. 127.68.52.17 converts into 127 * 256^3 + 68 * 256^2 + 52 * 256 + 17, and conversion back to string IP works similarly). The program supports only IPv4 as otherwise isn't specified.
-  For the purposes of communication with the daemon process, shared memory is used. Data structure of that shared memory consists of pointer – root of AVL tree, boolean flag that the daemon is running, and a buffer for interprocess communication (pipes could be also used).
- To search number of incoming packets from given IP address while the daemon is running (search in AVL tree is iterative, so it isn't heavy on stack), CLI process puts IP in the buffer in the shared memory and sends to the daemon process SIGUSR1 meaning that the daemon should read the buffer, perform the search, and put the number in the buffer. While the daemon isn't running, seach is done in a file in O(N).
-  To stop the daemon, handler of SIGTERM is implemented (saves statistics from AVL tree in a file and only then exists the daemon process).
-  Make is used as build automation tool.
-  To run the program, the user must have root privileges.



