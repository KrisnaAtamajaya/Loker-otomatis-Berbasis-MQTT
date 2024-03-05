#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "UTDI-UKM-1";
const char* password = "";
const char* mqtt_server = "broker.mqtt-dashboard.com";

const char* topic_loker1 = "smart-locker/loker1";
const char* topic_loker2 = "smart-locker/loker2";
const char* topic_loker3 = "smart-locker/loker3";
const char* topic_loker4 = "smart-locker/loker4";

const int solenoid_pin_loker1 = 23;
const int solenoid_pin_loker2 = 22;
const int solenoid_pin_loker3 = 21;
const int solenoid_pin_loker4 = 19;

WiFiClient wifiClient;
PubSubClient client(wifiClient);

void setup() {
  pinMode(solenoid_pin_loker1, OUTPUT);
  pinMode(solenoid_pin_loker2, OUTPUT);
  pinMode(solenoid_pin_loker3, OUTPUT);
  pinMode(solenoid_pin_loker4, OUTPUT);

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  while (!client.connected()) {
    Serial.println("Connecting to MQTT server...");
    if (client.connect("esp32Client")) {
      Serial.println("Connected to MQTT server");
      client.subscribe(topic_loker1);
      client.subscribe(topic_loker2);
      client.subscribe(topic_loker3);
      client.subscribe(topic_loker4);
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }
}

void loop() {
  client.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String message = "";
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println("Message received: " + message);
  if (strcmp(topic, topic_loker1) == 0) {
    if (message == "unlock") {
      digitalWrite(solenoid_pin_loker1, HIGH);
      Serial.println("Door loker1 is unlocked");
    } else if (message == "lock") {
      digitalWrite(solenoid_pin_loker1, LOW);
      Serial.println("Door loker1 is locked");
    }
  } else if (strcmp(topic, topic_loker2) == 0) {
    if (message == "unlock") {
      digitalWrite(solenoid_pin_loker2, HIGH);
      Serial.println("Door loker2 is unlocked");
    } else if (message == "lock") {
      digitalWrite(solenoid_pin_loker2, LOW);
      Serial.println("Door loker2 is locked");
    }
  } else if (strcmp(topic, topic_loker3) == 0) {
    if (message == "unlock") {
      digitalWrite(solenoid_pin_loker3, HIGH);
      Serial.println("Door loker3 is unlocked");
    } else if (message == "lock") {
      digitalWrite(solenoid_pin_loker3, LOW);
      Serial.println("Door loker3 is locked");
    }
  } else if (strcmp(topic, topic_loker4) == 0) {
    if (message == "unlock") {
      digitalWrite(solenoid_pin_loker4, HIGH);
      Serial.println("Door loker4 is unlocked");
    } else if (message == "lock") {
      digitalWrite(solenoid_pin_loker4, LOW);
      Serial.println("Door loker4 is locked");
    }
  }
}