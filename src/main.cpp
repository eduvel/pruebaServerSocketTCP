#include <Arduino.h>

#include <ESP8266WiFi.h>
#include "secrets.h"
/*const char* ssid = "TuRedWiFi";
const char* password = "TuContraseñaWiFi";
en secrets.h*/

WiFiServer server(8888); // Puerto para el servidor

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.begin(115200);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  Serial.println("Conexión WiFi establecida");
  Serial.print("Dirección IP asignada: ");
  Serial.println(WiFi.localIP());

  server.begin();
  Serial.print("Abre Telnet y conéctate a la IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" en el puerto ");
  Serial.println(8888);
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        if (c == '1') {
          digitalWrite(LED_BUILTIN, HIGH); // Encender el LED
        } else if (c == '0') {
          digitalWrite(LED_BUILTIN, LOW); // Apagar el LED
        }
      }
    }
    client.stop();
  }
}
