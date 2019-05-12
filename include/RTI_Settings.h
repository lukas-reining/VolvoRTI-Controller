//
// Provides functions to save RTI settings to the filesystem and to load them from there.
//
#include <stdbool.h>

#ifndef RTICONTROLLER_RTI_SETTINGS_H
#define RTICONTROLLER_RTI_SETTINGS_H

typedef struct setting{
    bool turnedOn;
    unsigned char brightness;
} rti_settings;

/**
 * Allocates a new RTI setting.
 * @return Pointer to the new allocated RTI settings.
 */
rti_settings *newRTISettings();

/**
 * Frees the given allocated RTI settings pointer.
 * @param settings The pointer to free.
 */
void freeRTISettings(rti_settings *settings);


/**
 * Loads the settings saved in a file and returns them as rti_settings struct pointer.
 * If file cannot be loaded or is invalid, a standard setting is returned.
 * In this case, the function tries to save the default values to the path.
 *
 * @param filePath The path to load the settings from.
 * @return The loaded settings. (Or if not found, default settings)
 */
rti_settings *loadSettings(const char *filePath);


/**
 * Saves the given settings pointer to the given path.
 *
 * @param settings The settings to save on disk.
 * @param path The path to save to.
 */
void saveSettings(rti_settings *settings, const char *path);

#endif //RTICONTROLLER_RTI_SETTINGS_H
