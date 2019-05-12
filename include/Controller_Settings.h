//
// Created by Lukas Reining on 12.05.2019.
//

#include <stdbool.h>

#ifndef RTICONTROLLER_CONTROLLER_SETTINGS_H
#define RTICONTROLLER_CONTROLLER_SETTINGS_H

#define SETTINGS_PATH           "/home/pi/carpc/Navidisplaysteuerung/screen_save.save"

#define DISPLAY_MODE            RTI_DISPLAYMODE_PAL // The displaymode to use (from Volvo_RTI.h)

#define PIN_BUTTON_MODE         0 //Pin for Toggle-Button(wiringPi-layout)
#define PIN_BUTTON_BRIGHTNESS   1 //Pin for Toggle-Button(wiringPi-layout)
#define PIN_BUTTON_TIMESET      5 //Pin for Timesetting-Button(wiringPi-layout)
#define PIN_LED_GREEN           2 //Pin for LED_GREEN
#define PIN_LED_RED             3 // Pin for LED_RED

#define LONG_PRESS_MILLIS       1000 //Time in millis, a long press takes

#define SEND_BRIGHTNESS         true //Sets if brightness should be sent to rti

#endif //RTICONTROLLER_CONTROLLER_SETTINGS_H
