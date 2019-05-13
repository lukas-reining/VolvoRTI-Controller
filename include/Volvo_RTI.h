/**
 * Defines for the values to send to the RTI system over serial to controll it.
 */

#ifndef RTICONTROLLER_VOLVO_RTI_H
#define RTICONTROLLER_VOLVO_RTI_H

#define RTI_MESSAGE_END         0x83

#define RTI_DISPLAYMODE_RGB     0x40
#define RTI_DISPLAYMODE_NTSC    0x45
#define RTI_DISPLAYMODE_PAL     0x4C
#define RTI_DISPLAYMODE_OFF     0x46

static const char brightness_levels[] = { 0x20, 0x61, 0x62, 0x23, 0x64, 0x25, 0x26,
                                   0x67, 0x68, 0x29, 0x2A, 0x2C, 0x6B, 0x6D, 0x6E, 0x2F };

#endif //RTICONTROLLER_VOLVO_RTI_H
