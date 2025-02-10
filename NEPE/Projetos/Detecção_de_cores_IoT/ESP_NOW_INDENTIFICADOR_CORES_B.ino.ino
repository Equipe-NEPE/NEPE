#include <Adafruit_TCS34725.h>
#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <esp_now.h>
#include <WiFi.h>

#define RED 1
#define GREEN 21
#define YELLOW 3
#define BLUE 23
#define WHITE 22

typedef struct struct_message {
    uint16_t vermelho, verde, azul;
    bool estado_sensor;
} 
struct_message;
struct_message myData;

void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingData, int len) {
    memcpy(&myData, incomingData, sizeof(myData));

    if (myData.estado_sensor) {
        if (myData.vermelho >= myData.verde * 2 && myData.vermelho >= myData.azul * 2) {
            digitalWrite(RED, HIGH);
            Serial.println("Cor apresentada é Vermelho");
            delay(3000);
            digitalWrite(RED, LOW);
        } 
        else if (myData.verde >= myData.vermelho * 2 && myData.verde >= myData.azul * 1.3) {
            digitalWrite(GREEN, HIGH);
            Serial.println("Cor apresentada é Verde");
            delay(3000);
            digitalWrite(GREEN, LOW);
        } 
        else if (myData.vermelho >= myData.azul * 2 && myData.verde >= myData.azul * 2) {
            digitalWrite(YELLOW, HIGH);
            Serial.println("Cor apresentada é Amarelo");
            delay(3000);
            digitalWrite(YELLOW, LOW);
        } 
        else if (myData.azul >= myData.vermelho * 2 && myData.azul >= myData.verde * 1.1) {
            digitalWrite(BLUE, HIGH);
            Serial.println("Cor apresentada é Azul");
            delay(3000);
            digitalWrite(BLUE, LOW);
        } 
        else if (myData.vermelho >= myData.verde * 0.75 && myData.verde >= myData.azul * 1.3) {
            digitalWrite(WHITE, HIGH);
            Serial.println("Cor apresentada é Branco");
            delay(3000);
            digitalWrite(WHITE, LOW);
        } 
        else {
            digitalWrite(2, HIGH);
            Serial.println("Cor Ambiente");
            delay(3000);
            digitalWrite(2, LOW);
        }
    }
}

void setup() {
    Serial.begin(115200);
    pinMode(2, OUTPUT);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(BLUE, OUTPUT);
    pinMode(WHITE, OUTPUT);

    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
    esp_now_register_recv_cb(OnDataRecv);
}

void loop() {}
