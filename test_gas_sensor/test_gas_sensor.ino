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

// #define led_pin  15
#define MQ2_PIN 34        // Chân DATA của MQ-2 kết nối với GPIO 19 của ESP32
double gas_value = 0;

#define BUZZER_PIN 18

// BLYNK_WRITE(V0)
// {
//   if(param.asInt()!=0){
//     digitalWrite(led_pin, HIGH);
//   }else{
//     digitalWrite(led_pin, LOW);
//   }
// }

void sendSensorData()
{
  gas_value = analogRead(MQ2_PIN);
  for(int i=1; i<100; i++){
    gas_value+=analogRead(MQ2_PIN);
  }
  double gas_average = gas_value/100;
  // Ghi giá trị vào chân ảo V3
  Blynk.virtualWrite(V3,gas_average);
  // In giá trị lên Serial Monitor:
  Serial.println(String("Gas value: ")+gas_average);
  // Kiểm tra giá trị gas:
  if(gas_average>700){
    digitalWrite(BUZZER_PIN, HIGH);
  }else{
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void setup() //Setup function - only function that is run in deep sleep mode
{
  Serial.begin(9600); // Bắt đầu chạy màn hình Serial với tốc độ 9600 baud

  // Thiết lập led
  // pinMode(led_pin, OUTPUT);
  // digitalWrite(led_pin, LOW);

  // THiết lập cảm biến MQ-2:
  pinMode(MQ2_PIN, INPUT);

  // THiết lập đầu ra cho còi:
  pinMode(BUZZER_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay

  // Tạm dừng 2s để hệ thống hoàn tất các thiết lập cần thiết
  delay(2000);

  // Mỗi 1s gọi hàm 1 lần
  timer.setInterval(1000L, sendSensorData);

}

// Hàm xử lý khi ESP32 kết nối với Blynk
BLYNK_CONNECTED() {
  Serial.println("ESP32 Connected to Blynk!");
  Blynk.syncVirtual(V0, V1, V2, V3);  // Đồng bộ dữ liệu từ các chân ảo V0
}

void loop() // Hàm lặp
{
  Blynk.run();
  timer.run();
}