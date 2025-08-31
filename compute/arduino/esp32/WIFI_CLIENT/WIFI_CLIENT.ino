#include <WiFi.h>

// WiFi配置信息
const char* ssid = "Redmi_2AD8";
const char* password = "zhou920227";

// 重连间隔时间(毫秒)
const unsigned long RECONNECT_INTERVAL = 5000;
unsigned long lastReconnectAttempt = 0;

void setup() {
  Serial.begin(9600);
  
  // 初始化WiFi
  WiFi.mode(WIFI_STA);  // 设置为Station模式
  WiFi.setAutoReconnect(true);  // 启用自动重连
  WiFi.persistent(true);       // 保存连接信息
  
  connectToWiFi();
}

void loop() {
  // 检查WiFi连接状态，如果断开则尝试重连
  if (WiFi.status() != WL_CONNECTED) {
    unsigned long now = millis();
    if (now - lastReconnectAttempt > RECONNECT_INTERVAL) {
      lastReconnectAttempt = now;
      Serial.println("WiFi连接已断开，尝试重连...");
      if (connectToWiFi()) {
        Serial.println("重连成功!");
      }
    }
  }
  
  // 已连接状态下的其他操作
  if (WiFi.status() == WL_CONNECTED) {
    // 这里可以添加你的业务逻辑
    delay(1000);
  }
}

// 连接WiFi函数
bool connectToWiFi() {
  Serial.print("正在连接到 ");
  Serial.println(ssid);
  
  // 开始连接
  WiFi.begin(ssid, password);
  
  // 等待连接结果，超时时间10秒
  unsigned long startAttemptTime = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < 10000) {
    Serial.print(".");
    delay(500);
  }
  
  // 检查连接是否成功
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi连接成功!");
    Serial.print("IP地址: ");
    Serial.println(WiFi.localIP());
    Serial.print("子网掩码: ");
    Serial.println(WiFi.subnetMask());
    Serial.print("网关: ");
    Serial.println(WiFi.gatewayIP());
    return true;
  } else {
    Serial.println("");
    Serial.println("WiFi连接失败!");
    return false;
  }
}
    