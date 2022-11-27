//This is group 19302's project arduino code
//Done by/ Ahmed Hassan, Mohamed Emad, and Omar Ramy.

#include "WiFi.h"
#include "ThingSpeak.h"
#include "DHT.h"

#define WIFI_NETWORK "19302"
#define WIFI_PASSWORD "19302_project"
#define WIFI_TIMEOUT_MS 20000

#define CHANNEL_ID 1951027
#define CHANNEL_API_KEY "4KHGJ1025KD6OMCK"

WiFiClient client;

#define CO2PIN     34
int moisture_sensor_pin = 35; 
int soil_moisture;  

#define DHTPIN 5   
#define DHTTYPE DHT22
  
DHT dht(DHTPIN, DHTTYPE);

//WI-FI Connection Code Start
void connectToWifi(){
  Serial.print("connecting to WIFI...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD);

  unsigned long startAttemptTime = millis();

  while(WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < WIFI_TIMEOUT_MS){
    Serial.println("Trying to connect to WiFi...");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){
    Serial.println("Failed to connect to this Wi-Fi Network.");
    // some action
  }else{
    Serial.print("Connected! IP:");
    Serial.println(WiFi.localIP());
  }
}
//WI-FI Connection Code End

void setup() 
{
  Serial.begin(9600);
  connectToWifi();
  ThingSpeak.begin(client);
  dht.begin();
  pinMode(CO2PIN,INPUT);
}
  
void loop() 
{
  
//CO2 Concentration Code Start
  int co2_now[10];
  int co2_raw = 0;
  int co2_ppm = 0;
  int x = 0;


  for (int i = 0; i<10; i++)
  {                   
    co2_now[i]=analogRead(34);
    delay(50);
  }

  for (int i = 0; i<10; i++)
  {                     
    x += co2_now[i];  
  }
  
  co2_raw = x/10;
  co2_ppm = co2_raw - 1500;   //CO2 calibration

  Serial.print("CO2 Concentration: ");
  Serial.print(co2_ppm);
  Serial.println(" PPM");
//CO2 Concentration Code End

//Temperature Code Start
  float temp = dht.readTemperature() + 0;     //Temperature calibration

  Serial.print("Temperature: ");
  Serial.print(temp);
  Serial.println(F(" °C"));
//Temperature Code End

//Soil Moisture Code Start
  soil_moisture = ((analogRead(moisture_sensor_pin)/-1) + 4095)/100;     //Soil Moisture calibration 
  Serial.print("Soil Moisture Value : ");
  Serial.print(soil_moisture);
  Serial.println(" %");
//Soil Moisture Code End

  Serial.println("------------------------------------------------------------------------------");

//pushing everything to ThingSpeak
  ThingSpeak.setField(1, co2_ppm);
  ThingSpeak.setField(2, temp);
  ThingSpeak.setField(3, soil_moisture);

  ThingSpeak.writeFields(CHANNEL_ID, CHANNEL_API_KEY);
  
  delay(15000);             
}
