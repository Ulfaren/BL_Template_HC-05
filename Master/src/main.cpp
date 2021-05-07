#include <Arduino.h>
#include "Bluetooth_HC_05.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Bluetooh.begin(38400);

}

void loop() {
  //set master device with pin '12345'
  bool initialized = Bluetooth_Initialize('12345');
  if(initialized)
  {
    Serial.write('Bluetooth moudle ready!\r\n');

    //wait untill connection is estiblished
    while(!checkConnection())
    {
      char found_devices = scan();
      Serial.write(found_devices);
      delay(5000);
    }

    //insert your code here!!!!!

  }
  else
  {
    Serial.write('Retry in 5s ...');
    delay(5000);
  }
}