//#include "FS.h"
#include "SD.h"
#include "SPI.h"
//#include "RTClib.h"
//#include "DHT.h"

//#define DHTPIN 2
//#define DHTTYPE DHT22
//
//DHT dht(DHTPIN, DHTTYPE);
//RTC_DS1307 rtc;

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void setup(){
  Serial.begin(9600);
//  dht.begin();
  
  if(!SD.begin()){
      Serial.println("Card Mount Failed");
      return;
      }

//  if (! rtc.begin()) {
//    Serial.println("Couldn't find RTC");
//    while (1);
//    }
//
//  if (!rtc.isrunning()) {
//    Serial.println("RTC lost power, lets set the time!");
//    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
//  }
  
  writeFile(SD, "/datalog_ESP32.txt", "Time, Humidity, Temperature \r\n");
}

void loop(){

  String dataString = "";

  float h = 0.0; //dht.readHumidity();
  float t = 0.0; // dht.readTemperature();

  //DateTime now = rtc.now();

  dataString += "Hoje";
  dataString += ",";
  dataString += String(h);
  dataString += ",";
  dataString += String(t);
  dataString += "\r\n";

  Serial.println(dataString);
  appendFile(SD, "/datalog_ESP32.txt", dataString.c_str());
    
  delay(2000);
}
