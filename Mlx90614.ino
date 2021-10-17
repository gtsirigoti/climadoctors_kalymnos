#include <i2cmaster.h>


#include <Wire.h> 
#include <SparkFunMLX90614.h> 

IRTherm therm;

void setup() {
 Serial.begin(9600); 
  therm.begin(); 
  therm.setUnit(TEMP_C);  // put your setup code here, to run once:

}

String temperature; 
char runner;

void loop() {
  if (therm.read()) // On success, read() will return 1, on fail 0.
  {
    temperature = String(therm.object(), 2);
    Serial.print("Object: ");
    Serial.print(temperature); Serial.println("C");// put your main code here, to run repeatedly:
    runner++;
    delay(5);
  }
  if (runner>20)
  runner=0;
  }
