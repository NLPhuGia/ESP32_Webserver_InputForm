#include <WiFi.h>
#include <WebSocketsClient.h>     

const char* ssid = "CHUONG_H";
const char* password = "vn911989";
const char* serverAddress = "ws://127.0.0.1:8080"; // Thay thế bằng địa chỉ máy chủ WebSocket

WebSocketsClient webSocket;

void webSocketEvent(WStype_t type, uint8_t* payload, size_t length) {
    switch (type) {
    case WStype_DISCONNECTED:
        Serial.println("[WebSocket] Disconnected");
        break;
    case WStype_CONNECTED:
        Serial.println("[WebSocket] Connected");
        break;
    case WStype_TEXT:
        Serial.print("[WebSocket] Received message: ");
        Serial.println((char*)payload);
        break;
    }
}

void setup() {
    Serial.begin(115200);

    // Kết nối với mạng Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");

    // Thiết lập kết nối WebSocket
    webSocket.begin(serverAddress);
    webSocket.onEvent(webSocketEvent);
}

void loop() {
    // Kiểm tra và duy trì kết nối WebSocket
    webSocket.loop();

    // Gửi tin nhắn đến máy chủ WebSocket
    webSocket.send("Hello, WebSocket!");

    delay(1000);
}
