#ifndef _KEYPAD_H_
#define _KEYPAD_H_
#include<Arduino.h>
#define buatKeymap(x) ((char*)x)

class KeyPad{
	public:
	KeyPad(char *_keys, byte _ROWS, byte _COLS, byte *_rowPins, byte *_colPins);
	
	void begin(char *_keys);
	unsigned char cek_kolom();
	unsigned char activate_row(unsigned char row_th);
	unsigned char ReadKeypad();

	private:
	char *keys;
	byte *rowPins;
	byte *colPins;
	byte ROWS;
	byte COLS;
};
#endif
