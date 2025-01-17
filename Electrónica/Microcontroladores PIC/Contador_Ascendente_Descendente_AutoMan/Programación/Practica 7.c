/* Pr�ctica 7: Contador ascendente-descendente (autom�tico)
   Paulo Salvatore Partida Escamilla   15300210
   Jose Luis Mar�n Alarc�n             15300157
*/
#include <16F886.h>
#use delay(clock=400000)
#fuses intrc_io,nowdt,noput,nomclr,noprotect,nocpd,nobrownout
#fuses noieso,nofcmen,nodebug,nowrt,borv21

#use fast_io(A)
#use fast_io(B)
#use fast_io(C)
void main()
{
   set_tris_A(0xFF);
   set_tris_B(0x00);
   set_tris_C(0x00);
   signed int  y=0; //Contador
   const int Hexa[16]= {0xFC,0x60,0xDA,0xF2,0x66,0xB6,0xBE,0xE0,0xFF,0xE6,0xEE,0x3E,0x9C,0x7A,0x9E,0x8E};
   /* 0= a,b,c,d,e,f    1111 1100         0xFC
      1=b,c             0110 0000         0x60
      2= a,b,d,e,g=1101 1010=             0xDA
      3=a,b,c,d,g= 1111 0010=             0xF2
      4= b,c,f,g=0110 0110                0x66
      5= a,c,d,f,g= 1011 0110             0xB6
      6= a,c,d,e,f,g=1011 1110            0xBE
      7= a,b,c=1110 0000                  0xE0
      8= a,b,c,d,e,f,g=1111 1111          0xFF
      9= a,b,c,f,g= 1110 0110             0xE6
      A=a,b,c,e,f,g =1110 1110            0xEE
      b=c,d,e,f,g= 0011 1110              0x3E
      C=a,d,e,f= 1001 1100                0x9C
      d= b,c,d,e,g= 0111 1010             0x7A
      E=a,d,e,f,g=1001 1110               0x9E
      F=a,e,f,g= 1000 1110                0x8E
   */
   while(True)
   {
      if (Input(Pin_A0)==1)//Autom�tico
      {
         Output_B(Hexa[y]);
         Output_C(y);
         if (Input(Pin_A1)==0) //Descender
            {
               delay_ms(5000);
               y= y-1;
            if (y<0)
               {y=15;}
            }
         if (Input(Pin_A1)==1) //Ascender
            {
               delay_ms(5000);
               y= y+1;
            if (y>15)
               {y=0;}
            }
      }
      if (Input(Pin_A0)==0) //Manual
      {
         Output_B(Hexa[y]);
         Output_C(y);
         if (Input(Pin_A1)==1) //Ascender
            {
            if (Input(Pin_A7)==1)
               {delay_ms(100);
               y= y+1;}
            while(Input(Pin_A7)==1)
               {}
            if (y>15)
               {y=0;}
            }
         if (Input(Pin_A1)==0) //Descender
            {
            if (Input(Pin_A7)==1)
               {delay_ms(100);
               y= y-1;}
            while(Input(Pin_A7)==1)
               {}
            if (y<0)
               {y=15;}
            } 
     }
   }
}
