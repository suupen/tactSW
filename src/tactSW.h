#ifndef TACTSW_H
#define TACTSW_H

/** tactSW library
*	arduino
*	タクトSWの押された状態(level)やON,OFF間の変化(edge)の認識を行う
*	pinのレベルが３回一致したらそれをレベルの確定値とする。（SWのチャタリングを回避する）
*/
#include <Arduino.h>

class tactSW{
public:
	tactSW(uint8_t pin);	// pinへの配線: pin -- SW -- GND	,pinはマイコン内部でpull upされる
							// A接点SW(押すと接点が閉じるタイプ): Hi:SW=OFF, Lo:SW=ON
							// B接点SW(押すと接点が開くタイプ): Hi:SW=ON,  Lo:SW=OFF
	
	void sampling(void);	// 実行する毎に一回pinのレベルを取り込む。取り込んだレベル値の３回一致でレベル確定し、レベル確定値からエッジ認識を行う	
	void edgeClear(void);	// 確定したエッジデータをクリアする(エッジデータを使ったら次のエッジを識別するために、この関数でエッジ認識をクリアする)
	
	uint8_t level(void);	// 確定値のレベル値を戻り値として返す	0:Low, 1:Hi
	uint8_t edgeHToL(void);	// HiからLoへのエッジ認識( 押して導通するSWの場合は、OFFからONへのエッジ認識になる)		0:エッジ認識なし, 1:エッジ認識あり
	uint8_t edgeLToH(void);	// LoからHiへのエッジ認識(ONからOFFへのエッジ認識になる)								0:エッジ認識なし, 1:エッジ認識あり
	
private:
	uint8_t _pin;
	uint8_t b_level = 0x00;	// pinのレベル値	0bit:最新, 1bit:1回前, 2bit:2回前, ・・・ 7bit:7回前		0:Lo, 1:Hi
	uint8_t d_level = 0x00;	// レベル確定値		0bit:最新, 1bit:1回前, 2bit:2回前, ・・・ 7bit:7回前		0:Lo, 1:Hi
	uint8_t d_edgeLtoH = 0x00;		// LoからHiレベルエッジ認識	0:なし, 1:あり
	uint8_t d_edgeHtoL = 0x00;		// HiからLoレベルエッジ認識 0:なし, 1:あり
	
};


#endif // TACTSW_H
