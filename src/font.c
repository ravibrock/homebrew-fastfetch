#include "fastfetch.h"

static void parseFont(char* font, char* buffer)
{
    char name[64];
    char size[32];
    sscanf(font, "%[^,], %[^,]", name, size);
    sprintf(buffer, "%s (%spt)", name, size);
}

void ffPrintFont(FFstate* state)
{
    char plasma[256];
    ffParsePropFileHome(state, ".config/kdeglobals", "font=%[^\n]", plasma);
    
    char gtk2[256];
    ffParsePropFileHome(state, ".gtkrc-2.0", "gtk-font-name=\"%[^\"]+", gtk2);
    char gtk2Pretty[256];
    parseFont(gtk2, gtk2Pretty);

    char gtk3[256];
    ffParsePropFileHome(state, ".config/gtk-3.0/settings.ini", "gtk-font-name=%[^\n]", gtk3);
    char gtk3Pretty[256];
    parseFont(gtk3, gtk3Pretty);

    char gtk4[256];
    ffParsePropFileHome(state, ".config/gtk-4.0/settings.ini", "gtk-font-name=%[^\n]", gtk4);
    char gtk4Pretty[256];
    parseFont(gtk4, gtk4Pretty);
    
    ffPrintLogoAndKey(state, "Font");

    if(plasma[0] == '\0')
    {
        printf("Noto Sans (10pt) [Plasma], ");
    }
    else
    {
        char plasmaPretty[256];
        parseFont(plasma, plasmaPretty);
        printf("%s [Plasma], ", plasmaPretty);
    }

    ffPrintGtkPretty(gtk2Pretty, gtk3Pretty, gtk4Pretty);
    putchar('\n');
}