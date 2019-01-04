#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <SoftwareSerial.h>

SoftwareSerial bt(10, 11); // RX | TX
LiquidCrystal_I2C lcd (0x27, 16, 2);

// Pines para el motor
int IN3=7;
int IN4=6;
int ENB=5;

int contador = 0;

const int sensorPin = A0; // Salida analogica del sensor de humedad

void setup(){

  Serial.begin(9600);
  
  // Para la pantalla
  Wire.begin();
  lcd.begin(16,2); // Definimos que es un LCD de 16x2
  lcd.backlight(); // Enciende la luz
  lcd.clear(); // limpiamos la pantalla

  // Para el motor
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Para el bluetooth
  bt.begin(9600); // activamos el serial del bluetooth
  pinMode(9, OUTPUT); // activamos el modulo bluetooth mediante el pin 9 del arduino
  digitalWrite(9,HIGH);

}

void pantalla(int humedad) {
  
  lcd.clear();
  lcd.setCursor(0, 0); // Inicia un LCD 16x02 (columnas,fila)
  lcd.print("H: "); 
  lcd.print(humedad); // Escribe el LCD
  lcd.setCursor(8, 0);
  lcd.print("S: ");
  
  if(humedad > 600){
    lcd.print("NOK");
  }
  else{
    lcd.print("OK");
  }
  lcd.setCursor(0, 1); // Ponemos el cursor en la segunda Fila
  lcd.print("Regado: ");
  lcd.print(contador);
  
}

void apagado_motor(){ 
  
// Funcion para que el motor pare
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
  
  analogWrite(ENB,150); 

}

void encencido_motor(){ 
  
// Funcion para que el motor se encienda
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  
  analogWrite(ENB,150);
 
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 0);
  lcd.print("REGANDO!!!");

  lcd.setCursor(0,1);
  
  delay(2000); // Regamos durante 2 segundos
  
  lcd.clear();
  
  apagado_motor();
  
  contador++;
  
}


void humedad_suelo(int humedad) {
  
  if(humedad > 600){ // salida analogica
   
    encencido_motor();

  }
  
  pantalla(humedad);
  
  delay(30000); // Esperamos 30 segundos antes de volver a medir la humedad
  
}

void loop()
{
  int humedad = analogRead(sensorPin);
  humedad_suelo(humedad);
  
  Serial.println(humedad);
  bt.println(String(humedad));
  
  delay(2000);

}
