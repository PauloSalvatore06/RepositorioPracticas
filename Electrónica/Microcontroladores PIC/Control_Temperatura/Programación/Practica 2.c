/* Pr�ctica 2: Control de temperatura
   Paulo Salvatore Partida Escamilla   15300210
   Miriam Cristina Avi�a Alatorre      15300829
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
   lcd_init();
   set_tris_A(0xFF);
   set_tris_C(0xFF);
   setup_adc(adc_clock_internal);
   setup_adc_ports(sAN0);
   set_adc_channel(0);
   int Enter=0;
   signed int Decenas=0;
   signed int Unidades=0;
   long int adc;
   float Digital;
   float Temperatura;
   int Setpoint;
   while (1)
   {
   if(Input(Pin_C0)==1)
     {delay_ms(200);
      Enter=Enter+1;}
   while (Input(Pin_C0)==1) {}
   if (Enter>1) {Enter=0;}
   Switch (Enter)
   {case 0:
      if (Input(Pin_C3)==1)
         {Unidades=Unidades-1;
         if (Unidades<0)
            {Unidades=9;}}
      while (Input(Pin_C3)==1) {}
      if (Input(Pin_C4)==1)
         {Unidades=Unidades+1;
         if (Unidades>9)
            {Unidades=0;}}
      while (Input(Pin_C4)==1) {}
      if (Input(Pin_C1)==1)
         {Decenas=Decenas-1;
         if (Decenas<0)
            {Decenas=9;}}
      while (Input(Pin_C1)==1) {}
      if (Input(Pin_C2)==1)
         {Decenas=Decenas+1;
         if (Decenas>9)
            {Decenas=0;}}
      while (Input(Pin_C2)==1) {}
      Lcd_gotoxy(1,1);
      printf (lcd_putc, "Ingrese el valor:\nSetPoint: %u%u C  ",Decenas,Unidades);
      delay_ms(200);
      break;
   case 1:
      adc=Read_Adc();
      Digital= adc*((5.000/1023.000));
      Temperatura=(Digital/0.01);                                                //1�C=10mV
      Setpoint=(Decenas*10)+ Unidades;
      lcd_gotoxy(1,1);
      if (Temperatura< Setpoint)
      {printf (lcd_putc, "Temperatura:%f\nSetpoint:%u T<S", Temperatura,Setpoint);}
      if (Temperatura==Setpoint)
      {printf (lcd_putc, "Temperatura:%f\nSetpoint:%u T=S", Temperatura,Setpoint);}
      if (Temperatura > Setpoint)
      {printf (lcd_putc, "Temperatura:%f\nSetpoint:%u T>S", Temperatura,Setpoint);}
      delay_ms(200);
      break;
   default:
      lcd_gotoxy(1,1);
      printf (lcd_putc, "Errooor         \n \f");
      break;}
   }
}
