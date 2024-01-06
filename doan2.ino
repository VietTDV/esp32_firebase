#include <Arduino.h>
#if defined(PICO_RP2040)
#include <WiFi.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#endif
#include <FirebaseESP8266.h>

#include <DHT.h> // Thư viện DHT

#define WIFI_SSID "TramNgok"
#define WIFI_PASSWORD "123567890"
#define API_KEY "AIzaSyDRmeNNzTzz4sEgMo3dFh9M6sn2DQFshEA"
#define DATABASE_URL "https://nha-iot-6d6f7-default-rtdb.firebaseio.com/"

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

#define DHTPIN 2   // Định nghĩa chân kết nối cảm biến DHT
#define DHTTYPE DHT11 // Loại cảm biến, có thể thay bằng DHT22
#define Loa 4

DHT dht(DHTPIN, DHTTYPE);

int Den_Khach = 19;
int Quat_Khach = 18;

int Den_Ngu = 5;
int Quat_Ngu  = 17;

int Den_Hoc = 16;




//##############################################################################
void setup(){
  Serial.begin(115200);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.println("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.println(".");
    
  }
  Serial.println("");
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Firebase signed up successfully.");
  }
  else{
    Serial.printf("Firebase sign-up error: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true); 

  dht.begin(); // Khởi động cảm biến DHT
    config.api_key = API_KEY;
  config.database_url = DATABASE_URL;

  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Firebase signed up successfully.");
  }
  else{
    Serial.printf("Firebase sign-up error: %s\n", config.signer.signupError.message.c_str());
  }

  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true); 

  dht.begin(); // Khởi động cảm biến DHT

    pinMode(Den_Khach, OUTPUT);
    pinMode(Quat_Khach, OUTPUT);
    pinMode(Den_Ngu, OUTPUT);
    pinMode(Quat_Ngu, OUTPUT);
    pinMode(Den_Hoc, OUTPUT);

    pinMode(Loa, OUTPUT);
}


void loop(){
  //###################################################################
  if(Firebase.getString(fbdo,"/DenKhach"))
  {
    if(fbdo.dataType() == "string"){
      String DenKhach = fbdo.stringData();
      if(DenKhach == "1")
      {
        Serial.println("Da Bat Den Khach");
        digitalWrite(Den_Khach, HIGH);
      }
      else if(DenKhach == "0"){
        Serial.println("Da Tat Den Khach");
        digitalWrite(Den_Khach, LOW);
      }
    }
  }

  //###################################################################
  if(Firebase.getInt(fbdo,"/QuatKhach"))
  {
    if(fbdo.dataType() == "string"){
      String QuatKhach = fbdo.stringData();
      if(QuatKhach == "1")
      {
        Serial.println("Da Bat Quat Khach");
        digitalWrite(Quat_Khach, HIGH);
      }
      else if(QuatKhach == "0"){
        Serial.println("Da Tat Quat Khach");
        digitalWrite(Quat_Khach, LOW);
      }
    }
  }

  //###################################################################
  if(Firebase.getInt(fbdo,"/DenNgu"))
  {
    if(fbdo.dataType() == "string"){
      String DenNgu = fbdo.stringData();
      if(DenNgu == "1")
      {
        Serial.println("Da Bat Den Ngu");
        digitalWrite(Den_Ngu, HIGH);
      }
      else if(DenNgu == "0"){
        Serial.println("Da Tat Den Ngu");
        digitalWrite(Den_Ngu, LOW);
      }
    }
  }
  
  //###################################################################
  if(Firebase.getInt(fbdo,"/QuatNgu"))
  {
    if(fbdo.dataType() == "string"){
      String QuatNgu = fbdo.stringData();
      if(QuatNgu == "1")
      {
        Serial.println("Da Bat Quat Ngu");
        digitalWrite(Quat_Ngu, HIGH);
      }
      else if(QuatNgu == "0"){
        Serial.println("Da Tat Quat Ngu");
        digitalWrite(Quat_Ngu, LOW);
      }
    }
  }

  //###################################################################
  if(Firebase.getInt(fbdo,"/DenHoc"))
  {
    if(fbdo.dataType() == "string"){
      String DenHoc = fbdo.stringData();
      if(DenHoc == "1")
      {
        Serial.println("Da Bat Den Hoc");
        digitalWrite(Den_Hoc, HIGH);
      }
      else if(DenHoc == "0"){
        Serial.println("Da Tat Den Hoc");
        digitalWrite(Den_Hoc, LOW);
      }
    }
  }

  //####################################################################
  // Đo và gửi dữ liệu từ cảm biến DHT lên Firebase
    float humidity = dht.readHumidity();
    float temperature = dht.readTemperature();
    if (!isnan(humidity) && !isnan(temperature)) {
      // Gửi dữ liệu lên Firebase
      Firebase.setFloat(fbdo, "/DHT/Humidity", humidity);
      Firebase.setFloat(fbdo, "/DHT/Temperature", temperature);
      Serial.print("Humidity: ");
      Serial.print(humidity);
      Serial.print("%  Temperature: ");
      Serial.print(temperature);
      Serial.println("°C");
    }

}