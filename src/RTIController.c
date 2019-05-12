#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <wiringSerial.h>

#include "../include/Volvo_RTI.h"
#include "../include/RaspberryRTI.h"
#include "../include/Controller_Settings.h"


//Application running ?
bool keepRunning = true;

/**
 * Interrupt stuff, used to track the time an interrupt has not been used, to implement debouncing.
 */
//Interrupt variables MODE
const short debounce_time_time = 300; //Debounce time/delay in milliseconds
unsigned long last_interrupt_time_time = 0;


//Only for interrupt setTime
void setTime() {
    unsigned long interrupt_time = millis();
    // If interrupts come faster than debounce_time, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time_time > debounce_time_time) {
        digitalWrite(PIN_LED_GREEN, 255);
        printf("Getting time from NTP.....\n");
        system("sudo ntpd -gq"); //Set systemtime from ntp
        system("sudo hwclock -w"); // Write to rtc
        printf("Time set from NTP\n");
        fflush(stdout);
        delay(1000);
        digitalWrite(PIN_LED_GREEN, 0);
    }
    last_interrupt_time_time = interrupt_time;
}

void initialise() {
    //Start wiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        exit(-1);
    }

    //Set Pins
    pinMode(PIN_BUTTON_TIMESET, INPUT);
    pinMode(PIN_LED_GREEN, OUTPUT);
    pinMode(PIN_LED_RED, OUTPUT);

    //Register interrupts for buttons
    pullUpDnControl(PIN_BUTTON_TIMESET, PUD_UP);
    if (wiringPiISR(PIN_BUTTON_TIMESET, INT_EDGE_FALLING, setTime) < 0) {
        fprintf(stderr, "Unable to setup ISR for timeset button: %s\n", strerror(errno));
        exit(-1);
    }
}


int main(int argc, char *argv[]) {
    //Check for commandline arguments
    if (argc > 0) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-d") == 0) {
                //TODO ADD Options
            } else {
                printf("Wrong Argument '%s' will be ignored!", argv[i]);
            }
        }
    }

    // Init everything
    initialise();
    initialiseRTI();

    // Main loop
    while (keepRunning) {
        rtiWriteAll();
    }

    return 0;
}

