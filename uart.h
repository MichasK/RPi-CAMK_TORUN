#ifndef _UART__H_
#define _UART__H_


/*
 * Ustawienie portu szeregowego
 */
int configureSerialPort(int uartFilestream, int speedNum );

/*
 * Wyslanie ciagu bitow
 */
int myWrite(int uartFilestream, const char tx_buffer[], int n);

/*
 * Odczyt ciagu bitow okreslonych w n
 */
int myRead(int uartFilestream, char rx_buffer[], int n);


int timeHasPassed(const struct timespec endingTime);

/*
 * Odiberz linie
 */
int readLine(int uartFilestream, char line[], int n, int *received, unsigned int timeoutMs);


/*
 * Wyslanie komendy - Kilka bajtow z suma kontrolna + odebranie sumy kontrolnej
 */
int sendCommand(int uartFilestream, const char command[], int n);

void clearUart(int uartFilestream);
int uart_init();
#endif /*_UART__H_*/
