/* dg_ctrl.c : Sample program for controlling the DG645 via TCP/IP */
#include <winsock2.h>
/*#include <Ws2tcpip.h> 
#include <winsock.h>
#include <w32api.h>
#include <winnetwk.h>
#include <ws2spi.h>
#include <wtsapi32.h>*/
#include <stdio.h>
#include <string.h>
/* prototypes */
void init_tcpip(void);
int dg_connect(unsigned long ip);
int dg_close(void);
int dg_write(char *str);
int dg_read(char *buffer, unsigned num);
SOCKET sDG645; /* DG645 tcpip socket */
unsigned dg_timeout = 3000; /* Read timeout in milliseconds */
int main(int argc, char * argv[])
{
 char buffer[1024];
 char whc[100];
 char str1[100]="dlay 2,0,";
 char str2[100]="dlay 3,2,";
 char str3[100]="dlay 4,0,";
 char str4[100]="dlay 5,4,";
 char seq[100];
 int nhc;
 /*double whc;*/
 /* Make sure ip address is supplied on the command line */
 if ( argc < 2 ) {
 printf("Usage: dg_ctrl IP_ADDRESS\n");
 exit(1);
 }
 /* Initialize the sockets library */
 init_tcpip();

 /* Connect to the dg645 */
 if ( dg_connect( inet_addr(argv[1]) ) ) {
 printf("Connection Succeeded\n");

 /* Get identification string */
 dg_write("*idn?\n");
 if ( dg_read(buffer,sizeof(buffer)) )
 printf(buffer);
 else
 printf("Timeout\n");
 
/*******************************************/
/*******************************************/

 /* Load default settings */
 dg_write("*rst\n");
 /* Set burst mode on */
 dg_write("burm 1\n");
 dg_write("burc 60\n");
 dg_write("burp 35e-3\n");
 dg_write("burd 0\n");
 
while(1<2)
	{
		printf("\n Please input seq1 (1110100), seq2 (1101001), seq3 (1010011), seq4(0100111), seq5(1001110), seq6(0011101), seq7(0111010): ");
		scanf("%s", &seq);
		while (strcmp(seq, "seq1")!=0 && strcmp(seq, "seq2")!=0 && strcmp(seq, "seq3")!=0 && strcmp(seq, "seq4")!=0 && strcmp(seq, "seq5")!=0 && strcmp(seq, "seq6")!=0 && strcmp(seq, "seq7")!=0){
		      printf("\n Wrong choice. Please input seq1 (011), seq2 (101), seq3 (110): ");
			  scanf("%s", &seq);
			  }
		
		if(strcmp(seq,"seq1")==0) {
 		 /* Set A = 0 ms */
		dg_write("dlay 2,0,0e-3\n");
 		/* Set B = A + 10 ms */
 		dg_write("dlay 3,2,10e-3\n");
 		/* Set C = 0 + 10 ms */
 		dg_write("dlay 4,0,10.001e-3\n");
 		/* Set D = C + 10 ms */
 		dg_write("dlay 5,4,10e-3\n");
 		/*Set A and B level to 5V*/
 		dg_write("lamp 2,5");
 		dg_write("lamp 3,5");
 		/*Set C and D level to 5V*/
 		dg_write("lamp 4,5");
 		dg_write("lamp 5,5");
 		printf("seq3 (110) sent ");			
					}
		
		if(strcmp(seq,"seq2")==0) {
 		 /* Set A = 0 ms */
		dg_write("dlay 2,0,0e-3\n");
 		/* Set B = A + 10 ms */
 		dg_write("dlay 3,2,10e-3\n");
 		/* Set C = 0 + 20 ms */
 		dg_write("dlay 4,0,20.001e-3\n");
 		/* Set D = C + 10 ms */
 		dg_write("dlay 5,4,10e-3\n");
 		/*Set A and B level to 5V*/
 		dg_write("lamp 2,5");
 		dg_write("lamp 3,5");
 		/*Set C and D level to 5V*/
 		dg_write("lamp 4,5");
 		dg_write("lamp 5,5");
 		printf("seq2 (101) sent ");			
					}
		
		if(strcmp(seq,"seq3")==0) {
 		 /* Set A = 0 + 10 ms */
		dg_write("dlay 2,0,10e-3\n");
 		/* Set B = A + 10 ms */
 		dg_write("dlay 3,2,10e-3\n");
 		/* Set C = 0 + 20 ms */
 		dg_write("dlay 4,0,20.001e-3\n");
 		/* Set D = C + 10 ms */
 		dg_write("dlay 5,4,10e-3\n");
 		/*Set A and B level to 5V*/
 		dg_write("lamp 2,5");
 		dg_write("lamp 3,5");
 		/*Set C and D level to 5V*/
 		dg_write("lamp 4,5");
 		dg_write("lamp 5,5");
 		/*Settings seq 1 completed*/
		printf("seq1 (011) sent ");	   	   
		
					}
	}
/*********************************************************************/
/********************************************************************/

 /* Make sure all commands have executed before closing connection */
 dg_write("*opc?\n");
 if ( !dg_read(buffer,sizeof(buffer)) )
 printf("Timeout\n");
 /* Close the connection */
 if (dg_close())
 printf("Closed connection\n");
 else
 printf("Unable to close connection");
 }
 else
 printf("Connection Failed\n");
return 0;
} 

void init_tcpip(void)
{
 WSADATA wsadata;
 if ( WSAStartup(2, &wsadata) != 0 ) {
 printf("Unable to load windows socket library\n");
 exit(1);
 }
}
int dg_connect(unsigned long ip)
{
 /* Connect to the DG645 */
 struct sockaddr_in intrAddr;
 int status;
 sDG645 = socket(AF_INET,SOCK_STREAM,0);
 if ( sDG645 == INVALID_SOCKET )
 return 0;
 /* Bind to a local port */
 memset(&intrAddr,0,sizeof(intrAddr));
 intrAddr.sin_family = AF_INET;
 intrAddr.sin_port = htons(0);
 intrAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
 if ( SOCKET_ERROR == bind(sDG645,(const struct sockaddr *)&intrAddr,sizeof(intrAddr)) ) {
 closesocket(sDG645);
 sDG645 = INVALID_SOCKET;
 return 0;
 }
 /* Setup address for the connection to dg on port 5025 */
 memset(&intrAddr,0,sizeof(intrAddr));
 intrAddr.sin_family = AF_INET;
 intrAddr.sin_port = htons(5025);
 intrAddr.sin_addr.S_un.S_addr = ip;
 status = connect(sDG645,(const struct sockaddr *)&intrAddr,sizeof(intrAddr));
 if ( status ) {
 closesocket(sDG645);
 sDG645 = INVALID_SOCKET;
 return 0;
 }
 return 1;
}
int dg_close(void)
{
 if ( closesocket(sDG645) != SOCKET_ERROR )
 return 1;
 else
 return 0;
}
int dg_write(char *str)
{
 /* Write string to connection */
 int result;

 result = send(sDG645,str,(int)strlen(str),0);
 if ( SOCKET_ERROR == result )
 result = 0;
 return result;
}

int dg_read(char *buffer, unsigned num)
{
 /* Read up to num bytes from connection */
 int count;
 fd_set setRead, setWrite, setExcept;
 TIMEVAL tm;

 /* Use select() so we can timeout gracefully */
 tm.tv_sec = dg_timeout/1000;
 tm.tv_usec = (dg_timeout % 1000) * 1000;
 FD_ZERO(&setRead);
 FD_ZERO(&setWrite);
 FD_ZERO(&setExcept);
 FD_SET(sDG645,&setRead);
 count = select(0,&setRead,&setWrite,&setExcept,&tm);
 if ( count == SOCKET_ERROR ) {
 printf("select failed: connection aborted\n");
 closesocket(sDG645);
 exit(1);
 }
 count = 0;
 if ( FD_ISSET(sDG645,&setRead) ) {
 /* We've received something */
 count = (int)recv(sDG645,buffer,num-1,0);
 if ( SOCKET_ERROR == count ) {
 printf("Receive failed: connection aborted\n");
 closesocket(sDG645);
 exit(1);
 }
 else if (count ) {
 buffer[count] = '\0';
 }
 else {
 printf("Connection closed by remote host\n");
 closesocket(sDG645);
 exit(1);
 }
 }
 return count;
} 
