/* dg_ctrl.c : Sample program for controlling the DG645 via TCP/IP */
/*Version 1.0 072016 Author Alessandro Spilotros*/

/*It makes use of the two channel 1 and 2  (AB,CD) connected in parallel (logical or would be better)*/
/*and generates 3 sequence of pulses, namely seq1 (1,1,0), seq2(1,0,1), seq3(0,1,1) with an adjustable width indicated in milliseconds*/

#include <winsock2.h>
#include <stdio.h>
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
 char whc[100]; /*width of hadamard channel*/
 char whc_i[100]=".001";/*little increment of hadamard channel typically 1 microsecond*/
 int choice;
 
 char str0[100]="0e-3\n";
 char str1[100]="dlay 4,2,"; /*Front C of channel 1*/
 char str1_1[100]="e-3\n";   
 
 char str2[100]="dlay 5,4,"; /*Front D of channel 1*/
 char str2_1[100]="e-3\n";
 
 char str3[100]="dlay 6,5,"; /*Front E of channel 2*/
 char str3_1[100]="e-3\n";
 
 char str4[100]="dlay 7,6,"; /*Front F of channel 2*/
 char str4_1[100]="e-3\n";
 
 int nhc=3; /*number of hadamard channel*/ 

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

/* Width of Hadamard channel*/
   printf("Please input the width of Hadamard channel (ms): ");
   scanf("%s", &whc);
   /*printf("You entered: %lf\n", whc);*/
   printf("whc is= %s\n", whc);

 /* Load default settings */
 dg_write("*rst\n");
/* Set external triggering */
 dg_write("tsrc 1\n"); 
 dg_write("dlay 1,0,0.00001e-3\n");

 /*Set A and B level to 5V*/
 dg_write("lamp 2,5");
 dg_write("lamp 3,5");
 /*Set C and D level to 5V*/
 dg_write("lamp 4,5");
 dg_write("lamp 5,5");
 
  /*Set E and F level to 5V*/
 dg_write("lamp 6,5");
 dg_write("lamp 7,5");
/******************************************/ 
 
 printf("Choose the sequence (type 1 2 3 or 0 to exit): 1 (1,1,0), 2(1,0,1), 3(0,1,1)");
   scanf("%d", &choice); 
while (choice!=1 && choice!=2 &&choice!=3 &&choice!=0) {
    printf("Choose the sequence (type 1 2 3 or 0 to exit): 1 (1,1,0), 2(1,0,1), 3(0,1,1)");
   scanf("%d", &choice);
   }
   printf("You entered: %d\n", choice); 

switch (choice)
{
	case (1):
		/*Sequence  1*/ 
 
		 /*Defining the strings to pass to dgwrite() command */
		 strcat (str1,str0);
		 /*strcat (str1,str1_1);*/
		 strcat (str2,whc);
		 strcat (str2,str2_1);
 
		 strcat (str3,whc_i);
		 strcat (str3,str3_1);
 	
		 strcat (str4,whc);
		 strcat (str4,str4_1);
 
 
 
		  /* Set B = A + 10 ms */
		 dg_write("dlay 2,0,0e-3\n");
		 dg_write(str1);
 
		 /* Set B = A + 10 ms */
		 /*dg_write("dlay 3,2,10e-3\n");*/
		 dg_write(str2);
 
		 /* Set C = 0 + 20 ms */
		 /*dg_write("dlay 4,0,10.001e-3\n");*/
		 dg_write(str3);
 
		 /* Set D = C + 10 ms */
		 /*dg_write("dlay 5,4,10e-3\n");*/
		 dg_write(str4);
	break; 

case (2):
		/*Sequence  2*/ 
 
		 /*Defining the strings to pass to dgwrite() command */
		 strcat (str1,str0);
		 /*strcat (str1,str1_1);*/
		 strcat (str2,whc);
		 strcat (str2,str2_1);
 
		 strcat (str3,whc);
		 strcat (str3,str3_1);
 	
		 strcat (str4,whc);
		 strcat (str4,str4_1);
 
 
 
		  /* Set B = A + 10 ms */
		 /*dg_write("dlay 2,0,0e-3\n");*/
		 dg_write("dlay 2,0,0e-3\n");
		 dg_write(str1);
 
		 /* Set B = A + 10 ms */
		 /*dg_write("dlay 3,2,10e-3\n");*/
		 dg_write(str2);
 
		 /* Set C = 0 + 20 ms */
		 /*dg_write("dlay 4,0,10.001e-3\n");*/
		 dg_write(str3);
 
		 /* Set D = C + 10 ms */
		 /*dg_write("dlay 5,4,10e-3\n");*/
		 dg_write(str4);
	break; 

case (3):
		/*Sequence  3*/ 
		 printf("Sequence 3\n");
 
		 /*Defining the strings to pass to dgwrite() command */
		 strcat (str1,whc);
		 strcat (str1,str1_1);
		 strcat (str2,whc);
		 strcat (str2,str2_1);
 
		 strcat (str3,whc_i);
		 strcat (str3,str3_1);
 	
		 strcat (str4,whc);
		 strcat (str4,str4_1);
 
		/* dg_write("dlay 2,0,10e-3\n");*/
		dg_write("dlay 2,0,0e-3\n");
		 dg_write(str1);
 
		 /* Set B = A + 10 ms */
		 /*dg_write("dlay 3,2,10e-3\n");*/
		 dg_write(str2);
 
		 /* Set C = 0 + 20 ms */
		 /*dg_write("dlay 4,0,10.001e-3\n");*/
		 dg_write(str3);
 
		 /* Set D = C + 10 ms */
		 /*dg_write("dlay 5,4,10e-3\n");*/
		 dg_write(str4);
	break; 


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
