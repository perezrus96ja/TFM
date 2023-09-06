#include <stdio.h>
#include <string.h>

#include <fcntl.h>    // File controls
#include <errno.h>    // Error integer and strerror() function
#include <termios.h>  // POSIX terminal control definitions
#include <unistd.h>   // write(), read(), close()


int main()
{
	int serial_port = open("/dev/ttyUSB2", O_RDWR);

	if (serial_port < 0) {
		printf("Error %i from open: %s\n", errno, strerror(errno));
	}

	struct termios tty;

	if (tcgetattr(serial_port, &tty) != 0) {
		printf("Error %i from tcgetattr: %s\n", errno, strerror(errno));
		return 1;
	}

	tty.c_cflag &= ~PARENB;
  	tty.c_cflag &= ~CSTOPB;
 	tty.c_cflag &= ~CSIZE;
 	tty.c_cflag |= CS8;
  	tty.c_cflag &= ~CRTSCTS;
  	tty.c_cflag |= CREAD | CLOCAL;

  	tty.c_lflag &= ~ICANON;
  	tty.c_lflag &= ~ECHO;
  	tty.c_lflag &= ~ECHOE;
  	tty.c_lflag &= ~ECHONL;
  	tty.c_lflag &= ~ISIG;
  	tty.c_iflag &= ~(IXON | IXOFF | IXANY);
  	tty.c_iflag &= ~(IGNBRK|BRKINT|PARMRK|ISTRIP|INLCR|IGNCR|ICRNL);

	tty.c_oflag &= ~OPOST;
  	tty.c_oflag &= ~ONLCR;

	tty.c_cc[VTIME] = 10;
	tty.c_cc[VMIN] = 128;

	cfsetispeed(&tty, B115200);
	cfsetospeed(&tty, B115200);

	if (tcsetattr(serial_port, TCSANOW, &tty) != 0) {
		printf("Error %i from tcsetattr: %s\n", errno, strerror(errno));
		return 1;
	}


 //WRITE TO SERIAL PORT

	
	char write_buf [128] = "AT\r\0"; 

	write(serial_port, write_buf, sizeof(write_buf));

	unsigned char read_buf [256];

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	int num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

//PIN SIM

	strcpy(write_buf, "AT+CPIN=4964\r\0");

	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

	
// SABER LA FUNCIONALIDAD DEL SISTEMA


	strcpy(write_buf, "AT+CFUN?\r\0");

	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// CONECTAR A CONTEXTO PDP 1

	strcpy(write_buf, "AT+CGACT=1,1\r\0");

	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// ABRIR LA NET

	strcpy(write_buf, "AT+NETOPEN\r\0");

	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);
	
// CIPOPEN

	strcpy(write_buf, "AT+CIPOPEN=1,\"UDP\",,,8080\r\0");

	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// ENVIAR POR UDP EN EL CIP 1

	strcpy(write_buf, "AT+CIPSEND=1,5,\"2.0.0.0\",0\r\0");

	write(serial_port, write_buf, sizeof(write_buf));
	
	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);
	
	strcpy(write_buf, "HELLO\r\0");
	write(serial_port, write_buf, sizeof(write_buf));

	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);


// CAMBIAR A FUNCIONALIDAD 0

	strcpy(write_buf, "AT+CFUN=0\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// USO DE PUERTO SERIE CON FUNCIONALIDAD 0

	strcpy(write_buf, "AT\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// CAMBIO A FUNCIONALIDAD 4

	strcpy(write_buf, "AT+CFUN=4\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

//USO DE CPIN CON FUNCIONALIDAD 4

	strcpy(write_buf, "AT+CPIN=?\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// CONSULTAR ESTADO DE PIN EN FUNCIONALIDAD 4


	strcpy(write_buf, "AT+CPIN?\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// PONER PIN EN FUNCIONALIDAD 4


	strcpy(write_buf, "AT+CPIN=4964\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// CAMBIO A FUNCIONALIDAD 7


	strcpy(write_buf, "AT+CFUN=7\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);

// CAMBIO A FUNCIONALIDAD 1 DESDE 7


	strcpy(write_buf, "AT+CFUN=1,1\r\0");

	write(serial_port, write_buf, sizeof(write_buf));


	memset(&read_buf, '\0', sizeof(read_buf));
	
	fflush(NULL);

	num_bytes = read(serial_port, &read_buf, sizeof(read_buf));
	
	fflush(NULL);
	

	if (num_bytes < 0) {
	printf("Error reading: %s", strerror(errno));
	return 1;
  	}
	
	printf("Read %i bytes \n", num_bytes);
	printf("Received message: %s \n", read_buf);
	
	memset(read_buf, 0, sizeof read_buf);


  	close(serial_port);
  	return 0;

};


