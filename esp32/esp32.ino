#include <WiFi.h>
#include <SocketIoClient.h>

// replace with your wifi credentials
const char* ssid     = "Abrar";
const char* password = "rakib165";


/// Socket.IO Settings ///
char host[] = "192.168.0.105"; // replace with your ipv4 ip, type "ipconfig" in your terminal for this
int port = 5000; 



SocketIoClient webSocket;
WiFiClient client;

void wifiSetup(){
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");  
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void socket_Connected(const char * payload, size_t length) {
  Serial.println("Socket.IO Connected!");
}

void socket_event(const char * payload, size_t length) {
  Serial.print("got message: ");
  Serial.println(payload);
}

void setup() {
  Serial.begin(115200);
  
  wifiSetup(); // connects to wifi

  webSocket.begin(host, port);// sets up the connection

  webSocket.on("connect", socket_Connected); // executes when connects to the server
  webSocket.on("vsm", socket_event); // executes when server emits on the "vsm" event 
}

void loop() { 

  webSocket.loop(); 
  // note: the string needs to be written how its written here, " "the string"  "
  webSocket.emit("message", " \"The String from esp\" "); //emits for the clients on the "message" event
  delay(500);
}
