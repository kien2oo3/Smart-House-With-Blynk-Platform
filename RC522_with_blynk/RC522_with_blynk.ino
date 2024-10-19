#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <deprecated.h>
#include <require_cpp11.h>

// Khai báo các hằng số cần thiết của Template
#define BLYNK_TEMPLATE_ID "TMPL6bBp0Lwdq"
#define BLYNK_TEMPLATE_NAME "Smart House"
#define BLYNK_AUTH_TOKEN "ONgxUUEQ5b65W4O6hKocUzyhYB5Zb2GP"
#define BLYNK_PRINT Serial


#include <SPI.h>
#include <MFRC522.h>
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

BlynkTimer timer;

#define RST_PIN 22  // Chân RST nối với GPIO22
#define SS_PIN 5    // Chân SDA nối với GPIO5
#define RELAY_PIN 4 // Chân điều khiển relay (quạt)

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Tạo đối tượng cảm biến thẻ từ

// UID hợp lệ của thẻ
String validCardID = "3d67362";  // Lưu ý UID không có khoảng trắng và viết thường

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Tầng 3"; // Khai báo tên Wifi
char pass[] = "13572468"; // Khai báo mật khẩu Wifi


void setup() {
  Serial.begin(9600);
  //SPI.begin();  // Khởi tạo SPI bus
 //mfrc522.PCD_Init();  // Khởi tạo cảm biến thẻ từ

  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);

  Blynk.begin(auth, ssid, pass);  // Kết nối với Blynk
  // Tạm dừng 2s để hệ thống hoàn tất các thiết lập cần thiết
  delay(2000);
  // Mỗi 1s gọi hàm 1 lần
  //timer.setInterval(1000L, myFunc);
  
}


BLYNK_WRITE(V0)
{
  if(param.asInt()!=0){
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("ON");
  }else{
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("OFF");
  }
}

// void myFunc(){
// // Kiểm tra xem có thẻ từ hay không
//   if (!mfrc522.PICC_IsNewCardPresent()) {
//     return;
//   }
  
//   // Kiểm tra xem thẻ đã được đọc thành công chưa
//   if (!mfrc522.PICC_ReadCardSerial()) {
//     return;
//   }

//   String uid = getIdCard();
//   Serial.println(String("Current ID: ") + uid);

//   if (uid == validCardID) {
//     digitalWrite(RELAY_PIN, HIGH);  // Bật quạt nếu thẻ hợp lệ
//     Serial.println("Quạt bật");
//     // Giữ quạt bật trong 5 giây rồi tắt
//     delay(5000);  // Đợi 5 giây
//     digitalWrite(RELAY_PIN, LOW);   // Tắt quạt sau 5 giây
//     Serial.println("Quạt tắt sau 5 giây");
//   } else {
//     digitalWrite(RELAY_PIN, LOW);   // Tắt quạt nếu thẻ không hợp lệ
//     Serial.println("Quạt tắt");
//   }

// }

void loop() {
  Blynk.run();
  //timer.run();
}

// // Hàm lấy ID của thẻ cần kiểm tra
// String getIdCard() {
//   String cardUID = "";
//   for (byte i = 0; i < mfrc522.uid.size; i++) {
//     cardUID += String(mfrc522.uid.uidByte[i], HEX);  // Chuyển đổi thành chuỗi hex
//   }
//   cardUID.toLowerCase();  // Chuyển UID về dạng chữ thường
//   return cardUID;
// }


