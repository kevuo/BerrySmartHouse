//Created by manzumbado 
//Last edited: September 7, 2016

#include <gpio.h>
#include <json.h>
#include <stdio.h>
#include <stdlib.h>

int ledGPIOArray[6] = {4, 5, 6, 12, 13, 16};
int doorGPIOArray[4]={17, 18, 19, 20};
int garageGpio=21;


//This is intended a an wrapper around the gpio dynamic library
//to be used in nodejs, as a server in a tiny but powerfull raspberry pi
//The way is designed allows to write to raspberry's gpio pins, and provide
//a simple interface to be called as an binary with parameters.
int main(int argc,char *argv[]){
	

//Set up pins as inputs or outputs as needed
int configure(){
	printf("%s\n", "enter config");

	//Configure leds pin as outputs
	for(int i=0; i<6; i++){
		pinMode(ledGPIOArray[i], 1);
	}
	//Configure doors pins as inputs
	for(int i=0; i<4; i++){
		pinMode(doorGPIOArray[i], 0);
	}
	//Configure garage pin as output
	pinMode(garageGpio,1);

	return 0;
}

//Free Pins
int freePins(){

	//Unexport leds pin as outputs
	for(int i=0; i<6; i++){
		unexportPin(ledGPIOArray[i]);
	}
	//Unexport doors pins 
	for(int i=0; i<4; i++){
		unexportPin(doorGPIOArray[i]);
	}
	//Unexport garage pin 
	unexportPin(garageGpio);

	return 0;
}

//Set pin value as 1 or 0, parameters pinNumChar ('0' or '1') and valueChar 
//are are char pointers. Return 

int setPinValue( char * pinNumChar, char * valueChar){
	int pinNum=strtol(pinNumChar, NULL, 10);
	int pinValue= strtol(valueChar, NULL, 10);
  	digitalWrite(pinNum, pinValue);
  	return 0;
}


//Get lights state while building JSON file, the return created JSON
int lightsState(){
	json_object * jsonObjTop = json_object_new_object();
	json_object * jsonArray = json_object_new_array();
	//loop over gpio pins
	for(int i = 0; i<6; i++){
		int res= digitalRead(ledGPIOArray[i]);
		json_object * jsonObj= json_object_new_object();
		json_object * jPinNum= json_object_new_int(ledGPIOArray[i]);
		json_object * jPinValue = json_object_new_int(res);
		json_object_object_add(jsonObj,"pin",jPinNum);
		json_object_object_add(jsonObj,"value",jPinValue);
		json_object_array_add(jsonArray,jsonObj);
	}
	json_object_object_add(jsonObjTop,"lights",jsonArray);
	//its better to return a string rather than open and write a file
	//FILE *fp = fopen("../data/lightsState.json", "w");
	printf("%s", json_object_to_json_string(jsonObjTop));
	return 0;
}

//Get doors state while building JSON file, then return created JSON file
int doorsState(){
	json_object * jsonObjTop = json_object_new_object();
	json_object * jsonArray = json_object_new_array();
	//loop over gpio pins
	for(int i = 0; i<4; i++){
		int res= digitalRead(doorGPIOArray[i]);
		json_object * jsonObj= json_object_new_object();
		json_object * jPinNum= json_object_new_int(doorGPIOArray[i]);
		json_object * jPinValue = json_object_new_int(res);
		json_object_object_add(jsonObj,"pin",jPinNum);
		json_object_object_add(jsonObj,"value",jPinValue);
		json_object_array_add(jsonArray,jsonObj);
	}
	json_object_object_add(jsonObjTop,"lights",jsonArray);
	//its better to return a string rather than open and write a file
	//FILE *fp = fopen("../data/lightsState.json", "w");
	printf("%s", json_object_to_json_string(jsonObjTop));
	return 0;
}

//Get garage state while building JSON file, then return created JSON file
int garageState(){

	int res= digitalRead(garageGpio);
	json_object * jsonObj= json_object_new_object();
	json_object * jPinNum= json_object_new_int(garageGpio);
	json_object * jPinValue = json_object_new_int(res);
	json_object_object_add(jsonObj,"pin",jPinNum);
	son_object_object_add(jsonObj,"value",jPinValue);
	//its better to return a string rather than open and write a file
	//FILE *fp = fopen("../data/lightsState.json", "w");
	printf("%s", json_object_to_json_string(jsonArray));
	return 0;
}

//Perform system command to take a picture with gstreammer1.0
int takePicture(){

	system("gst-launch-1.0 -e v4l2src num-buffers=4 ! jpegenc ! filesink location=app/data/webcamshoot.jpeg");
	return 0;
}

//Print help
void help(){
	printf("%s\n", "You must type one of the folowing options");
	printf("%s\n", "'-c' to configure pins");
	printf("%s\n", "'-l' to get lights state");
	printf("%s\n", "'-d' to get doors state");
	printf("%s\n", "'-g' to get garage door state");
	printf("%s\n", "'-s pinNumber value' to set pin value");
	printf("%s\n", "'-f to free pins");
	printf("%s\n", "'-h' to display this help");
}


//Decode options
if(argc>1 && argv[1][0] == '-'){

		switch (argv[1][1]){

			case 'c':
							configure();
							break;
			case 'l':
						  	lightsState();
						  	break;
			case 'd':
						  	doorsState();
						  	break;
			case 'g':
						  	garageState();
						  	break;
			case 's':
							setPinValue(argv[2], argv[3]);
						  	break;
			case 'f':
							freePins();
							break;
			case 't':
							takePicture();
							break;
			case 'h':
					help();
					break;
			default:
					printf("%s\n", "You must type a valid argument, type '-h' as an argument for help");
					break;

		}

	} else {
		printf("%s\n", "You must type an option, type -h for help");
	}
}
