#ifndef LCD_H
#define	LCD_H

void lcd_cmd(uint8_t);
void lcd_init(void);
void lcd_clear(void);
void lcd_putc(uint8_t data);
void lcd_puts(const uint8_t* buf);

#endif	/* LCD_H */

