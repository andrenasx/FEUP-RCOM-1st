#include "socket.h"

int init_connection(char* ip, int port) {
    int	sockfd;
	struct sockaddr_in server_addr;
	
	/*server address handling*/
	bzero((char*)&server_addr,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(ip);	/*32 bit Internet address network byte ordered*/
	server_addr.sin_port = htons(port);		/*server TCP port must be network byte ordered */
    
	/*open an TCP socket*/
	if ((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
    	fprintf(stderr, "Error opening socket!\n");
        return -1;
    }

	/*connect to the server*/
    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
        fprintf(stderr, "Error connecting to server!\n");
		return -1;
	}

    return sockfd;
}

int write_to_socket(int sockfd, char *message) {
    int bytes;
	int msg_len = strlen(message);

    if((bytes = write(sockfd, message, msg_len)) != msg_len){
        fprintf(stderr, "Error writing message to socket!\n");
        return -1;
    }

    printf("> %s", message);
    return 0;
}

int read_from_socket(int sockfd){
    FILE* fp = fdopen(sockfd, "r");

	char* buf;
	size_t bytesRead = 0;
	int response_code;

	while(getline(&buf, &bytesRead, fp) > 0){
		printf("< %s", buf);
		if(buf[3] == ' '){
			sscanf(buf, "%d", &response_code);
			break;
		}
	}

	return response_code;
}

int read_passivemode(int sockfd, char *ip, int *port){
	FILE* fp = fdopen(sockfd, "r");

	char* buf;
	size_t bytesRead = 0;
	int response_code;

	while(getline(&buf, &bytesRead, fp) > 0){
		printf("< %s", buf);
		if(buf[3] == ' '){
			sscanf(buf, "%d", &response_code);
			break;
		}
	}

	//parse ip address and port
	char *find;
	int ip1, ip2, ip3, ip4, p1, p2;

	find = strrchr(buf, '(');
	sscanf(find, "(%d,%d,%d,%d,%d,%d)", &ip1, &ip2, &ip3, &ip4, &p1, &p2);

	sprintf(ip, "%d.%d.%d.%d", ip1, ip2, ip3, ip4);

  	*port = p1*256+p2;
  
  	return response_code;
}