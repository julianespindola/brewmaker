#include <LiquidCrystal.h>
#include <TimerOne.h>

#define pinLcd1 12
#define pinLcd2 11
#define pinLcd3 5
#define pinLcd4 4
#define pinLcd5 3
#define pinLcd6 2
#define pinLcd7 6
#define pinBuzzer 10

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(pinLcd1, pinLcd2, pinLcd3, pinLcd4, pinLcd5, pinLcd6);
int tempoEmSegundos = 0;
char tempoFormatado;

void setup()
{
  Serial.begin(9600);
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(pinLcd7,OUTPUT); //DECLARA QUE O PINO 6 É UMA SAÍDA
  pinMode(pinBuzzer,OUTPUT); //Pino do buzzer
  analogWrite(6,50); //ESCREVE O VALOR 50 NA PORTA 6 (CONTROLE DO CONTRASTE VIA PWM)
  Timer1.initialize(1000000);
  Timer1.attachInterrupt(somaTempo);
}

void loop()
{
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(0, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("R1:");
  lcd.setCursor(4, 0);
  lcd.print(TimeToString(tempoEmSegundos));
  lcd.setCursor(0, 1);
  //lcd.print("Mostura " + (char)tempoEmSegundos + "| Temp: 20C°");
  lcd.print("T1:");
  lcd.setCursor(4, 1);
  lcd.print("68C");  
  lcd.setCursor(8, 1);
  lcd.print("TA:");  
  lcd.setCursor(12, 1);
  lcd.print("67C");

  delay(1000);
}

void somaTempo()
{
  tempoEmSegundos = tempoEmSegundos + 1;
}

char * TimeToString(unsigned long t)
{
   static char str[12];
   long h = t / 3600;
   t = t % 3600;
   int m = t / 60;
   int s = t % 60;
   if(s<1)
    {
      tone(pinBuzzer, 1000);
      delay(200);
      noTone(pinBuzzer);
    }
   sprintf(str, "%04ld:%02d:%02d", h, m, s);
   return str;
}
