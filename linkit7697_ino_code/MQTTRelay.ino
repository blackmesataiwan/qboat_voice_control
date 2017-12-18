
#include <LWiFi.h>
#include <PubSubClient.h>
#define USER_NAME "8fa8300e-b543-4345-bf20-bbbff9e0e167"   
#define USER_PASS "r:ad5cffea691672f24f21e1943329b35b"
#define CLIENT_ID "RELAY7697_1512542438"

IPAddress server(192, 168, 1, 47);      //QIoT Server
char data[80];
char temp1[30];
char hum1[30];

char ssid[] = "LaisanHere";           //網路名稱
char pass[] = "t101419008";  //網路密碼
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiClient client;
PubSubClient download(client);

#define RELAY   4

void reconnect() {     //重新連線
  // Loop until we're reconnected
  while (!download.connected()) {      
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (download.connect(CLIENT_ID, USER_NAME, USER_PASS )) {
      Serial.println("connected");
      download.subscribe("qiot/things/admin/RELAY7697/HomeRelay");  //看QIoT Things的Resource定義
    } 
    else
    {                                           //若沒連線會秀出錯誤資訊
      Serial.print("failed, rc=");
      Serial.print(download.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup()
{
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);
  
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
  // attempt to connect to Wifi network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
  }
  Serial.println("Connected to wifi");
  printWifiStatus();   //wifi 連線資訊

  download.setServer(server, 21883);   //設定與server的連線port
  download.setCallback(callback);
}

void loop()
{
  if (!download.connected()) {
    reconnect();
  }

  download.loop();
}

void printWifiStatus() {  //wifi連線資訊
    // print the SSID of the network you're attached to:
    Serial.print("SSID: ");
    Serial.println(WiFi.SSID());

    // print your WiFi shield's IP address:
    IPAddress ip = WiFi.localIP();
    Serial.print("IP Address: ");
    Serial.println(ip);

    // print the received signal strength:
    long rssi = WiFi.RSSI();
    Serial.print("signal strength (RSSI):");
    Serial.print(rssi);
    Serial.println(" dBm");
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if(payload[0] == '1')
  {
    digitalWrite(RELAY, HIGH);
  }
  else
  {
    digitalWrite(RELAY, LOW);
  }
}

