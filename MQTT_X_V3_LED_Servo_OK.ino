
#include <WiFi.h>
#include <PubSubClient.h>

// WiFi
const char* ssid = "xxxxxxxxxxx";
const char* password = "xxxxxxxxxxxxx";

// WiFi
//const char* ssid = "xxxxxxxxx";
//const char* password = "xxxxxxxxxxxxx";

// MQTT Broker
const char *mqtt_broker = "broker.emqx.io";
const char *mqtt_username = "emqx";
const char *mqtt_password = "public";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

const int ledPinSala = 25;        // Porta GPIO para o LED da Sala
const int ledPinCozinha = 26;     // Porta GPIO para o LED da Cozinha
const int ledPinBanheiro = 33;    // Porta GPIO para o LED do Banheiro
const int ledPinQuarto = 32;      // Porta GPIO para o LED do Quarto
const int ledPinCorredor = 22;    // Porta GPIO para o LED do Corredor
const int ledPinCopa = 12;        // Porta GPIO para o LED da Copa
const int ledPinGaragem = 14;     // Porta GPIO para o LED da Garagem
const int servoPin = 15;          // Porta GPIO para o Servo da Garagem

void setup() {
  Serial.begin(115200);

  pinMode(ledPinSala, OUTPUT);        // Configura o pino do LED da Sala como saída
  pinMode(ledPinCozinha, OUTPUT);     // Configura o pino do LED da Cozinha como saída
  pinMode(ledPinBanheiro, OUTPUT);    // Configura o pino do LED do Banheiro como saída
  pinMode(ledPinQuarto, OUTPUT);      // Configura o pino do LED do Quarto como saída
  pinMode(ledPinCorredor, OUTPUT);    // Configura o pino do LED do Corredor como saída
  pinMode(ledPinCopa, OUTPUT);        // Configura o pino do LED da Copa como saída
  pinMode(ledPinGaragem, OUTPUT);     // Configura o pino do LED da Garagem como saída

  pinMode(servoPin, OUTPUT);          // Configura o pino do Servo como saída

  // Conectando à rede WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  // Conectando ao broker MQTT
  client.setServer(mqtt_broker, mqtt_port);
  client.setCallback(callback);
  while (!client.connected()) {
    String client_id = "esp32-client-";
    client_id += String(WiFi.macAddress());
    Serial.printf("The client %s connects to the public MQTT broker\n", client_id.c_str());
    if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
      Serial.println("Public EMQX MQTT broker connected");
    } else {
      Serial.print("Failed with state ");
      Serial.print(client.state());
      delay(2000);
    }
  }

  // Publicando e assinando tópicos renomeados
  client.publish("esp32/response", "Hi Harry I'm ESP32");
  client.subscribe("Casa/Sala");
  client.subscribe("Casa/Cozinha");
  client.subscribe("Casa/Banheiro");
  client.subscribe("Casa/Quarto");
  client.subscribe("Casa/Corredor");
  client.subscribe("Casa/Copa");
  client.subscribe("Casa/Garagem");
  client.subscribe("Casa/PortaGaragem");
}

void callback(char *topic, byte *payload, unsigned int length) {
  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  Serial.print("Message: ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  // Controle dos LEDs
  if (strcmp(topic, "Casa/Sala") == 0) {
    Serial.println("Controlando Sala...");
    controlaLED(ledPinSala, payload, length);
  } else if (strcmp(topic, "Casa/Cozinha") == 0) {
    Serial.println("Controlando Cozinha...");
    controlaLED(ledPinCozinha, payload, length);
  } else if (strcmp(topic, "Casa/Banheiro") == 0) {
    Serial.println("Controlando Banheiro...");
    controlaLED(ledPinBanheiro, payload, length);
  } else if (strcmp(topic, "Casa/Quarto") == 0) {
    Serial.println("Controlando Quarto...");
    controlaLED(ledPinQuarto, payload, length);
  } else if (strcmp(topic, "Casa/Corredor") == 0) {
    Serial.println("Controlando Corredor...");
    controlaLED(ledPinCorredor, payload, length);
  } else if (strcmp(topic, "Casa/Copa") == 0) {
    Serial.println("Controlando Copa...");
    controlaLED(ledPinCopa, payload, length);
  } else if (strcmp(topic, "Casa/Garagem") == 0) {
    Serial.println("Controlando Garagem...");
    controlaLED(ledPinGaragem, payload, length);
  } else if (strcmp(topic, "Casa/PortaGaragem") == 0) {
    Serial.println("Controlando Porta da Garagem...");
    controlaServo(payload, length);
  }
}

void controlaLED(int pin, byte *payload, unsigned int length) {
  if (strstr((char*)payload, "Ligar") != NULL) {
    Serial.println("Comando para Ligar recebido");
    digitalWrite(pin, HIGH);
    Serial.println("LED ligado");
  } else if (strstr((char*)payload, "Desligar") != NULL) {
    Serial.println("Comando para Desligar recebido");
    digitalWrite(pin, LOW);
    Serial.println("LED desligado");
  }
}

void controlaServo(byte *payload, unsigned int length) {
  if (strstr((char*)payload, "Abrir") != NULL) {
    Serial.println("Comando para Abrir a Porta da Garagem recebido");
    moverServoCompleto();
    Serial.println("Porta da Garagem aberta");
  } else if (strstr((char*)payload, "Fechar") != NULL) {
    Serial.println("Comando para Fechar a Porta da Garagem recebido");
    moverServoCompleto();
    Serial.println("Porta da Garagem fechada");
  }
}

void moverServoCompleto() {
  for (int i = 0; i <= 180; i++) {
    servoWrite(i);
    delay(10);
  }
  delay(5000);
}

void servoWrite(int angle) {
  int pulseWidth = 1000 * angle / 180 + 500;
  digitalWrite(servoPin, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(servoPin, LOW);
  delayMicroseconds(10000 - pulseWidth);
}

void loop() {
  client.loop();
}