#include "KeyPad.h"

/***************************************************************
Konstruktor dengan beberapa overriding
****************************************************************/
KeyPad::KeyPad(char *_keys,byte _ROWS,byte _COLS,byte *_rowPins,byte *_colPins){
	begin(_keys);
	rowPins = _rowPins;
	colPins = _colPins;
	ROWS = _ROWS;
	COLS = _COLS;
}

/***************************************************************
Deklarasi Pin dan Inisialisasi variabel keys
****************************************************************/
void KeyPad::begin(char *_keys){
	keys = _keys;	
}

/****************************************************************
Polling kolom keypad
return:
0:kolom 0 aktif
1:kolom 1 aktif
2:kolom 2 aktif
3:kolom 3 aktif(untuk keypad 4X4)
4:tidak ada kolom yg aktif
****************************************************************/
unsigned char KeyPad::cek_kolom(){
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
Aktivasi baris,sekaligus cek kolom, menghasilkan kombinasi baris-kolom
params:
row_th :baris yg akan diaktifkan
return:
kolom yg aktif dalam baris yg diaktifkan
****************************************************************/
unsigned char KeyPad::activate_row(unsigned char row_th){
	unsigned char out_clm;
	//DDRF|=0x0F;
	//PORTF=0xFF;
	for(char i=0;i<4;i++){
		digitalWrite(rowPins[i], HIGH);
	}
	digitalWrite(rowPins[row_th],LOW);
	out_clm=cek_kolom();
	return out_clm;
}


/****************************************************************
Membaca data dari keypad, langsung menghasilkan tombol yg dipencet
return:
karakter keypad yg dipencet ('#','*','0',...,'9')
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
