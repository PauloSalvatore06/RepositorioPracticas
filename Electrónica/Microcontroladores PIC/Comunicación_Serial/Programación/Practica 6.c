/* Pr�ctica 6: Comunicaci�n Serial. PIC CON EL TECLADO
   Paulo Salvatore Partida Escamilla 15300210
   Miriam Cristina Avi�a Alatorre 15300829
*/
#include <16F886.h>
#use delay(clock=4000000)
#use RS232(BAUD=9600,XMIT=PIN_C6,RCV=PIN_C7,BITS=8)
#fuses intrc_io,nowdt,noput,nomclr,noprotect,nocpd,nobrownout
#fuses noieso,nofcmen,nodebug,nowrt,borv21
#use fast_io(A)
#use fast_io(B)
#use fast_io(C)

int led;
#Int_RDA
void RDA_isr()
{
led=getc();
}

void main()
{  
   ENABLE_INTERRUPTS(INT_RDA);
   ENABLE_INTERRUPTS(GLOBAL);
   set_tris_A(0x00);
   set_tris_B(0x00);
   set_tris_C(0xFF);
   int Activacion[4]= {14,13,11,7},y=0;
   /* 14= 1110
      13= 1101
      11= 1011
      7=  0111*/
   char Tecla;
   long int LecturaConSerial,Lectura;
   
   while (1)
   {
      Output_A(Activacion[y]);
      y=y+1;
      if (y>=4)
         {y=0;}
      delay_ms(20);
      LecturaConSerial=Input_C();
      Lectura=LecturaConSerial&0x0F;
      // 0000 1111=0F
      if (led==1)
      {OUTPUT_HIGH(PIN_B7);}
      else
      {OUTPUT_LOW(PIN_B7);}
      
      switch (y)
      {
         case 0:
            if (Lectura==7)
            {Tecla='1';}
            if (Lectura==11)
            {Tecla='4';}
            if (Lectura==13)
            {Tecla='7';}
            if (Lectura==14)
            {Tecla='*';}
         break;
         case 3:
            if (Lectura==7)
            {Tecla='2';}
            if (Lectura==11)
            {Tecla='5';}
            if (Lectura==13)
            {Tecla='8';}
            if (Lectura==14)
            {Tecla='0';}
         break;
         case 2:
            if (Lectura==7)
            {Tecla='3';}
            if (Lectura==11)
            {Tecla='6';}
            if (Lectura==13)
            {Tecla='9';}
            if (Lectura==14)
            {Tecla='#';}
         break;
         case 1:
            if (Lectura==7)
            {Tecla='A';}
            if (Lectura==11)
            {Tecla='B';}
            if (Lectura==13)
            {Tecla='C';}
            if (Lectura==14)
            {Tecla='D';}
         break;
      }
      putchar(Tecla);
   }
}

