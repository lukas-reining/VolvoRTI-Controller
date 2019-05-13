#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

#include <wiringPi.h>
#include <wiringSerial.h>

#include "../include/Volvo_RTI.h"
#include "../include/Controller_Settings.h"
#include "../include/RTI_Settings.h"

/**
 * Uses wiringPi to provide functions for controlling the RTI system over serial.
 * wiringPi has to be initialized before the functions can be called!!
 */

// Serial stuff
int serial_descriptor;

//Display variables
volatile bool displayOn = true; //Display on?
volatile unsigned char current_brightness_level = 15;
const int rti_delay = 100; //delay between bytes, ms

/**
 * Interrupt stuff, used to track the time an interrupt has not been used, to implement debouncing.
 */
//Interrupt variables MODE
const short debounce_time_mode = 300; //Debounce time/delay in milliseconds
unsigned long last_interrupt_time_mode = 0;

//Interrupt variables BRIGHTNESS
const short debounce_time_brightness = 300; //Debounce time/delay in milliseconds
unsigned long last_interrupt_time_brightness = 0;


// Saves the current settings state to the disk
void save() {
    rti_settings *settings = newRTISettings();
    settings->brightness = current_brightness_level;
    settings->turnedOn = displayOn;
    saveSettings(settings, SETTINGS_PATH);
}

/**
 * Callback function to be called when displayState button is pressed to perform toggling.
 */
void toggleDisplayState() {
    unsigned long interrupt_time = millis();
    // If interrupts come faster than debounce_time, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time_mode > debounce_time_mode) {
        displayOn = !displayOn;

        save();

        printf("DisplayMode: %s\n", displayOn ? "ON" : "OFF");
        fflush(stdout);
    }
    last_interrupt_time_mode = interrupt_time;
}


/**
 * Callback function to be called when displayBrightness button is pressed to perform toggling.
 */
void changeBrightness() {
    unsigned long interrupt_time = millis();
    // If interrupts come faster than debounce_time, assume it's a bounce and ignore
    if (interrupt_time - last_interrupt_time_brightness > debounce_time_brightness) {
        current_brightness_level++;
        if (current_brightness_level > 15) {
            current_brightness_level = 0;
        }

        save();

        printf("Brightness set to: %i\n", current_brightness_level);
        fflush(stdout);
    }
    last_interrupt_time_brightness = interrupt_time;
}


void initialiseRTI() {
    //Start wiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stdout, "Unable to start wiringPi: %s\n", strerror(errno));
        exit(-1);
    }

    //Initialise pins
    pinMode(PIN_BUTTON_BRIGHTNESS, INPUT);
    pinMode(PIN_BUTTON_MODE, INPUT);

    //Register interrupts for buttons
    pullUpDnControl(PIN_BUTTON_MODE, PUD_UP);
    if (wiringPiISR(PIN_BUTTON_MODE, INT_EDGE_FALLING, toggleDisplayState)
        < 0) {
        fprintf(stderr, "Unable to setup ISR for screen mode button: %s\n", strerror(errno));
        exit(-1);
    }

    pullUpDnControl(PIN_BUTTON_BRIGHTNESS, PUD_UP);
    if (wiringPiISR(PIN_BUTTON_BRIGHTNESS, INT_EDGE_FALLING, changeBrightness)
        < 0) {
        fprintf(stderr, "Unable to setup ISR for brightness button: %s\n", strerror(errno));
        exit(-1);
    }

    //Load settings from disk
    rti_settings *settings = loadSettings(SETTINGS_PATH);

    displayOn = settings->turnedOn;
    current_brightness_level = settings->brightness;

    freeRTISettings(settings);

    //Open serial uart on Pi-Pin 8
    if ((serial_descriptor = serialOpen("/dev/ttyS0", 2400)) < 0) { //TODO For PI1 and PI2 use ttyAMA0
        fprintf(stderr, "Unable to open serial device: %s\n", strerror(errno));
        exit(-1);
    }
}

void rtiWrite(char byte) {
    serialPutchar(serial_descriptor, byte);
    delay(rti_delay);
}


void rtiWriteAll() {
    if (displayOn) {
        rtiWrite(DISPLAY_MODE);
    } else {
        rtiWrite(RTI_DISPLAYMODE_OFF);
    }

    if (SEND_BRIGHTNESS) {
        rtiWrite(0x2F); //TODO SEND right brightness
    }

    rtiWrite(RTI_MESSAGE_END);
}