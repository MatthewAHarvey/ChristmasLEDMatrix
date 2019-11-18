#include "FastLED.h"

#include "SerialChecker.h"
#include "MilliTimer.h"
#include "SEHandler.h"
#include "animations.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <ESPmDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
// #include <Wire.h>
// #include <hd44780.h>                       // main hd44780 header
// #include <hd44780ioClass/hd44780_I2Cexp.h> // i2c expander i/o class header

// Smart Encoders
HardwareSerial espSerial(2); // Needed for ESP32.
SEHandler encoders(espSerial);
// SEHandler encoders(Serial1); // For Arduino Mega's Serial1
event_t event;

// wifi stuff
const char* ssid = "manchasllama";
const char* ssid2 = "LCF_2.4GHz";
const char* password = "sneakapeek";
WiFiMulti wifiMulti;
WiFiServer server(80);

MilliTimer t(1000);
MilliTimer f(1000);
SerialChecker sc;
// matrix size
const uint8_t Width  = 16;
const uint8_t Height = 16;
const uint8_t CentreX =  (Width / 2) - 1;
const uint8_t CentreY = (Height / 2) - 1;


#define LED_PIN     5
#define COLOR_ORDER GRB
#define CHIPSET     WS2811
#define NUM_LEDS    256
// NUM_LEDS = Width * Height

uint8_t pattern = 4;
uint8_t maxBrightness = 64;
int8_t delayAdjuster = 1;
CRGB leds[NUM_LEDS];
Fire fireAnimation(leds);
// CRGB newFrame[NUM_LEDS];
MilliTimer smoothT(100);
// MilliTimer newFrameT(100);
// snow settings
uint8_t meltFraction = 45;
uint8_t settleFraction = 8;
uint8_t snowFraction = 32;
uint16_t fallDelay = 200;
// uint8_t fireDecay = 96;
// uint8_t fireDelay = 60;//66;



// // DEFINE_GRADIENT_PALETTE( fireMap ) {
// //       0,     0,  0,  0,   //black
// //     128,   255,  0,  0,   //red
// //     224,   255,255,  0,   //bright yellow
// //     255,   255,255,255 }; //full white
// // CRGBPalette16 firePalette = fireMap;
// DEFINE_GRADIENT_PALETTE( fireMap ) {
//       0,     0,  0,  0,   //black
//     128,   64,  0,  0,   //red
//     224,   128,128,  0,   //bright yellow
//     255,   255,255,200 }; //full white
// CRGBPalette256 firePalette = fireMap; 
// // uint8_t heatindex = (something from 0-255);
// // leds[i] = ColorFromPalette( myPal, heatindex); // normal palette access
// uint8_t fireColour[Width * Height] = {0};

void setup() {
    if(encoders.init()){
        Serial.println("Encoders init OK");
    }

    sc.init();
    Serial.println("Connected to ChristmasLEDMatrix.ino");
    FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    // FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
    FastLED.setBrightness(maxBrightness);
    FastLED.setMaxPowerInVoltsAndMilliamps(5,2000);
    FastLED.setDither(DISABLE_DITHER);

    // for(int i = 0; i < 256; i++){
    //   leds[i] = CHSV(0,0,255);
    // }
    // FastLEDshowESP32();
    setupWifi();
    fireAnimation.init();
    // initDisplay();
    // initButtons();
}

uint16_t elapsed = 0;
void loop(){
    //espSerial.println("test");
    ArduinoOTA.handle();  
    checkSerial();
    checkWifi();

    // if(t.timedOut(true)){
    //     if(pattern == 1){
    //         updateRandomPattern();
    //     }
    //     if(pattern == 2){
    //         updateBlondeBrunetteRedhead();
    //     }
    //     if(pattern == 3){
    //         updateSnow();
    //     }
    //     if(pattern == 4){
    //         updateFire();
    //     }
    //     if(pattern == 5){
    //         firePaletteTest();
    //     }
    // } 
    fireAnimation.update();
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
        // else if(sc.contains("fire")){
        //     fireDecay = sc.toInt8();
        // }
        // else if(sc.contains("delay")){
        //     fireDelay = sc.toInt8();
        // }
    }
    // else{
    //   uint8_t b = sc.toInt8();
    //   for(int i = 0; i < 256; i++){
    //     leds[i] = CHSV(0,0,b);
    //   }
    //   FastLEDshowESP32();
    // }
}

// void initDisplay(){
//     lcd.begin(LCDcolumns, LCDrows);
//     lcd.noLineWrap();
//     lcd.setCursor(0, 1);
//     lcd.print("Adam's Light Box");
// }

// void initButtons(){
//     pinMode(redButtonPin, INPUT_PULLUP);
//     pinMode(yellowButtonPin, INPUT_PULLUP);
//     pinMode(greenButtonPin, INPUT_PULLUP);
//     pinMode(blueButtonPin, INPUT_PULLUP);
//     pinMode(whiteButtonPin, INPUT_PULLUP);
//     pinMode(blackButtonPin, INPUT_PULLUP);
//     pinMode(bigButtonPin, INPUT_PULLUP);
// }

// void updateRandomPattern(){
//     smoothT.reset();
//     for(int i = 0; i < NUM_LEDS; i++){
//         // leds[i] = CRGB( random8 (), random8 () , random8 ());
//         leds[i] = CHSV(random8(), 255, random8());
//     }
//     FastLED.show();
//     t.updateTimeOut(uint16_t(random8()) << delayAdjuster);
//     elapsed = smoothT.elapsed();
// }


// void updateSmoothRandomPattern(){
//     // same as updateRandomPattern but with smooth transitions between pattern frames updated depending on time between frames and the update rate.
//     // if 
//     t.updateTimeOut(0); // just make this run all the time.
//     if(smoothT.timedOut(true)){
//         // 
//     }
// }

// void updateBlondeBrunetteRedhead(){
//     for(int i = 0; i < NUM_LEDS; i++){
//         // leds[i] = CRGB( random8 (), random8 () , random8 ());
//         uint8_t r = random8() >> 6;
//         if(r == 0){
//             leds[i] = CRGB(0,143,17);
//         }
//         else if(r == 1){
//             leds[i] = CRGB(0,255,65);
//         }
//         else if (r == 2){
//             leds[i] = CRGB(0,59,0);
//         }
//         else{
//             leds[i] = CRGB(13,2,8);
//         }
//         // leds[i] = CHSV(random8(), 255, random8());
//     }
//     FastLED.show();
//     t.updateTimeOut(uint16_t(random8()) << delayAdjuster);
// }

// leds[i] = ColorFromPalette( myPal, heatindex); // normal palette access
// uint8_t fireColour[Width * Height] = 0;
// class Fire{
//     // For a 16 x 16 matrix that is n
// public:
//     Fire();
//     //Fire(uint8_t Height, uint8_t Width);
//     //~Fire();
//     init(); // just blanks the screen
//     update(); // nex

// private:
//     uint8_t Height = 16;
//     uint8_t Width = 16;
//     uint8_t fireDecay = 96;
//     uint8_t fireDelay = 60;
//     DEFINE_GRADIENT_PALETTE( fireMap ) {
//           0,     0,  0,  0,   //black
//         128,   128,  0,  0,   //red
//         224,   128,128,  0,   //bright yellow
//         255,   255,255,200 }; //near full white
//     CRGBPalette256 firePalette = fireMap; 
//     uint8_t fireColour[Width * Height] = {0};
// };
// void updateFire(){
//     // takes 8ms to execute. Max update rate is therefore 125 fps if nothing else is happening on the esp32.
//     smoothT.reset();
//     if(f.timedOut(true)){ // make fire randomly get hotter or colder at random rate
//         fireDecay = random8(32, 128);
//         f.updateTimeOut(random16(150, 750));
//     }
//     // Seed bottom row
//     for(uint8_t col = 0; col < Width; col++){
//         fireColour[xy(col, 15)] = 255;
//         leds[xy(col, 15)] = ColorFromPalette(firePalette, 255);
//     }
//     // Spread fire
//     for(uint8_t col = 0; col < Width; col++){
//         for(uint8_t row = 0; row < Height; row++){
//             uint8_t randTurb = random8(3); //turbulence
//             uint8_t randDecay = random8(fireDecay);
//             uint8_t tmpColour = 0;
//             if(row == Height - 1){
//                  tmpColour = random8(192, 255);
//             }
//             else{
//                 tmpColour = fireColour[xy(col, row + 1)] - randDecay;
//                 if(tmpColour > fireColour[xy(col, row + 1)]){
//                     // We have rolled over so just set to zero
//                     tmpColour = 0;
//                 }
//             }
//             // allow left and right turbulence but wrap it back to other side of fire if it overflows the matrix
//             uint8_t turbCol = col - 1 + randTurb;
//             if(turbCol > (Width - 1)){ turbCol = 0; }
//             else if(turbCol > 250) { turbCol = Width - 1; }
//             fireColour[xy(turbCol, row)] = tmpColour;
//             leds[xy(turbCol , row)] = ColorFromPalette(firePalette, tmpColour);
//         }
//     }
//     FastLED.show();
//     t.updateTimeOut(fireDelay);
//     elapsed = smoothT.elapsed();
// }

// void firePaletteTest(){
//     smoothT.reset();
//     for(int row = 0; row < 16; row++){
//         // for(int i = 0; i < 256; i++){
//         //     leds[i] = 0;
//         // }
//         for(int col = 0; col < 1; col++){
//             leds[xy(col, row)] = ColorFromPalette(firePalette, xy(col, row));
//         }
//         // FastLEDshowESP32();
//         // delay(100);
//         // t.updateTimeOut(500);
//     }
//     FastLED.show();
//     elapsed = smoothT.elapsed();
// }

// void updateSnow(){
//     // Snow. Randomly seed the top row with different brightness whites. Have them fall. If they reach the bottom, add a fraction of their value to the bottom block's brightness. The snow should melt at a fixed rate. If the block reaches full brightness, light up the next lowest block so hte snow piles up.
//     // Extras, add wind and a wall?
//     // To do this, cycle through all the blocks. If top row, randomly seed with snow. If bottom row, pile up and melt. If in between, drop snow to next level down. Start from bottom to top.
//     smoothT.reset();
//     // // Settling snow
//     for(int col = 0; col < 16; col++){
//         if(leds[xy(col, 14)]){
//             leds[xy(col, 15)] += leds[xy(col, 14)].fadeToBlackBy(settleFraction);
//             leds[xy(col, 14)] = 0;
//         }
//         // melt
//         leds[xy(col, 15)].fadeToBlackBy(meltFraction);
//     }

//     // Falling snow
//     for(int row = 14; row > 0; row--){
//         for(int col = 0; col < 16; col++){
//             if(leds[xy(col,row - 1)]){
//                 leds[xy(col, row)] = leds[xy(col,row - 1)];
//                 leds[xy(col,row - 1)] = 0;
//             }
//         }
//     }
//     // new snow (top row)
//     for(int col = 0; col < 16; col++){
//         if(random8() <= snowFraction){
//             leds[col] = CHSV(random8(), random(0, 8), random8());
//         }
//     }

//     FastLED.show();
//     t.updateTimeOut(fallDelay);
//     elapsed = smoothT.elapsed();
// }

// // updateSnow works well but only fills the bottom row. There is no wind and no snow drifts.
// // What does a snow drift look like? Make it so only top layer can melt. If bottom row plus next row is higher than 255, set bottom to 255 and remainder in next row up.
// // If next row up is 

// // new method for update snow

// void updateSnowV2(){
//     // works from bottom up. This time in columns which probably makes more sense
//     for(int col = 0; col < Width; col++){
//         // First, settle the snow and let snow fall
//         for(int row = Height - 1; row > 0; row--){
//             if(leds[xy(col, row - 1)]){
//                 // if the square above current square has something in it, then I have either let it settle if I'm empty, or let it pile up a bit
//                 CRGB tmp = leds[xy(col, row - 1)] - leds[xy(col, row)];
//                 leds[xy(col, row)] += leds[xy(col, row - 1)];
//                 if(leds[xy(col, row)] == CHSV(0, 255, 255)){
//                     leds[xy(col, row - 1)] = tmp.fadeToBlackBy(settleFraction);
//                 }
//                 else{
//                     leds[xy(col, row - 1)] = 0;
//                 }
//             }
//         }
//         // Now melt top layer of settled snow
//         for(int row = Height - 1; row > 0; row--){
//             if(!leds[xy(col, row - 1)]){
//                 leds[xy(col, row)].fadeToBlackBy(meltFraction);
//                 break;
//             }
//         }
//         // Now make more snow
//         for(int col = 0; col < Width; col++){
//             if(random8() <= snowFraction){
//                 leds[col] = CHSV(random8(), random(0, 8), random8());
//             }
//         }
//     }

//     FastLED.show();
//     t.updateTimeOut(fallDelay);
// }



void setupWifi(){
    WiFi.mode(WIFI_STA);
    // WiFi.begin(ssid, password);
    WiFi.setSleep(false); // if you don't add this line, ping will go from ~14ms to 170ms and mdns won't work
    wifiMulti.addAP(ssid, password);
    wifiMulti.addAP(ssid2, password);
    WiFi.setHostname("LEDMATRIX");
    Serial.println("Connecting Wifi...");
    while (wifiMulti.run() != WL_CONNECTED) {
        Serial.println("Connection Failed!");// Rebooting...");
        //delay(5000);
        //ESP.restart();
    }


    // Port defaults to 3232
    // ArduinoOTA.setPort(3232);

    // Hostname defaults to esp3232-[MAC]
    ArduinoOTA.setHostname("LEDMATRIX");
    if (!MDNS.begin("LEDMATRIX")) {
        Serial.println("Error setting up MDNS responder!");
        while(1){
            delay(1000);
        }
    }
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

    server.begin();
}

void checkWifi(){

    if(wifiMulti.run() != WL_CONNECTED) {
        Serial.println("WiFi not connected!");
        // delay(1000);
    }
    WiFiClient client = server.available();   // listen for incoming clients

    if (client) {                             // if you get a client,
        Serial.println("New Client.");           // print a message out the serial port
        String currentLine = "";                // make a String to hold incoming data from the client
        while (client.connected()) {            // loop while the client's connected
            if (client.available()) {             // if there's bytes to read from the client,
                char c = client.read();             // read a byte, then
                Serial.write(c);                    // print it out the serial monitor
                if (c == '\n') {                    // if the byte is a newline character
                    // if the current line is blank, you got two newline characters in a row.
                    // that's the end of the client HTTP request, so send a response:
                    if (currentLine.length() == 0) {
                        // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
                        // and a content-type so the client knows what's coming, then a blank line:
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();
                        // the content of the HTTP response follows the header:
                        client.print("Click <a href=\"/H\">here</a> to turn on randomPattern.<br>");
                        client.print("Click <a href=\"/L\">here</a> to turn on snowV1.<br>");
                        client.print("Click <a href=\"/F\">here</a> to turn on Fire.<br>");
                        client.print("Click <a href=\"/T\">here</a> to turn on Fire Palette Test.<br>");
                        client.print("loop time: ");
                        client.print(elapsed);
                        client.println(" ms");
                        // The HTTP response ends with another blank line:
                        client.println();
                        // break out of the while loop: 
                        break;
                    } 
                    else {    // if you got a newline, then clear currentLine:
                        currentLine = "";
                    }
                } 
                else if (c != '\r') {  // if you got anything else but a carriage return character,
                    currentLine += c;      // add it to the end of the currentLine
                }

                // Check to see if the client request was "GET /H" or "GET /L":
                if (currentLine.endsWith("GET /H")) {
                    //digitalWrite(5, HIGH);               // GET /H turns the LED on
                    pattern = 1;
                    Serial.println("random launched");
                }
                else if (currentLine.endsWith("GET /L")) {
                    //digitalWrite(5, LOW);                // GET /L turns the LED off
                    pattern = 3;
                    Serial.println("snow launched");
                }
                else if (currentLine.endsWith("GET /1")){
                    pattern = 1;
                }
                else if (currentLine.endsWith("GET /2")){
                    pattern = 2;
                } 
                else if (currentLine.endsWith("GET /F")){
                    pattern = 4;
                }   
                else if (currentLine.endsWith("GET /T")){
                    pattern = 5;
                }   
            }
        }
        // close the connection:
        client.stop();
        Serial.println("Client Disconnected.");
    }
}