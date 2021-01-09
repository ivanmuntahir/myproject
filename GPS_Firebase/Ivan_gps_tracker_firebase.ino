/* Sending Sensor Data to Firebase Database by CircuitDigest(www.circuitdigest.com) */
#include <FirebaseESP8266.h> 
#include <ESP8266WiFi.h>                                                    
#include <Arduino.h> 
#include <FirebaseJson.h>
#include <TinyGPS++.h>
#include <SoftwareSerial.h>                                                     

#define FIREBASE_HOST "fir-34242-default-rtdb.firebaseio.com"                          // the project name address from firebase id
#define FIREBASE_AUTH "tBXRjBeNqE3SQf5QpdFX8lZ80Ied4EVfVneS3jXp"            // the secret key generated from firebase

#define WIFI_SSID "hotspot"                                             
#define WIFI_PASSWORD "modulku33"                                   

FirebaseData fbdo;

static const int RXPin = 4, TXPin = 5;
static const uint32_t GPSBaud = 9600;

TinyGPSPlus gps;

SoftwareSerial ss(RXPin, TXPin);
String latitude,longitude;

                                                    

void setup() {
  Serial.begin(115200);
  ss.begin(GPSBaud);
  delay(1000);                
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                            
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                              
}

void loop() { 
  while (ss.available() > 0)
    if (gps.encode(ss.read())){
float la= (gps.location.lat());
float lo= (gps.location.lng());
latitude = String(la,6);
longitude = String (lo,6);
  Serial.print(F("Location: ")); 
  if (gps.location.isValid())
  {
    Serial.print(latitude);
    Serial.print ("   ");
    Serial.println(longitude);
    
  Firebase.setString(fbdo, "/Location/Latitude", latitude);
  Firebase.setString(fbdo, "/Location/Longitude", longitude);
  delay(1000);

}
}
}
