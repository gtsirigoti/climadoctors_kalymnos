/***********************************
Arduino Contactless thermometer 
MLX90614 I2C connection
OLED 4-wire SPI connection 
Dated: 7-6-2019
Code by: Aswint Raj
**********************************/

#include <Wire.h> 
#include <SparkFunMLX90614.h> 

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
int laser_pin=8;
int button_pin=4;
int val = 0;
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

IRTherm therm;

void setup() 
{
  pinMode(laser_pin, OUTPUT);
  pinMode(button_pin, INPUT);
  Serial.begin(9600); 
  therm.begin(); 
  therm.setUnit(TEMP_C); 

   display.begin(SSD1306_SWITCHCAPVCC);
   display.clearDisplay();
   display.setRotation(2);
  
}

String temperature; 
char runner;

void loop() 
{
  val = digitalRead(button_pin);  // read input value
  if (val == LOW) {         // check if the input is HIGH (button released)
    digitalWrite(laser_pin, LOW);  // turn LED OFF
  } else {
    digitalWrite(laser_pin, HIGH);  // turn LED ON
  }
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    temperature = String(therm.object(), 2);
    Serial.print("Object: ");
    Serial.print(temperature); Serial.println("C");
    display.clearDisplay();
    runner++;
    delay(5);
  }

  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(display.width()/4,display.height()/12);
  
  if (therm.object()>=100)
  display.setCursor(display.width()/4,display.height()/12);
  
  display.println(temperature);

  display.drawLine(display.width()/runner,display.height() - display.height()/2.5, display.width()/runner+1, display.height() - display.height()/2.5, WHITE);

  display.setCursor(0,display.height()-display.height()/4);
  display.setTextSize(1);
  display.println("   Arduino Thermlgun");
  display.setCursor(display.width()- display.width()/4,display.height()/12);
  display.println("deg C");
  display.display();

  if (runner>20)
  runner=0;
}
