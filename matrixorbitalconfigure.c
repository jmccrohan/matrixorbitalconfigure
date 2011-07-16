/*
 * matrixorbitalconfigure.c
 *
 * Copyright (C) 2011 - Jonathan McCrohan
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/signal.h>
#include <sys/types.h>
#define BAUDRATE B19200
#define device "/dev/ttyUSB0"
int main(int argc, char *argv[]){

	// open serial port
	struct termios term;
	int lcd = open(device, O_RDWR | O_NOCTTY | O_NONBLOCK);
	if (lcd < 0){
		printf("Error opening serial port %s\n",device);
		return -1;
	}

	// serial port config: 8N1
	term.c_cflag = BAUDRATE | CS8 | CSTOPB | CLOCAL | CREAD;
	term.c_iflag = 0;
	term.c_oflag = 0;
	term.c_lflag = 0;
	tcflush(lcd, TCIFLUSH);
	tcsetattr(lcd,TCSANOW,&term);

	// send mes
	unsigned char msg[] = {254,152,atoi(argv[1])};
	write(lcd,msg,sizeof(msg));
	
	close(lcd);
	return 0;
}
