#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include "FastLED.h"
#include "MilliTimer.h"

// HELPER FUNCTIONS

// Helper function that translates from x, y into an index into the LED array
// The LED strip is wired from bottom right corner and "snakes" to the top.
// This function corrects the x,y coordinate so that i is correctly addressed.
uint8_t xy(uint8_t x, uint8_t y);
TProgmemRGBGradientPalettePtr fireMap;
// void snakeFill(){
//     for(int i = 0; i < 256; i++){
//         leds[i] = 0;
//     }
//     FastLED.show();
//     for(int i = 0; i < 256; i++){
//         leds[i] = CHSV(0, 255, 64);
//         FastLED.show();
//         delay(250);
//     }
// }

// void rowFill(){
//     for(int i = 0; i < 256; i++){
//         leds[i] = 0;
//     }
//     FastLED.show();
//     for(int j = 0; j < 16; j++){
//         for(int i = 0; i < 16; i++){
//             leds[xy(i, j)] = CHSV(0, 255, 64);
//             FastLED.show();
//             delay(250);
//         }
//     }
// }


class Fire{
    // For a 16 x 16 matrix.
    // Assume can run as fast as WS2812B strip which for 256 LEDs is 125 fps.
    // That is 8 ms. Therefore, we can have 8 frames between each 'step' and 
    // 64 ms is 15 fps. This will look smooth.
public:
    Fire(CRGB *leds);
    //Fire(uint8_t Height, uint8_t Width);
    //~Fire();
    void init(); // just blanks the screen
    void update(); // nex

private:
    CRGB *leds;
    static const uint8_t Height = 16;
    static const uint8_t Width = 16;
    static const uint16_t NumLeds = Height * Width;
    uint8_t fireDecay = 96;
    // uint8_t fireDelay = 64;
    uint8_t transitionEvery = 8; // frame
    uint8_t frame = 0;

    

    CRGBPalette256 firePalette = fireMap; 
    uint8_t fireColour[NumLeds] = {0};
    
    // MilliTimer frameT();
    // MilliTimer transitionT(fireDelay);
};

#endif

