#include "KeyPad.h"

/***************************************************************
Constructor with overriding
****************************************************************/
KeyPad::KeyPad(char *_keys,byte _ROWS,byte _COLS,byte *_rowPins,byte *_colPins){
	begin(_keys);
	rowPins = _rowPins;
	colPins = _colPins;
	ROWS = _ROWS;
	COLS = _COLS;
}

/***************************************************************
Keys Initialization
****************************************************************/
void KeyPad::begin(char *_keys){
	keys = _keys;	
}

/****************************************************************
Polling keypad Column
return:
0: Column 0 active
1: Column 1 active
2: Column 2 active
3: Column 3 active (for 4x4 keypad)
4: No active column
****************************************************************/
unsigned char KeyPad::check_column(){
	if (digitalRead(colPins[0])==LOW){
		delay(10);
		if(digitalRead(colPins[0])==LOW){
			delay(10);
			while (!(digitalRead(colPins[0]))){};
			return 0;
		}
	}
	else if (digitalRead(colPins[1])==LOW){
		delay(10);
		if(digitalRead(colPins[1])==LOW){
			delay(10);
			while (!(digitalRead(colPins[1]))){};
			return 1;
		}
	}
	else if (digitalRead(colPins[2])==LOW){
		delay(10);
		if(digitalRead(colPins[2])==LOW){
			delay(10);
			while (!(digitalRead(colPins[2]))){};
			return 2;
		}
	}
	else if (digitalRead(colPins[3])==LOW){
		delay(10);
		if(digitalRead(colPins[3])==LOW){
			delay(10);
			while (!(digitalRead(colPins[3]))){};
			return 3;
		}
	}
	return (4);
}


/****************************************************************
Activating rows and check columns,resulting column-row
params:
row_th : activated row
return:
active column in activated row
****************************************************************/
unsigned char KeyPad::activate_row(unsigned char row_th){
	unsigned char out_clm;
	//DDRF|=0x0F;
	//PORTF=0xFF;
	for(char i=0;i<4;i++){
		digitalWrite(rowPins[i], HIGH);
	}
	digitalWrite(rowPins[row_th],LOW);
	out_clm=check_column();
	return out_clm;
}


/****************************************************************
Reads data from keypad, resulting buttons that has been pushed
return:
Keypad charactes ('#','*','0',...,'9')
****************************************************************/
unsigned char KeyPad::ReadKeypad(){
	unsigned char tmp, get_dt_loop,conter_tmb;
	tmp=4;
	for (conter_tmb=0;conter_tmb<4;conter_tmb++){
		tmp=activate_row(conter_tmb);
		if(tmp<4) return keys[conter_tmb*COLS+tmp];
	}
	if(conter_tmb==4) return 0;
}
