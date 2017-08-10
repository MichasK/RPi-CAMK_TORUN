#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h> /*for UART*/
#include <fcntl.h> /*for UART*/
#include <termios.h> /*for UART*/
//#include <jpeglib.h> /*for jpeg's*/
//#define _BSD_SOURCE
//#include "defines.h" /*for constants*/
#include "uart.h" /*for reading and writing to UART*/
#include <time.h>

int configureSerialPort(int uartFilestream, int speedNum )
{
  int speeds[] = { 9600,19200,38400,57600,115200,230400,460800 };
  speed_t speeds_t[] = { B9600 , B19200, B38400, B57600, B115200, B230400, B460800 };
  speed_t speed = speeds_t[speedNum];

  struct termios options;
  /*TRY OPEN UART IF NOT OPENED*/
  if(uartFilestream == -1)
    {
      //fprintf(stderr,"No UART opened, abort serial configuration\n");
      return -1;
    }
  else
    {
  /*CONFIGURE THE UART*/

  /*struct termios options;*/

  tcgetattr(uartFilestream, &options);
  cfsetispeed(&options, speed); /*set baud-rate*/
  cfsetospeed(&options, speed); /*set baud-rate*/
  options.c_cflag = speed | CS8 | CLOCAL | CREAD; /*set baud-rate*/
  options.c_cflag &= ~CSTOPB;
  /*options.c_iflag = (IGNPAR | ICRNL );*/
  options.c_iflag &= ~(ISTRIP | IGNBRK | ICRNL | INLCR | PARMRK | INPCK | ISTRIP | IXON);
  /*options*/
  options.c_oflag = 0;
  options.c_lflag &= ~(ICANON|ECHO|ISIG|ECHONL|IEXTEN);

  options.c_cc[VTIME] = 2;
  options.c_cc[VMIN] = 0;
  usleep(200*1000);
  tcflush(uartFilestream, TCIOFLUSH);
  tcsetattr(uartFilestream, TCSANOW,&options);

  //printf("Baud rate set to %d\n",speed);

  return 0;
    }
}

/*
 * Wyslanie ciagu bitow
 */
int MyWrite(int uartFilestream, const char tx_buffer[], int n)
{
  int count;

  if(uartFilestream != -1)
    {
        count = write(uartFilestream,tx_buffer,n);
	if(count == -1)
	  {
	    //fprintf(stderr, "Blad komunikacji\n");
	    return -1;
	  }
      return count;
    }
  else
    {
      //fprintf(stderr, "Blad otwarcia UARTu\n");
      return -1;
    }
}

/*
 * Odczyt ciagu bitow okreslonych w n
 */
int MyRead(int uartFilestream, char rx_buffer[], int n)
{

  int count = 0;

  if(uartFilestream != -1)
    {
      count = read(uartFilestream,rx_buffer, n);

      if(count < 0)
	{
	  perror("UART RX error");
	  return -1;
	}
      else if(count == 0)
	{
	  fprintf(stdout,"No data, waiting...\n");
	  return 0;
	}
      else
	{
	  rx_buffer[count] = '\0';
	  //fprintf(stdout," %i bytes read: %s\n", count, rx_buffer);
	  return count;
	}
    }
  else
    {
      fprintf(stderr,"UART not opened\n");
      return -1;
    }
}

/*!
 *
 */
int timeHasPassed(const struct timespec endingTime)
{
  struct timespec  now;

  clock_gettime(CLOCK_REALTIME,&now);

  return now.tv_sec > endingTime.tv_sec ||
        (now.tv_sec == endingTime.tv_sec &&
         now.tv_nsec > endingTime.tv_nsec) ;
}


void clearUart(int uartFilestream)
{
  tcflush(uartFilestream, TCIOFLUSH);
}

int readLine(int uartFilestream, char line[], int n, int *received, unsigned int timeoutMs)
{
  struct timespec  endingTime;
  int num = 0;
  int end = 0;
  clock_gettime(CLOCK_REALTIME,&endingTime);

  endingTime.tv_sec += timeoutMs/1000;
  endingTime.tv_nsec += (long int)((timeoutMs % 1000)*1000000);
  *received = 0;

  //  tcflush(uartFilestream, TCIOFLUSH);

  if(uartFilestream != -1)
  {

    do {

      if((num = read(uartFilestream, line + (*received), 1)) != -1)
      {

        *received += num;
        //usleep(10);
      }

      if(*received > 0)
      {
	       if(line[(*received)-1] == '\n')
            end = 1;
      }

      if(timeHasPassed(endingTime) || (*received >= (n-1)))
      {
        end = 1;
      }

    } while(!end);
    line[*received] = '\0';
  }
  else
  {
    printf("Uart error\n");
  }
  //printf("\n%d\n",*received);

  return *received;

}


int sendCommand(int uartFileStream, const char command[], int n)
{
  char rx_buffer[1024];
  char tx_buffer[1024];
  int count  = 0;
  int i = 0;
  tcflush(uartFileStream, TCIOFLUSH);
  usleep(10*1000);

  /*for(i = 0 ; i < n ; i++)*/
  /*tx_buffer[i] = command[i];*/

  count = MyWrite(uartFileStream, command, n);
  if(count > 0)
  {
      //printf("Writing %s , checksum %c \n",command,checksum);

      count = MyWrite(uartFileStream,tx_buffer,1);
      if(count > 0)
	    {
          return 0;
      }
  }
  else
	{
	    return -1;
	}

}
