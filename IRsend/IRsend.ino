/* IRremoteESP8266: IRsendDemo - demonstrates sending IR codes with IRsend.
 *
 * Version 1.0 April, 2017
 * Based on Ken Shirriff's IrsendDemo Version 0.1 July, 2009,
 * Copyright 2009 Ken Shirriff, http://arcfn.com
 *
 * An IR LED circuit *MUST* be connected to the ESP8266 on a pin
 * as specified by IR_LED below.
 *
 * TL;DR: The IR LED needs to be driven by a transistor for a good result.
 *
 * Suggested circuit:
 *     https://github.com/markszabo/IRremoteESP8266/wiki#ir-sending
 *
 * Common mistakes & tips:
 *   * Don't just connect the IR LED directly to the pin, it won't
 *     have enough current to drive the IR LED effectively.
 *   * Make sure you have the IR LED polarity correct.
 *     See: https://learn.sparkfun.com/tutorials/polarity/diode-and-led-polarity
 *   * Typical digital camera/phones can be used to see if the IR LED is flashed.
 *     Replace the IR LED with a normal LED if you don't have a digital camera
 *     when debugging.
 *   * Avoid using the following pins unless you really know what you are doing:
 *     * Pin 0/D3: Can interfere with the boot/program mode & support circuits.
 *     * Pin 1/TX/TXD0: Any serial transmissions from the ESP8266 will interfere.
 *     * Pin 3/RX/RXD0: Any serial transmissions to the ESP8266 will interfere.
 *   * ESP-01 modules are tricky. We suggest you use a module with more GPIOs
 *     for your first time. e.g. ESP-12 etc.
 */

#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

//  Dis works with ESP32-C3 Mini with IRRemoteESP8266/pull/2040
//  Problem is the RGB LED freaks out like diddy.  that mite not be so bad but it sucks down like nearly 40ma lol fml
//  Using the IR shield i'd have to cut the send trace and jumper it, blech.  it's just a transistor so might as well cobble up my own thing if I can find my IR LEDs...

//#define IR_LED D3
#define IR_LED 7  

IRsend irsend(IR_LED);  // Set the GPIO to be used to sending the message.

void setup() {
  Serial.begin(115200);
  irsend.begin();
}

uint32_t koda_address = 0x7E7E;  //  NEC protocol

uint32_t koda_power_on  = 0x5;
uint32_t koda_power_off = 0x4;

uint32_t koda_night_mode        = 0x30;  //  set to 10%
uint32_t koda_bright_10         = 0x1D;  //  set to 10%
uint32_t koda_bright_100        = 0x1C;  //  set to 100%
uint32_t koda_bright_less       = 0x1B;
uint32_t koda_bright_more       = 0x1A;

uint32_t koda_timer_dim_disable = 0xD;
uint32_t koda_timer_dim_30s     = 0xC;
uint32_t koda_timer_dim_10min   = 0xE;
uint32_t koda_timer_dim_30min   = 0xF;

uint32_t koda_timer_off_disable = 0x11;
uint32_t koda_timer_off_30s     = 0x10;
uint32_t koda_timer_off_10min   = 0x12;
uint32_t koda_timer_off_30min   = 0x13;

uint32_t koda_ambient_sensor_off        = 0x15;
uint32_t koda_ambient_sensor_overcast   = 0x14;
uint32_t koda_ambient_sensor_dusk       = 0x16;
uint32_t koda_ambient_sensor_night      = 0x17;  //  light turns on only when "dark" and motion is detected

uint32_t koda_motion_distance_1 = 0x9;  //  "very near"
uint32_t koda_motion_distance_2 = 0x8;  //  "near"
uint32_t koda_motion_distance_3 = 0xA;  //  "mid-range"
uint32_t koda_motion_distance_4 = 0xB;  //  "far"

void loop() {
  uint32_t enc;

  enc = irsend.encodeNEC(koda_address, koda_power_on);
  Serial.println(enc, HEX);
  irsend.sendNEC(enc);
  delay(2000);

  enc = irsend.encodeNEC(koda_address, koda_power_off);
  Serial.println(enc, HEX);
  irsend.sendNEC(enc);
  delay(2000);
  
}
