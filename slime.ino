#include <M5Core2.h>

void setup() {
  M5.begin(true, true, true, true);
  M5.Lcd.fillRect(0, 0, 320, 240, BLUE);
  M5.Lcd.fillCircle(100, 70, 40, WHITE);
  M5.Lcd.fillCircle(100, 70, 20, BLACK);
  M5.Lcd.fillCircle(220, 70, 40, WHITE);
  M5.Lcd.fillCircle(220, 70, 20, BLACK);

  
}

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
    M5.Lcd.fillRect(0, 0, 320, 240, BLUE);
    M5.Lcd.fillCircle(100, 70, 40, ORANGE);
    M5.Lcd.fillCircle(100, 70, 20, BLACK);
    M5.Lcd.fillCircle(220, 70, 40, ORANGE);
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

void loop() {

}
