#include "../include/RTI_Settings.h"
#include "../include/Controller_Settings.h"

#include <stdlib.h>
#include <stdio.h>

rti_settings *newRTISettings() {
    rti_settings *settings = calloc(1, sizeof(rti_settings));

    settings->turnedOn = true;
    settings->brightness = 15;

    return settings;
}

void freeRTISettings(rti_settings *settings) {
    free(settings);
}


void saveSettings(rti_settings *settings, const char *path) {
    FILE *fp = fopen(path, "w");

    if (fp == NULL) {
        fprintf(stderr, "\nSettings file cannot be saved to: %s\n", path);
        return;
    }

    fwrite(settings, sizeof(settings), 1, fp);
}


rti_settings *loadSettings(const char *path) {
    FILE *fp = fopen(path, "r");
    rti_settings *settings = NULL;

    if (fp == NULL) {
        fprintf(stderr, "\nSettings file could not be loaded or doesn't exist at: %s\n", path);

        settings = newRTISettings();
        settings->brightness = 15;
        settings->turnedOn = true;

        saveSettings(settings, path);
        fprintf(stderr, "Created new save file at: %s", path);

        return settings;
    }

    fread(settings, sizeof(rti_settings), 1, fp);
    return settings;
}