#include <WiFi.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

// WiFi Credentials
const char* ssid = "Airtel_kumm_0120";
const char* password = "Air@24885";

// MQTT Configuration
const char* local_server = "192.168.1.5";
const int local_port = 1883;

// HiveMQ Cloud Configuration
const char* cloud_server = "6e7b29c81521455da6d7030fcfa04fa9.s1.eu.hivemq.cloud";
const int cloud_port = 8883;
const char* cloud_user = "hivemq.webclient.1748548759446";
const char* cloud_pass = "XY1u3BN2s,#CkGd>l9;o";

// Root CA Certificate
const char* root_ca = \
"-----BEGIN CERTIFICATE-----\n" \
"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\n" \
"-----END CERTIFICATE-----\n";

// MQTT Topics
#define LOCAL_DATA_TOPIC "esp32/local/data"
#define CLOUD_DATA_TOPIC "esp32/cloud/data"
#define CONTROL_TOPIC "esp32/control/gpio2"  // Same for both brokers

// Objects
WiFiClient localClient;
WiFiClientSecure secureClient;
PubSubClient mqttLocal(localClient);
PubSubClient mqttCloud(secureClient);

// Variables
unsigned long lastMsgTime = 0;
const long interval = 2000;
const int gpio2 = 2;

void setup_wifi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("\nWiFi connected");
  Serial.println("IP address: " + WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("]: ");
  
  String message;
  for (int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Control GPIO2 from ANY broker
  if (String(topic) == CONTROL_TOPIC) {
    if (message == "ON") {
      digitalWrite(gpio2, HIGH);
      Serial.println("GPIO2 set HIGH (via MQTT)");
    } else if (message == "OFF") {
      digitalWrite(gpio2, LOW);
      Serial.println("GPIO2 set LOW (via MQTT)");
    }
  }
}

void reconnectMQTT(PubSubClient& client, bool isCloud) {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection to ");
    Serial.println(isCloud ? "Cloud" : "Local");
    
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    
    if (isCloud) {
      if (client.connect(clientId.c_str(), cloud_user, cloud_pass)) {
        Serial.println("Cloud MQTT connected!");
        client.subscribe(CONTROL_TOPIC);
      } else {
        Serial.print("Cloud connection failed, rc=");
        Serial.print(client.state());
        Serial.println(" retrying in 5 seconds");
        delay(5000);
      }
    } else {
      if (client.connect(clientId.c_str())) {
        Serial.println("Local MQTT connected!");
        client.subscribe(CONTROL_TOPIC);  // Subscribe to control topic locally
      } else {
        Serial.print("Local connection failed, rc=");
        Serial.print(client.state());
        Serial.println(" retrying in 5 seconds");
        delay(5000);
      }
    }
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(gpio2, OUTPUT);
  digitalWrite(gpio2, LOW);

  setup_wifi();
  
  // Configure Cloud MQTT
  secureClient.setCACert(root_ca);
  mqttCloud.setServer(cloud_server, cloud_port);
  mqttCloud.setCallback(callback);  // Set callback for cloud
  
  // Configure Local MQTT
  mqttLocal.setServer(local_server, local_port);
  mqttLocal.setCallback(callback);  // Set same callback for local
}

void loop() {
  // Maintain cloud connection
  if (!mqttCloud.connected()) {
    reconnectMQTT(mqttCloud, true);
  }
  mqttCloud.loop();

  // Maintain local connection
  if (!mqttLocal.connected()) {
    reconnectMQTT(mqttLocal, false);
  }
  mqttLocal.loop();

  // Publish temperature data
  unsigned long currentTime = millis();
  if (currentTime - lastMsgTime > interval) {
    lastMsgTime = currentTime;
    
    float temperature = 20.0 + random(1000)/100.0;
    String tempString = String(temperature, 2);
    
    mqttLocal.publish(LOCAL_DATA_TOPIC, tempString.c_str());
    mqttCloud.publish(CLOUD_DATA_TOPIC, tempString.c_str());
    
    Serial.println("Published: " + tempString);
  }
