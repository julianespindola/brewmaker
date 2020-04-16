#include <LiquidCrystal.h>
#include <TimerOne.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define pinLcd1 12
#define pinLcd2 11
#define pinLcd3 5
#define pinLcd4 4
#define pinLcd5 3
#define pinLcd6 2
#define pinLcd7 6
#define pinBuzzer 10
#define pinRele1 7 //Porta ligada ao pino IN1 do modulo
#define pinRele2 8 //Porta ligada ao pino IN2 do modulo
#define pinTemperatura 9

// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(pinTemperatura);

DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(pinLcd1, pinLcd2, pinLcd3, pinLcd4, pinLcd5, pinLcd6);
int tempoEmSegundos = 0;
bool alarmeDisparado = false;
int tempoAlarmeAcionado = 0;
int dispararAlameSonoro = 60; // quanto tempo (em segundos) apos alarme acionado será disparado o alarme sonoro
float temperaturaAtual = 0;
float temperaturaMin = 15.00;
float temperaturaMax = 20.00;
char tempoFormatado;

void setup()
{
  Serial.begin(9600);
  sensors.begin();
  Serial.println(sensors.getDeviceCount(), DEC);
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensor nao encontrado ;-( !"); 
  else
    Serial.println("Sensor encontrado :-) !!!!!!"); 
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(pinLcd7,OUTPUT); //DECLARA QUE O PINO 6 É UMA SAÍDA
  pinMode(pinBuzzer,OUTPUT); //Pino do buzzer
  //Define pinos para o rele como saida
  pinMode(pinRele1, OUTPUT); 
  pinMode(pinRele2, OUTPUT);
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
  lcd.print("Mi");
  lcd.setCursor(2, 0); 
  lcd.print(temperaturaMin);
  lcd.setCursor(8, 0); 
  lcd.print("Ma");
  lcd.setCursor(11, 0); 
  lcd.print(temperaturaMax);

  //lcd.setCursor(4, 0);
  //lcd.print(TimeToString(tempoEmSegundos));
  ler_temperatura();
  
  //digitalWrite(pinRele1, LOW);  //Liga rele 1
  //digitalWrite(pinRele1, HIGH); //Desliga rele 1

  delay(1000);
}

void somaTempo()
{
  tempoEmSegundos = tempoEmSegundos + 1;
  if(alarmeDisparado)
  {
    tempoAlarmeAcionado += 1;
  }
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
      /*tone(pinBuzzer, 1000);
      delay(200);
      noTone(pinBuzzer);*/
    }
   sprintf(str, "%04ld:%02d:%02d", h, m, s);
   return str;
}
void ler_temperatura()
{
   sensors.requestTemperatures();
  temperaturaAtual = sensors.getTempC(sensor1);
  
  lcd.setCursor(0, 1);
  lcd.print("TA:");
  lcd.setCursor(4, 1);
  lcd.print(temperaturaAtual); 
  if(temperaturaAtual >= temperaturaMax)
  {
    alarmeDisparado = true;
    lcd.setCursor(10, 1);
    lcd.print("*T Max*");  
    //digitalWrite(pinRele1, LOW);  //Liga rele 1
  }
  else if(temperaturaAtual <= temperaturaMin)
  {
    alarmeDisparado = true;
    lcd.setCursor(10, 1);
    lcd.print("*T Min*");  
    
    //digitalWrite(pinRele1, HIGH);  //Liga rele 1
  }
  else
  {
    alarmeDisparado = false;
    tempoAlarmeAcionado = 0;
  }
  if(tempoAlarmeAcionado>dispararAlameSonoro)
  {
    tone(pinBuzzer, 1000);
    delay(200);
    noTone(pinBuzzer);    
  }
}
