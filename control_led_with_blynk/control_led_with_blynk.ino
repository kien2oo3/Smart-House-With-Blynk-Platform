// Khai báo các hằng số cần thiết của Template
#define BLYNK_TEMPLATE_ID "TMPL6bBp0Lwdq"
#define BLYNK_TEMPLATE_NAME "Smart House"
#define BLYNK_AUTH_TOKEN "ONgxUUEQ5b65W4O6hKocUzyhYB5Zb2GP"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Tầng 3"; // Khai báo tên Wifi
char pass[] = "13572468"; // Khai báo mật khẩu Wifi

BlynkTimer timer;

#define led_pin  15

BLYNK_WRITE(V0)
{
  if(param.asInt()!=0){
    digitalWrite(led_pin, HIGH);
  }else{
    digitalWrite(led_pin, LOW);
  }
}

void setup() //Setup function - only function that is run in deep sleep mode
{
  Serial.begin(9600); //Start the serial output at 115,200 baud
  pinMode(led_pin, OUTPUT);
  digitalWrite(led_pin, LOW);
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay
  delay(2000);
  // timer.setInterval(1000L, mySensor);
}

// Hàm xử lý khi ESP32 kết nối với Blynk
BLYNK_CONNECTED() {
  Serial.println("ESP32 Connected to Blynk!");
  Blynk.syncVirtual(V0);  // Đồng bộ dữ liệu từ các chân ảo V0
}

void loop() // Hàm lặp
{
  Blynk.run();
  // timer.run();
}