/**
 * tactSW library sample
 * A接点SW(押すと導通)のOFFでLED点灯, OFFでLED消灯させる
 * SWはマイコン内部でpullupされているのでSW=OFFがHi, SW=ONがLoになる
 * 
 * 接続図
 *  SW1_PIN -- A接点SW -- GND
 *  LED_PIN -- LED -- R -- GND
 *  
 */

#include "tactSW.h"

#define SW1_PIN (8)
#define LED_PIN (7)

tactSW sw1 = tactSW(SW1_PIN);

uint8_t led1level = 0;

void setup(){
	pinMode(LED_PIN, OUTPUT);
	digitalWrite(LED_PIN, led1level);
}


void loop(){
	sw1.edgeClear();  // エッジ確定値のクリア
	sw1.sampling();   // SWのレベル認識とエッジ認識

  // SWのレベル・エッジ認識結果の利用
  led1level = sw1.level();
 
 // LEDへの出力更新    
 digitalWrite(LED_PIN, led1level);
}
