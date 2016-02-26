#ifndef LCD_H_
#define LCD_H_

#define LCD_Y 2		// iloœæ wierszy wyœwietlacza LCD
#define LCD_X 16	// iloœæ kolumn wyœwietlacza LCD

#define USE_RW 1    //nie podlaczone do masy tylko do mikroproc - opisalem na kartkach - szybciej dziala itd...


#define LCD_D7PORT  A // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D7 1      // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D6PORT  A //ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D6 2      // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D5PORT  A // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D5 3      // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D4PORT  A // ustawiam tutaj piny i port przez posrednie zminne
#define LCD_D4 4      // ustawiam tutaj piny i port przez posrednie zminne



#define LCD_RSPORT A
#define LCD_RS 7

#define LCD_RWPORT A
#define LCD_RW 6

#define LCD_EPORT A
#define LCD_E 5


#define USE_LCD_LOCATE	1			// ustawia kursor na wybranej pozycji Y,X (Y=0-3, X=0-n)

#define USE_LCD_CHAR 	1			// wysy³a pojedynczy znak jako argument funkcji

#define USE_LCD_STR_P 	1			// wysy³a string umieszczony w pamiêci FLASH
#define USE_LCD_STR_E 	1			// wysy³a string umieszczony w pamiêci FLASH

#define USE_LCD_INT 	1			// wyœwietla liczbê dziesietn¹ na LCD
#define USE_LCD_HEX 	0			// wyœwietla liczbê szesnastkow¹ na LCD

#define USE_LCD_DEFCHAR		1		// wysy³a zdefiniowany znak z pamiêci RAM
#define USE_LCD_DEFCHAR_P 	1		// wysy³a zdefiniowany znak z pamiêci FLASH
#define USE_LCD_DEFCHAR_E 	1		// wysy³a zdefiniowany znak z pamiêci EEPROM

#define USE_LCD_CURSOR_ON 		0	// obs³uga w³¹czania/wy³¹czania kursora
#define USE_LCD_CURSOR_BLINK 	0	// obs³uga w³¹czania/wy³¹czania migania kursora
#define USE_LCD_CURSOR_HOME 	0	// ustawia kursor na pozycji pocz¹tkowej


#if ( (LCD_Y == 4) && (LCD_X == 16) )
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x28		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x14  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x54  	// adres 1 znaku 4 wiersza
#else
#define LCD_LINE1 0x00		// adres 1 znaku 1 wiersza
#define LCD_LINE2 0x40		// adres 1 znaku 2 wiersza
#define LCD_LINE3 0x10  	// adres 1 znaku 3 wiersza
#define LCD_LINE4 0x50  	// adres 1 znaku 4 wiersza
#endif


#define PORT(x) SPORT(x)
#define SPORT(x) (PORT##x)
// *** PIN
#define PIN(x) SPIN(x)
#define SPIN(x) (PIN##x)
// *** DDR
#define DDR(x) SDDR(x)
#define SDDR(x) (DDR##x)

///////////////////definicje stalych z tabelki

#define LCDC_CLS					0x01
#define LCDC_HOME					0x02
#define LCDC_ENTRY					0x04
	#define LCDC_ENTRYR					0x02
	#define LCDC_ENTRYL					0
	#define LCDC_MOVE					0x01
#define LCDC_ONOFF					0x08
	#define LCDC_DISPLAYON				0x04
	#define LCDC_CURSORON				0x02
	#define LCDC_CURSOROFF				0
	#define LCDC_BLINKON				0x01
#define LCDC_SHIFT					0x10
	#define LCDC_SHIFTDISP				0x08
	#define LCDC_SHIFTR					0x04
	#define LCDC_SHIFTL					0
#define LCDC_FUNC					0x20
	#define LCDC_FUNC8B					0x10
	#define LCDC_FUNC4B					0
	#define LCDC_FUNC2L					0x08
	#define LCDC_FUNC1L					0
	#define LCDC_FUNC5x10				0x04
	#define LCDC_FUNC5x7				0
#define LCDC_SET_CGRAM				0x40
#define LCDC_SET_DDRAM				0x80

/////////////deklaracje funkcji
void lcd_init(void);
void lcd_cls(void);	
void lcd_str(char * str); //pobiera argument funkcji w postaci str i zapisuje na wyswietlaczu


void lcd_locate(uint8_t y, uint8_t x);

void lcd_char(char c);		
void lcd_str_P(char * str);	
void lcd_str_E(char * str);	
void lcd_int(int val);
void lcd_hex(int val);
void lcd_defchar(uint8_t nr, uint8_t *def_znak);
void lcd_defchar_P(uint8_t nr, uint8_t *def_znak);
void lcd_defchar_E(uint8_t nr, uint8_t *def_znak);

void lcd_home(void);
void lcd_cursor_on(void);
void lcd_cursor_off(void);
void lcd_blink_on(void);
void lcd_blink_off(void);

#endif
