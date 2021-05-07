#include <SoftwareSerial.h>

#define CLEAR 'AT+RMADD\r\n';
#define SET_MASTER 'AT+ROLE=1\r\n';
#define REST 'AT+REST\r\n';
#define SET_MODE 'AT+CMODE=1\r\n';
#define SET_INQUIRY 'AT+INQM=0,5,5\r\n';
#define SET_PIN(pin) 'AT+PSWD='+pin+'\r\n';
#define SET_NAME(name) 'AT+NAME='+name+'\r\n';
#define START 'AT+INIT\r\n';
#define SCAN 'AT+INQ';
#define CHECK_STATE 'AT+STATE?\r\n';
#define OK 'OK\r\n';

static SoftwareSerial Bluetooh(0,1);

static const bool Bluetooth_Initialize(char pin){
    char msg = ' ';
    char OK_resp = OK;

    //clear all connected devices
    msg = CLEAR;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not clear connected devices!\r\n');
        return false;
    }

    //Set device to master mode
    msg = SET_MASTER;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not set device to master!\r\n');
        return false;
    }

    //rest the moudle
    msg = REST;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not reset the device!\r\n');
        return false;
    }

    //allow connection from any device
    msg = SET_MODE;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not change mode!\r\n');
        return false;
    }

    //set the inquiry mode
    msg = SET_INQUIRY;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not set standard inquiry mode!\r\n');
        return false;
    }

    //set the pin
    msg = SET_PIN(pin);
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not set the pin!\r\n');
        return false;
    }

    //set name
    msg = SET_NAME('MASTER');
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not set the name!\r\n');
        return false;
    }

    //set name
    msg = START;
    Serial.write(msg);
    while(!Serial.available()){}
    msg=Serial.read();
    if(msg!=OK_resp)
    {
        Serial.write('Could not start the bluetooth moudle!\r\n');
        return false;
    }

    return true;
};

static const char scan()
{
    char msg = SCAN;
    Serial.write(msg);
    while(!Serial.available()){};
    msg = Serial.read();
    return msg;
}

static const bool checkConnection()
{
    char msg = CHECK_STATE;
    char resp = '+STATE:CONNECTED\r\nOK\r\n';
    Serial.write(msg);
    while(!Serial.available()){}
    msg = Serial.read();
    if(msg==resp)
    {
        return true;
    }
    else
    {
        return false;
    }
}

static const char Read()
{
    if(Bluetooh.available())
    {
        char msg = Bluetooh.read();
        return msg;
    }
    else
    {
        char msg = 'ERROR';
        return msg;
    }
}

static const void Write(char msg)
{
    while(!Bluetooh.availableForWrite()){}
    Bluetooh.write(msg);
    return;
}