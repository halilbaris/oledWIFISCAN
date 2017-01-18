
#include "ESP8266WiFi.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET LED_BUILTIN  // 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 64)
#endif

int screen_roll_delay = 800;

void setup() {

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("  KABLOSUZ AGLAR");
  Serial.begin(115200);
  Serial.println("Setup begins....");
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  Serial.println("Setup completes!!!");
  display.println("------------------");
  display.println("   www.arduinom.org");
  display.println("     HOSGELDINIZ");
  display.display();
  delay(5000);
}

void loop() {
  Serial.println("Scan starts...");

  display.clearDisplay();
  display.display();
  display.setCursor(0, 0);
  display.println("Araniyor...");
  display.display();

  digitalWrite(0, HIGH);
  int n = WiFi.scanNetworks();
  Serial.println(" and completes!!!");

  if (n == 0) {
    Serial.println("No WiFi found!!!");

    // update OLED
    display.clearDisplay();
    display.display();
    display.setCursor(0, 0);
    display.println("Araniyor...");
    display.println("Ag bulunamadi!!!");
    display.display();
    digitalWrite(0, LOW);
  }
  else
  {
    Serial.print(n);
    Serial.println(" Networks found:");
    Serial.println("----------------");

    for (int i = 0; i < n; ++i)
    {
      digitalWrite(0, HIGH);


      Serial.print(i + 1);
      Serial.print(": ");
      Serial.print(WiFi.SSID(i));
      Serial.print(": ");
      Serial.print(WiFi.RSSI(i));
      Serial.print("dBm | ");
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Not Encrypted" : "Encrypted");
      display.clearDisplay();
      display.display();
      display.setCursor(0, 0);
      display.print("Network ");
      display.print(i + 1);
      display.print(" / ");
      display.println(n);
      display.display();
      display.println(WiFi.SSID(i));
      display.println("-------------------");
      display.print(WiFi.RSSI(i));
      display.print("dBm | ");
      display.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? "Sifresiz" : "Sifreli");
      display.display();

      delay(screen_roll_delay);
      digitalWrite(0, LOW);
      delay(screen_roll_delay);
      digitalWrite(0, HIGH);
      delay(screen_roll_delay);
      digitalWrite(0, LOW);
      delay(screen_roll_delay);
    }
  }
  Serial.println("");
}
