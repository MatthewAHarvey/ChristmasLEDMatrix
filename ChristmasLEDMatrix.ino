#include "FastLED.h"
#include "SerialChecker.h"
#include "MilliTimer.h"

#include <WiFi.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

// wifi stuff
const char* ssid = "**";
const char* password = "**";

MilliTimer t(1000);
SerialChecker sc;
// matrix size
uint8_t Width  = 16;
uint8_t Height = 16;
uint8_t CentreX =  (Width / 2) - 1;
uint8_t CentreY = (Height / 2) - 1;


#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    256
// NUM_LEDS = Width * Height

uint8_t pattern = 1;
uint8_t maxBrightness = 64;
int8_t delayAdjuster = 1;
CRGB leds[NUM_LEDS];

// snow settings
uint8_t meltFraction = 45;
uint8_t settleFraction = 8;
uint8_t snowFraction = 32;
uint16_t fallDelay = 200;

void setup() {
    sc.init();
    Serial.println("Connected to ChristmasLEDMatrix.ino");
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(maxBrightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,1000);
    FastLED.setDither(DISABLE_DITHER);
    // for(int i = 0; i < 256; i++){
    //   leds[i] = CHSV(0,0,255);
    // }
    // FastLED.show();
    setupWifi();
}

void loop(){
    ArduinoOTA.handle();  
    checkSerial();
    
    if(t.timedOut(true)){
        if(pattern == 1){
            updateRandomPattern();
        }
        if(pattern == 2){
            updateBlondeBrunetteRedhead();
        }
        if(pattern == 3){
            updateSnow();
        }
    } 
}

void checkSerial(){
    if(sc.check()){
        if(sc.contains("SB")){
            maxBrightness = sc.toInt8();
            FastLED.setBrightness(maxBrightness);
        }
        else if(sc.contains("SD")){
            delayAdjuster = sc.toInt8();
        }
        else if(sc.contains("SP")){
            pattern = sc.toInt8();
        }
        else if(sc.contains("SM")){
            FastLED.setMaxPowerInVoltsAndMilliamps(5,sc.toInt16());
        }
        else if(sc.contains("melt")){
            meltFraction = sc.toInt8();
        }
        else if(sc.contains("settle")){
            settleFraction = sc.toInt8();
        }
        else if(sc.contains("snow")){
            snowFraction = sc.toInt8();
        }
        else if(sc.contains("fall")){
            fallDelay = sc.toInt16();
        }
    }
    // else{
    //   uint8_t b = sc.toInt8();
    //   for(int i = 0; i < 256; i++){
    //     leds[i] = CHSV(0,0,b);
    //   }
    //   FastLED.show();
    // }
}

void updateRandomPattern(){
    for(int i = 0; i < NUM_LEDS; i++){
        // leds[i] = CRGB( random8 (), random8 () , random8 ());
        leds[i] = CHSV(random8(), 255, random8());
    }
    FastLED.show();
    t.updateTimeOut(uint16_t(random8()) << delayAdjuster);
}

void updateBlondeBrunetteRedhead(){
    for(int i = 0; i < NUM_LEDS; i++){
        // leds[i] = CRGB( random8 (), random8 () , random8 ());
        uint8_t r = random8() >> 6;
        if(r == 0){
            leds[i] = CRGB(0,143,17);
        }
        else if(r == 1){
            leds[i] = CRGB(0,255,65);
        }
        else if (r == 2){
            leds[i] = CRGB(0,59,0);
        }
        else{
            leds[i] = CRGB(13,2,8);
        }
        // leds[i] = CHSV(random8(), 255, random8());
    }
    FastLED.show();
    t.updateTimeOut(uint16_t(random8()) << delayAdjuster);
}

void updateSnow(){
    // Snow. Randomly seed the top row with different brightness whites. Have them fall. If they reach the bottom, add a fraction of their value to the bottom block's brightness. The snow should melt at a fixed rate. If the block reaches full brightness, light up the next lowest block so hte snow piles up.
    // Extras, add wind and a wall?
    // To do this, cycle through all the blocks. If top row, randomly seed with snow. If bottom row, pile up and melt. If in between, drop snow to next level down. Start from bottom to top.

    // // Settling snow
    for(int col = 0; col < 16; col++){
        if(leds[xy(col, 14)]){
            leds[xy(col, 15)] += leds[xy(col, 14)].fadeToBlackBy(settleFraction);
            leds[xy(col, 14)] = 0;
        }
        // melt
        leds[xy(col, 15)].fadeToBlackBy(meltFraction);
    }

    // Falling snow
    for(int row = 14; row > 0; row--){
        for(int col = 0; col < 16; col++){
            if(leds[xy(col,row - 1)]){
                leds[xy(col, row)] = leds[xy(col,row - 1)];
                leds[xy(col,row - 1)] = 0;
            }
        }
    }
    // new snow (top row)
    for(int col = 0; col < 16; col++){
        if(random8() <= snowFraction){
            leds[col] = CHSV(random8(), random(0, 8), random8());
        }
    }

    FastLED.show();
    t.updateTimeOut(fallDelay);

}

// updateSnow works well but only fills the bottom row. There is no wind and no snow drifts.
// What does a snow drift look like? Make it so only top layer can melt. If bottom row plus next row is higher than 255, set bottom to 255 and remainder in next row up.
// If next row up is 

// new method for update snow

void updateSnowV2(){
    // works from bottom up. This time in columns which probably makes more sense
    for(int col = 0; col < Width; col++){
        // First, settle the snow and let snow fall
        for(int row = Height - 1; row > 0; row--){
            if(leds[xy(col, row - 1)]){
                // if the square above current square has something in it, then I have to do
            }
        }
    }
}

void snakeFill(){
    for(int i = 0; i < 256; i++){
        leds[i] = 0;
    }
    FastLED.show();
    for(int i = 0; i < 256; i++){
        leds[i] = CHSV(0, 255, 64);
        FastLED.show();
        delay(250);
    }
}

void rowFill(){
    for(int i = 0; i < 256; i++){
        leds[i] = 0;
    }
    FastLED.show();
    for(int j = 0; j < 16; j++){
        for(int i = 0; i < 16; i++){
            leds[xy(i, j)] = CHSV(0, 255, 64);
            FastLED.show();
            delay(250);
        }
    }
}

// Helper function that translates from x, y into an index into the LED array
// The LED strip is wired from bottom right corner and "snakes" to the top.
// This function corrects the x,y coordinate so that i is correctly addressed.
// x,y starts from top left and
// uint16_t XY( uint8_t x, uint8_t y) {
//   uint8_t i;
//   if ( y & 0x01) { //bitwise AND
//     // Odd rows run forwards
//     i = NUM_LEDS - 1 - ((y * Width) + x);
//   } 
//   else {
//     // Even rows run backwards
//     uint8_t reverseX = (Width - 1) - x;
//     i = NUM_LEDS - 1 - ((y * Width) + reverseX);
//   }
//   return i;
// }
// 
//def xy(x, y):
        // if y % 2:
        //     # even row
        //     i = width - 1 - x + width * y
        // else:
        //     i = x + width * y
        // return i
// 
uint8_t xy(uint8_t x, uint8_t y){
    if(y & 1){
        // odd row
        return x + Width * y;
    }
    else{
        return Width - 1 - x + Width * y;
    }
}

void setupWifi(){
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    while (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("Connection Failed! Rebooting...");
        delay(5000);
        ESP.restart();
    }

    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("LEDMATRIX");

    // No authentication by default
    // ArduinoOTA.setPassword("admin");

    // Password can be set with it's md5 value as well
    // MD5(admin) = 21232f297a57a5a743894a0e4a801fc3
    // ArduinoOTA.setPasswordHash("21232f297a57a5a743894a0e4a801fc3");

    ArduinoOTA
        .onStart([]() {
            String type;
            if (ArduinoOTA.getCommand() == U_FLASH)
                type = "sketch";
            else // U_SPIFFS
                type = "filesystem";

            // NOTE: if updating SPIFFS this would be the place to unmount SPIFFS using SPIFFS.end()
            Serial.println("Start updating " + type);
        })
        .onEnd([]() {
            Serial.println("\nEnd");
        })
        .onProgress([](unsigned int progress, unsigned int total) {
            Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
        })
        .onError([](ota_error_t error) {
            Serial.printf("Error[%u]: ", error);
            if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
            else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
            else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
            else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
            else if (error == OTA_END_ERROR) Serial.println("End Failed");
        });

    ArduinoOTA.begin();

    Serial.println("Ready");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
}