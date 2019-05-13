#include "../include/RTI_Settings.h"
#include "../include/Controller_Settings.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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

    fprintf(fp, "%s %i\n", "DISPLAY_ON:", settings->turnedOn);
    fprintf(fp, "%s %i\n", "BRIGHTNESS:", settings->brightness);

    fclose(fp);
}


rti_settings *loadSettings(const char *path) {
    FILE *fp = fopen(path, "r");
    rti_settings *settings = newRTISettings();

    char identifier[255];
    int value;

    if (fp) {
        while (fscanf(fp, "%s %i\n", &identifier, &value) != EOF) {
            if (strcmp(identifier, "DISPLAY STATUS:") == 0) {
                if (value == 0) settings->turnedOn = false;
            } else if (strcmp(identifier, "BRIGHTNESS:") == 0) {
                if (0 <= value && value <= 15) settings->brightness = value;
            }
        }

        printf("Loaded settings from disk: DISPLAY_ON: %s\tBRIGHTNESS: %i", settings->turnedOn ? "ON" : "OFF",
               settings->brightness);
        fflush(stdout);

        fclose(fp);
        return settings;
    }

    fprintf(stderr, "Settings file is invalid or doesn't exist at: %s\n", path);
    fprintf(stderr, "Created new save file at: %s", path);
    saveSettings(settings, path);

    return settings;
}