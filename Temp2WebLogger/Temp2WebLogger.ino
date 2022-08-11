#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>
Adafruit_BMP280 bmp; // I2C

int TempArray[144]; //this will store the temps 


void setup() {
  Serial.begin(9600); //standard serial code
  bmp.begin(0x76); // sets the address of the sensor on the I2C Bus
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
}

void loop() {
 TenMinTimer();
//PrintSerial();
}

void TenMinTimer() {
unsigned long  current_millis = millis();
static unsigned long prev_millis;      
    if (current_millis - prev_millis > 600000) {
        AddDataToArray();
        prev_millis = current_millis;
    }
    PrintSerial();  
}

void PrintSerial() {
        for (int i = (0); i < 144; i++)
   {         
    Serial.print("Array Location = ");      
    Serial.print(i) ;      
    Serial.print("  Data = ");
    Serial.println(TempArray[i]);
    }     
  
}

void AddDataToArray() {
    float floatTemp = (bmp.readTemperature());
    int inttemp = (int)floatTemp;
      pushBack(TempArray, inttemp, 144); 
}



// this code pushes the data back in the array 
// so the newest value is always at the start.

void pushBack(int arr [], int str, int len) 
{
  int tempArr [len];

  for (int i = 0; i <= len; ++i)
  {
    tempArr[i] = arr[i];
  }

  arr[0] = str;

  for (int i = 1; i <= len; i++)
  {
    arr[i] = tempArr[i - 1];
  }
}
