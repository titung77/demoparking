#define BLYNK_TEMPLATE_ID "TMPL6wWSDm0fI"
#define BLYNK_TEMPLATE_NAME "ParkingTung"
#define BLYNK_AUTH_TOKEN "apAuzTbUZwDbn_i-0R_eEJxH4YO241GP"
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Mr.Tung";
char pass[] = "tungphan6868";
#define TRIG_PIN 5
#define ECHO_PIN 18
#define LED_PIN V1  // Thay đổi V1 thành V2 cho đèn LED trên Blynk

BlynkTimer timer;

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  
  // Thực hiện đo khoảng cách mỗi 2 giây
  timer.setInterval(2000L, measureDistance);
}

void measureDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  float distance_cm = duration / 58.0; // Chuyển thời gian sang khoảng cách (đơn vị cm)

  // Gửi khoảng cách lên ứng dụng Blynk
  Blynk.virtualWrite(V0, distance_cm);

  Serial.print("Khoang cach: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Kiểm tra khoảng cách và bật/tắt đèn trên Blynk
  if (distance_cm >= 0 && distance_cm <= 50) {
    Blynk.virtualWrite(LED_PIN, HIGH); // Bật đèn trên Blynk
  } else {
    Blynk.virtualWrite(LED_PIN, LOW); // Tắt đèn trên Blynk
  }
}

void loop() {
  Blynk.run();
  timer.run();
}
