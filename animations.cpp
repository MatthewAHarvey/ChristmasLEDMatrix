#include "animations.h"

DEFINE_GRADIENT_PALETTE( fireMap ) {
      0,     0,  0,  0,   //black
    128,   128,  0,  0,   //red
    224,   128,128,  0,   //bright yellow
    255,   255,255,200 }; //near full white

uint8_t xy(uint8_t x, uint8_t y){
    const uint8_t Width = 16;
    if(y & 1){
        // odd row
        return x + Width * y;
    }
    else{
        return Width - 1 - x + Width * y;
    }
}

Fire::Fire(CRGB *leds){
    this->leds = leds;
}

void Fire::init(){
    for(int i = 0; i < NumLeds; i++){
        leds[i] = 0;
    }
}

void Fire::update(){
    //if(f.timedOut(true)){ // make fire randomly get hotter or colder at random rate
        fireDecay = random8(32, 128);
      //  f.updateTimeOut(random16(150, 750));
    // }
    // Seed bottom row
    // for(uint8_t col = 0; col < Width; col++){
    //     fireColour[xy(col, 15)] = 255;
    //     leds[xy(col, 15)] = ColorFromPalette(firePalette, 255);
    // }
    // // Spread fire
    // for(uint8_t col = 0; col < Width; col++){
    //     for(uint8_t row = 0; row < Height; row++){
    //         uint8_t randTurb = random8(3); //turbulence
    //         uint8_t randDecay = random8(fireDecay);
    //         uint8_t tmpColour = 0;
    //         if(row == Height - 1){
    //              tmpColour = random8(192, 255);
    //         }
    //         else{
    //             tmpColour = fireColour[xy(col, row + 1)] - randDecay;
    //             if(tmpColour > fireColour[xy(col, row + 1)]){
    //                 // We have rolled over so just set to zero
    //                 tmpColour = 0;
    //             }
    //         }
    //         // allow left and right turbulence but wrap it back to other side of fire if it overflows the matrix
    //         uint8_t turbCol = col - 1 + randTurb;
    //         if(turbCol > (Width - 1)){ turbCol = 0; }
    //         else if(turbCol > 250) { turbCol = Width - 1; }
    //         fireColour[xy(turbCol, row)] = tmpColour;
    //         leds[xy(turbCol , row)] = ColorFromPalette(firePalette, tmpColour);
    //     }
    // }
    //FastLED.show();
    // t.updateTimeOut(fireDelay);
}