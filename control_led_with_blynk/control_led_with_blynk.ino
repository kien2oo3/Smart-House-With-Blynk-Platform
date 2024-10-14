// Khai báo các hằng số cần thiết của Template
#define BLYNK_TEMPLATE_ID "TMPL6bBp0Lwdq"
#define BLYNK_TEMPLATE_NAME "Smart House"
#define BLYNK_AUTH_TOKEN "ONgxUUEQ5b65W4O6hKocUzyhYB5Zb2GP"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include "DHT.h"

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Tầng 3"; // Khai báo tên Wifi
char pass[] = "13572468"; // Khai báo mật khẩu Wifi

BlynkTimer timer;

#define led_pin  15
#define DHTPIN 18        // Chân DATA của DHT11 kết nối với GPIO 2 của ESP32
#define DHTTYPE DHT11    // Định nghĩa loại cảm biến là DHT11

DHT dht(DHTPIN, DHTTYPE);

BLYNK_WRITE(V0)
{
  if(param.asInt()!=0){
    digitalWrite(led_pin, HIGH);
  }else{
    digitalWrite(led_pin, LOW);
  }
}

void sendSensorData()
{
  // Đọc nhiệt độ và độ ẩm
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 
  
  // Kiểm tra xem có lỗi khi đọc không
  if (isnan(h) || isnan(t)) {
    Serial.println("Lỗi đọc cảm biến DHT11!");
    return;
  }

  // Gửi dữ liệu lên Blynk (các chân ảo V5 và V6)
  Blynk.virtualWrite(V1, t);  // Gửi độ ẩm đến Virtual Pin V5
  Blynk.virtualWrite(V2, h);  // Gửi nhiệt độ đến Virtual Pin V6

  // In dữ liệu ra Serial Monitor
  Serial.print("Độ ẩm: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Nhiệt độ: ");
  Serial.print(t);
  Serial.println(" *C");
}

void setup() //Setup function - only function that is run in deep sleep mode
{
  Serial.begin(9600); //Start the serial output at 115,200 baud
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay
  dht.begin();

  delay(2000);
  timer.setInterval(1000L, sendSensorData);

}

// Hàm xử lý khi ESP32 kết nối với Blynk
BLYNK_CONNECTED() {
  Serial.println("ESP32 Connected to Blynk!");
  Blynk.syncVirtual(V0, V1, V2);  // Đồng bộ dữ liệu từ các chân ảo V0
}

void loop() // Hàm lặp
{
  Blynk.run();
  timer.run();
}