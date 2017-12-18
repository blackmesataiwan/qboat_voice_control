
#include <LWiFi.h>
#include <PubSubClient.h>
#define USER_NAME "fdbe9823-1522-4cd5-9461-2f47ea514146"   
#define USER_PASS "r:49117ecc7f568475ada142b00d6461ff"
#define CLIENT_ID "MON7697_1512545078"

/*****溫溼度的函式庫********/
#include "DHT.h"
#define dht_dpin 3
#define DHTTYPE DHT11   // DHT 11
DHT dht(dht_dpin, DHTTYPE);

IPAddress server(192, 168, 1, 47);      //QIoT Server
char data[80];
char temp1[30];
char hum1[30];

char ssid[] = "LaisanHere";           //網路名稱
char pass[] = "t101419008";  //網路密碼
int keyIndex = 0;
int status = WL_IDLE_STATUS;
WiFiClient client;
PubSubClient upload(client);

void reconnect() {     //重新連線
  // Loop until we're reconnected
  while (!upload.connected()) {      
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
   if (upload.connect(CLIENT_ID, USER_NAME, USER_PASS )) {
      Serial.println("connected");    } 
    else {                                           //若沒連線會秀出錯誤資訊
             Serial.print("failed, rc=");
             Serial.print(upload.state());
             Serial.println(" try again in 5 seconds");
              // Wait 5 seconds before retrying
              delay(5000);
    }
  }
}
void setup()
{
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
    upload.setServer(server, 21883);   //設定與server的連線port
    delay(1500);

    // Activate DHT11
    dht.begin();
}
void loop()
{
  Serial.print("Humidity = ");   
  Serial.print(dht.readHumidity());   
  Serial.print("% ");   
  Serial.print("temperature = ");   
  Serial.print(dht.readTemperature());   
  Serial.println("C "); 

  String h= String(dht.readHumidity());
  String t= String(dht.readTemperature());
  String payload = "{\"value\":{\"temperature\":"+ t +",\"humidity\":"+h+"}}";   // 寫入要上傳資料

payload.toCharArray(data, (payload.length() + 1));
  if (!upload.connected()) {
    reconnect();
}
  else{ //送出資料至QIoT 而topic會在驗證後resource得到
    upload.publish("qiot/things/admin/MON7697/HomeEnv",data);     //將資料上傳至對應主題
    delay(100);
  }
  upload.loop();
  delay(2000);
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

