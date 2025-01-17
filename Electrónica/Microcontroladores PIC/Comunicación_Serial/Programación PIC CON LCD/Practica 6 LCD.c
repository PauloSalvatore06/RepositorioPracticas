/* Pr�ctica 6: Comunicaci�n Serial. PIC CON EL LCD
   Paulo Salvatore Partida Escamilla 15300210
   Miriam Cristina Avi�a Alatorre 15300829
*/
#include <16F886.h>
#use delay(clock=4000000)
#include <lcd1.c>
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,BITS=8)
#fuses intrc_io,nowdt,noput,nomclr,noprotect,nocpd,nobrownout
#fuses noieso,nofcmen,nodebug,nowrt,borv21
#use fast_io(B)
#use fast_io(C)

char Teclapresionada;
#Int_RDA
void RDA_isr()
{
   Teclapresionada=getc();
}

void main()
{
   ENABLE_INTERRUPTS(INT_RDA);
   ENABLE_INTERRUPTS(GLOBAL);
   lcd_init();
   int led;
   while(1)
   {
      lcd_gotoxy(1,1);
      printf (lcd_putc, "Tecla presionada:\n%c                  ",Teclapresionada);
      If (Teclapresionada=='0')
      {led=1;}
      else  
      {led=0;}
      putchar(led);
   }
}


