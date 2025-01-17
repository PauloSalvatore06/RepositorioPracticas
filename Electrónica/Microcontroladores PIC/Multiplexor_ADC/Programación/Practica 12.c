/* Pr�ctica 12: Multiplexor de 4 canales anal�gicos
   Paulo Salvatore Partida Escamilla   15300210
   Jose Luis Mar�n Alarc�n             15300157
*/
#include <16F886.h>
#device ADC=10
#use delay(clock=4000000)
#include <lcd1.c>
#fuses intrc_io,nowdt,noput,nomclr,noprotect,nocpd,nobrownout
#fuses noieso,nofcmen,nodebug,nowrt,borv21
#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

void main()
{  
   set_tris_C(0xFF);
   setup_adc(adc_clock_internal);
   setup_adc_ports(sAN0|sAN1|sAN2|sAN3);
   lcd_init();                                                                   //k= (Vin)/(2^n-1)
   Lcd_gotoxy(1,1);
   while(1)
   {  
      int dip=Input_C();
      dip=dip&0x03;                                                             //0000 0011=03;
      set_adc_channel(dip);
      long int Digital=Read_Adc();
      float Analogico=Digital*((5.000/1023.000));
      printf(lcd_putc,"\f \n \f");
      printf (lcd_putc, "Canal:%u Dig:%lu  \nAnalogico:%.2g",dip,Digital,Analogico);
      delay_ms(300);
   }
}
