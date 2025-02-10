//ESP32 A
#include <Adafruit_TCS34725.h>
#include <Arduino.h>
#include <Wire.h>
#include  <SPI.h>
#include <esp_now.h>
#include <WiFi.h>

uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_1X);
const int led_esp = 2;

typedef struct struct_message {
uint16_t vermelho, verde, azul;
bool estado_sensor = false;
} 
struct_message;
struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup(void) {
  
  pinMode(led_esp, OUTPUT);
  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_send_cb(OnDataSent);
  
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  if (tcs.begin()) {
    Serial.println("Sensor encontrado");
  } else {
    Serial.println("Sensor nao encontrado ... verifique as conexoes");
    while (1);
  }
}

void loop(void) {

    esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
    if (result == ESP_OK) {
    Serial.println("Sent with success");
    }
    else {
      Serial.println("Error sending the data");
    }

    uint16_t r, g, b, c, tempCor, lux;
    tcs.getRawData(&r, &g, &b, &c);
    tempCor = tcs.calculateColorTemperature_dn40(r, g, b, c);
    lux = tcs.calculateLux(r, g, b);

    Serial.print("Temp. da cor: "); Serial.print(tempCor, DEC); Serial.print(" K - ");
    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
    Serial.println(" ");

    if (myData.vermelho > r + (r * 0.1) || myData.vermelho < r - (r * 0.1) || myData.verde > g + (g * 0.1) || myData.verde < g - (g * 0.1) || myData.azul > b + (b * 0.1) || myData.azul < b - (b * 0.1)) {
      myData.estado_sensor = true;
    } 
    else {
      myData.estado_sensor = false;
    }

    myData.vermelho = r;
    myData.verde = g;
    myData.azul = b;    
}