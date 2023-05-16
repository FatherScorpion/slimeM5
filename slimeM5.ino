#include <M5Core2.h>
#include <esp_now.h>
#include <WiFi.h>

esp_now_peer_info_t slave;

void drawSlime(int num){
  if(num==0){
    M5.Lcd.fillRect(0, 0, 320, 240, BLUE);
    M5.Lcd.fillCircle(100, 70, 40, WHITE);
    M5.Lcd.fillCircle(100, 70, 20, BLACK);
    M5.Lcd.fillCircle(220, 70, 40, WHITE);
    M5.Lcd.fillCircle(220, 70, 20, BLACK);
    int x=90;
    int y=140;
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, RED);
      x++;
      y++;  
    }
    for(x=x;x<180;x++){
      M5.Lcd.fillCircle(x, y, 10, RED);
    }
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, RED);
      x++;
      y--;  
    }
  }else if(num==1){
    M5.Lcd.fillRect(0, 0, 320, 240, ORANGE);
    M5.Lcd.fillCircle(100, 70, 40, WHITE);
    M5.Lcd.fillCircle(100, 70, 20, BLACK);
    M5.Lcd.fillCircle(220, 70, 40, WHITE);
    M5.Lcd.fillCircle(220, 70, 20, BLACK);
    int x=90;
    int y=140;
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, PURPLE);
      x++;
      y++;  
    }
    for(x=x;x<180;x++){
      M5.Lcd.fillCircle(x, y, 10, PURPLE);
    }
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, PURPLE);
      x++;
      y--;  
    }
  }else{
    M5.Lcd.fillRect(0, 0, 320, 240, LIGHTGREY);
    M5.Lcd.fillCircle(100, 70, 40, WHITE);
    M5.Lcd.fillCircle(100, 70, 20, BLACK);
    M5.Lcd.fillCircle(220, 70, 40, WHITE);
    M5.Lcd.fillCircle(220, 70, 20, BLACK);
    int x=90;
    int y=140;
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, RED);
      x++;
      y++;  
    }
    for(x=x;x<180;x++){
      M5.Lcd.fillCircle(x, y, 10, RED);
    }
    for(int i=0;i<50;i++){
      M5.Lcd.fillCircle(x, y, 10, RED);
      x++;
      y--;  
    }
  }
}

// 送信コールバック
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.print("Last Packet Sent to: ");
  Serial.println(macStr);
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

// 受信コールバック
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  char macStr[18];
  char msg[1];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.printf("Last Packet Recv from: %s\n", macStr);
  Serial.printf("Last Packet Recv Data(%d): ", data_len);
  for ( int i = 0 ; i < data_len ; i++ ) {
    msg[1] = data[i];
    Serial.print(msg[1]);
  }
  Serial.println("");

  drawSlime(data[0]);
}

void setup() {
  M5.begin(true, true, true, true);
  drawSlime(0);

  Serial.begin(115200);

  // ESP-NOW初期化
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() == ESP_OK) {
    Serial.println("ESPNow Init Success");
  } else {
    Serial.println("ESPNow Init Failed");
    ESP.restart();
  }

  // マルチキャスト用Slave登録
  memset(&slave, 0, sizeof(slave));
  for (int i = 0; i < 6; ++i) {
    slave.peer_addr[i] = (uint8_t)0xff;
  }
  
  esp_err_t addStatus = esp_now_add_peer(&slave);
  if (addStatus == ESP_OK) {
    // Pair success
    Serial.println("Pair success");
  }
  // ESP-NOWコールバック登録
  esp_now_register_send_cb(OnDataSent);
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  M5.update();
  if(M5.BtnA.wasPressed()){
    drawSlime(0);
    uint8_t data[1] = {0};
    esp_now_send(slave.peer_addr, data, sizeof(data));
  }
  if(M5.BtnB.wasPressed()){
    drawSlime(1);
    uint8_t data[1] = {1};
    esp_now_send(slave.peer_addr, data, sizeof(data));
  }
  if(M5.BtnC.wasPressed()){
    drawSlime(2);
    uint8_t data[1] = {2};
    esp_now_send(slave.peer_addr, data, sizeof(data));
  }

  delay(100);
}
