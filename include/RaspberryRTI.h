//
// Created by Lukas Reining on 12.05.2019.
//

#ifndef RTICONTROLLER_RASPBERRYRTI_H
#define RTICONTROLLER_RASPBERRYRTI_H

/**
 * Call to initialise wiringpi, pins and interrupts and get initial state of screen
 * Exits, if anything essential like initialising wiringPi goes wrong.
 */
void initialiseRTI();

/**
 * Writes a single byte to the serial connected to the RTI.
 * @see initialiseRTI has to be called before.
 * @param byte The byte to send.
 */
void rtiWrite(char byte);


/**
 * Only function cou have to call afte @see initialiseRTI.
 * Sends all information managed by the RaspberryRTI to the rti.
 */
void rtiWriteAll();

#endif //RTICONTROLLER_RASPBERRYRTI_H
