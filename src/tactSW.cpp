/** tactSW library
*	arduino
*/
#include <Arduino.h>
#include "tactSW.h"

tactSW::tactSW(uint8_t pin){
	_pin = pin;
	pinMode(_pin, INPUT_PULLUP);
	
}

void tactSW::sampling(void){
	// level sampling
	b_level = (b_level << 1) |( 0x01 & digitalRead (_pin));

	// level認識
		switch(b_level & 0x03){
		case 0x00:	// Loレベル確定
			d_level = (d_level << 1);
			break;
		case 0x03:	// Hiレベル確定
			d_level = (d_level << 1) | 0x01;
			break;
		default:	// レベル不確定(Hi,Lo混在)
			return;
		break;
	}
	
	// これ以降の処理はHi,Loレベル認識値が確定した場合のみ行う
	// edge認識
	switch(d_level & 0x03){
		case 0x01:	// Lo to Hi (0bxxxx xx01)
			d_edgeLtoH |= 0x1;
			break;
		case 0x02:	// Hi to Lo	(0bxxxxx xx10)
			d_edgeHtoL |= 0x1;
			break;
		default:	// エッジ未確定
			// nothing
		break;
	}
}

void tactSW::edgeClear(void){
	d_edgeLtoH = 0x00;
	d_edgeHtoL = 0x00;
}

uint8_t tactSW::level(void){
	return(d_level & 0x01);
}

uint8_t tactSW::edgeHToL(void){
	return(d_edgeHtoL & 0x01);
}

uint8_t tactSW::edgeLToH(void){
	return(d_edgeLtoH & 0x01);
}
