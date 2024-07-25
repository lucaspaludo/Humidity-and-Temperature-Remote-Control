#include <LiquidCrystal.h>

//entrada
#define pino_sinal_analogico A0

//saídas
#define pino_led_vermelho 5
#define pino_led_amarelo 6
#define pino_led_verde 7
#define pino_buzzer 3
#define pino_bomba 13

//portas do display LCD
#define RS 12
#define EN 4
#define D4 8
#define D5 9
#define D6 10
#define D7 11

//instancia objeto lcd do tipo LiquidCrystal
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

//valor da umidade
int valor_analogico;
bool flag = false;


void setup() {
  Serial.begin(9600);
  
  //inicia entradas e saídas
  pinMode(pino_sinal_analogico, INPUT);
  pinMode(pino_led_vermelho, OUTPUT);
  pinMode(pino_led_amarelo, OUTPUT);
  pinMode(pino_led_verde, OUTPUT);
  pinMode(pino_bomba, OUTPUT);
  pinMode(pino_buzzer, OUTPUT);
  
  //inicia display LCD de 16 colunas e 2 linhas
  lcd.begin(16, 2); 
}


void loop() {

  //Le o valor do pino A0 do sensor
  valor_analogico = analogRead(pino_sinal_analogico);

  //limpa o display
  lcd.clear();   

  //Mostra o valor da porta analogica no serial monitor
  Serial.print("Porta analogica: ");
  Serial.print(valor_analogico);  

    //Solo umido, acende o led verde, imprime do display, no monitor serial e no celular
  if (valor_analogico >= 0 && valor_analogico < 450)
  {

    Serial.println(" Status: Solo umido");
    apagaleds();
    digitalWrite(pino_led_verde, HIGH);
    lcd.print("UMIDADE BOA");
    flag = false;
    digitalWrite(pino_bomba, HIGH);
    
  }
 
  //Solo com umidade moderada, acende led amarelo, imprime do display, no monitor serial e no celular
  if (valor_analogico >= 450 && valor_analogico < 600)
  {
 
    Serial.println(" Status: Umidade moderada");
    apagaleds();
    digitalWrite(pino_led_amarelo, HIGH);
    lcd.print("UMIDADE MODERADA");
    chamaBomba();
 
  }
 
  //Solo seco, acende led vermelho, imprime do display, no monitor serial e no celular
  if (valor_analogico >= 600 && valor_analogico <= 1024)
  {

    Serial.println(" Status: Solo seco");
    apagaleds();
    digitalWrite(pino_led_vermelho, HIGH);
    lcd.print("UMIDADE BAIXA");
    chamaBomba();
   
  }
  delay(100);
}
 
void apagaleds()
{
  digitalWrite(pino_led_vermelho, LOW);
  digitalWrite(pino_led_amarelo, LOW);
  digitalWrite(pino_led_verde, LOW);
}

void chamaBomba()
{
  if (!flag) {
      digitalWrite(pino_buzzer, HIGH);
      delay(500);
      digitalWrite(pino_buzzer, LOW);
      flag = true; 
    }

  digitalWrite(pino_bomba, LOW);

}
