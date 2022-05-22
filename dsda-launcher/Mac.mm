#include "Mac.h"
#import <Cocoa/Cocoa.h>

bool macDarkThemeAvailable()
{
    if (__builtin_available(macOS 10.14, *))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool macIsInDarkTheme()
{
    if (__builtin_available(macOS 10.14, *))
    {
        auto appearance = [NSApp.effectiveAppearance bestMatchFromAppearancesWithNames:
                @[ NSAppearanceNameAqua, NSAppearanceNameDarkAqua ]];
        return [appearance isEqualToString:NSAppearanceNameDarkAqua];
    }
    return false;
}

void macSetToDarkTheme()
{
   if (__builtin_available(macOS 10.14, *))
   {
        [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameDarkAqua]];
   }
}

void macSetToLightTheme()
{
    if (__builtin_available(macOS 10.14, *))
    {
        [NSApp setAppearance:[NSAppearance appearanceNamed:NSAppearanceNameAqua]];
    }
}

void macSetToAutoTheme()
{
    if (__builtin_available(macOS 10.14, *))
    {
        [NSApp setAppearance:nil];
    }
}
