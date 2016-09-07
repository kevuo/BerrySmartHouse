#include <gpio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#define RPI_GPIO_EXPORT "/sys/class/gpio/export"
#define RPI_GPIO_UNEXPORT "/sys/class/gpio/unexport"
#define MAXBUFFER 64	

//Establishes the given pin number as input or output.
int pinMode(int pin, int mode){
//Variables declaration.
FILE *exp; 
FILE *direction;
char modeValue[MAXBUFFER]; 
char path[MAXBUFFER];

//Export given pin.
exp = fopen(RPI_GPIO_EXPORT, "w");
if (exp == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
//Write the pin number to file.
fprintf(exp, "%d", pin);

//Close file after write.
fclose(exp);

//Assign port direction.
if(mode==0){
	strcpy(modeValue, "in");
}else{
	strcpy(modeValue, "out");
}

sprintf(path, "/sys/class/gpio/gpio%d/direction", pin);

//Write port direction to file.
direction = fopen(path, "w");
if (direction == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

fprintf(direction, "%s", modeValue);
fclose(direction);

return(0);
}

//Sets the input value to the given pin. (1:ON, 0:OFF)
int digitalWrite(int pin, int value){
	//Variables declaration.
	int fileDescriptor;
	char v;
	char buffer[MAXBUFFER];

	//Open file and set as write only.
	sprintf(buffer, "/sys/class/gpio/gpio%d/value", pin);
	fileDescriptor= open(buffer, O_WRONLY);

	if(value==1){
		v='1';
	}
	else if (value==0)
	{
		v='0';
	}
	//Write value to file.
	if(fileDescriptor==-1){
		fprintf(stderr, "Failed to open gpio pin\n");
		return(-1);
	}
	if(write(fileDescriptor, &v,1)!=1){
		fprintf(stderr, "Failed to write value\n");
		return(-1);
	}

	//Close file.
	close(fileDescriptor);
	return(0);
}

//Reads the value held by given pin.
int digitalRead(int pin){
	//Variables declaration
	int fileDescriptor;
	char buffer[MAXBUFFER];
	char value[3];

	//Open file and set as read only.
	sprintf(buffer, "/sys/class/gpio/gpio%d/value", pin);
	fileDescriptor= open(buffer, O_RDONLY);

	//Read value from file.
	if(fileDescriptor==-1){
		fprintf(stderr, "Failed to open gpio pin\n");
		return(-1);
	}
	if(read(fileDescriptor,&value,1)==-1){
		fprintf(stderr, "Failed to read value\n");
		return(-1);
	}
	//Close file and return read value.
	close(fileDescriptor);
	return(atoi(value));
}
//Turns on and off a LED connected to the given pin
//in the input frequency and duration.
int blink(int pin, double freq, double duration){
	//Variables declaration.
	time_t start,end;
	double elapsed;
	int condition=1;
	time(&start);
	//Loop that turns on and off the LED.
	while(condition){
		time(&end);
		elapsed=difftime(end,start);
		if(elapsed>= duration){
			condition=0;
		}
		digitalWrite(pin,0);
		delay(freq);
		digitalWrite(pin,1);
		delay(freq);
	}
	digitalWrite(pin,0);
	return (0);
}

//Auxiliar function in charge of holding up the given time.
void delay(double dly){
 time_t start = time(NULL);
 time_t current;

 while(difftime(current, start) < dly){
  time(&current);
 }
}

//Unexports the given pin.
int unexportPin(int pin){
//Variables declaration.
FILE *unexp;

//Open file for writing.
unexp = fopen(RPI_GPIO_UNEXPORT, "w");
if (unexp == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}

//Unexport the pin.
fprintf(unexp, "%d", pin);
fclose(unexp);
return(0);
}