//Programa: Teste de Display LCD 16 x 2
//Autor: FILIPEFLOP
#include <Arduino.h>
//Carrega a biblioteca LiquidCrystal
#include <LiquidCrystal.h>
 
//Define os pinos que serão utilizados para ligação ao display
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 
void setup()
{
  //Define o número de colunas e linhas do LCD
  lcd.begin(16, 2);
  pinMode(6,OUTPUT); //DECLARA QUE O PINO 6 É UMA SAÍDA
  pinMode(10,OUTPUT); //Pino do buzzer
  analogWrite(6,50); //ESCREVE O VALOR 50 NA PORTA 6 (CONTROLE DO CONTRASTE VIA PWM)
}
 
void loop()
{
  //Limpa a tela
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(3, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("JUJUISADORA");
  lcd.setCursor(3, 1);
  lcd.print(" LCD 16x2");

    /*tone(10,262,200); //DO
    delay(100);
    tone(10,294,300); //RE
    delay(100);
    tone(10,330,300); //MI
    delay(200);
    tone(10,349,300); //FA
    delay(300);
    tone(10,349,300); //FA
    delay(300);
    tone(10,349,300); //FA
    delay(300);
    tone(10,262,100); //DO
    delay(200);
    tone(10,294,300); //RE
    delay(200);   
    tone(10,262,100); //DO
    delay(200);
    tone(10,294,300); //RE
    delay(300);
    tone(10,294,300); //RE
    delay(300);
    tone(10,294,300); //RE
    delay(300);
    tone(10,262,200); //DO
    delay(200);
    tone(10,392,200); //SOL
    delay(200);
    tone(10,349,200); //FA
    delay(200);
    tone(10,330,300); //MI
    delay(300);
    tone(10,330,300); //MI
    delay(300);
    tone(10,330,300); //MI
    delay(300);
    tone(10,262,200); //DO
    delay(200);
    tone(10,294,300); //RE
    delay(200);
    tone(10,330,300); //MI
    delay(200);
    tone(10,349,300); //FA
    delay(300);
    tone(10,349,300); //FA
    delay(300);
    tone(10,349,300); //FA
    delay(300);*/

  delay(5000);
   
  //Rolagem para a esquerda
  for (int posicao = 0; posicao < 3; posicao++)
  {
    lcd.scrollDisplayLeft();
    delay(300);
  }
   
  //Rolagem para a direita
  for (int posicao = 0; posicao < 6; posicao++)
  {
    lcd.scrollDisplayRight();
    delay(300);
  }
}
