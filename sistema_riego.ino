#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int MotorDer1=7;
int MotorDer2=8;
int PWM_Derecho=10;
int contador = 0;

LiquidCrystal_I2C lcd (0x27, 16, 2);

const int sensorPin = A0; // Salida analogica del sensor de humedad

void setup(){

  Serial.begin(9600); 
  Wire.begin();
  lcd.begin(16,2); // Definimos que es un LCD de 16x2
  lcd.backlight(); // Enciende la luz
  lcd.clear(); // limpiamos la pantalla

  pinMode(MotorDer1, OUTPUT);
  pinMode(MotorDer2, OUTPUT);
  pinMode(PWM_Derecho, OUTPUT);

}

void pantalla(int humedad) {
  
  lcd.clear();
  lcd.setCursor(0, 0); // Inicia un LCD 16x02 (columnas,fila)
  lcd.print("H: "); 
  lcd.print(humedad); // Escribe el LCD
  lcd.setCursor(8, 0);
  lcd.print("S: ");
  
  if(humedad > 500){
    lcd.print("NOK");
  }
  else{
    lcd.print("OK");
  }
  lcd.setCursor(0, 1); // Ponemos el cursor en la segunda Fila
  lcd.print("Contador: ");
  lcd.print(contador);
  
}

void apagado_motor(){ 
/* Funcion para que el motor pare */
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,LOW);
  
  analogWrite(PWM_Derecho,150); 

}

void encencido_motor(){ 
/* Funcion para que el motor se encienda */
  digitalWrite(MotorDer1,LOW);
  digitalWrite(MotorDer2,HIGH);
  
  analogWrite(PWM_Derecho,150);
 
  lcd.setCursor(0, 0);
  lcd.print("               ");
  lcd.setCursor(0, 0);
  lcd.print("REGANDO!!!");

  lcd.setCursor(0,1);
  
  delay(6000); // Regamos durante 6 segundos
  
  lcd.clear();
  
  apagado_motor();
  
  contador++;
  
}


void humedad_suelo(int humedad) {
  
  int humedad = analogRead(sensorPin);

  if(humedad > 500){ // salida analogica
   
    encencido_motor();

  }
  
  pantalla(humedad);
  delay(10000); // Esperamos 10 segundos antes de volver a medir la humedad
  
}


void loop()
{
//  int humedad = analogRead(sensorPin);
  humedad_suelo(humedad);

}
