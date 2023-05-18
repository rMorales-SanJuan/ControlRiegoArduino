/* ******** Prototipo Escalable de Sistema Básico de ********
   *** Control de Micro Riego (en Contexto Rural Aislado) ***

  Versión: 1.1.5
  Actualizado: jueves 18/05/2023 (02:15)

  Autor: Ricardo M. Morales
  Pocito, San Juan, Argentina
  E-Mail: rmorales.unlar@gmail.com

  Descripción: permite regular agua de riego, mediante sensores de humedad de
    suelo, con los que se controlan minibombas de agua, para riego localizado.

  Configuración actual:
    2 sensores de humedad con control de 2 bombas de agua mediante relés.

  Sugerencias:
    Utilizar fuente separada para relés y bombas, con interconexión de neutros (masa).
    Puede adaptarse a diferentes cantidades y capacidades de sensores y bombas,
      cuidando los consumos de cada elemento.

  Desarrollado con:
    - Ubuntu Mate 22.04.2 LTS (Jammy Jellyfish) de 64 bits
    - Huayra 5.0 (y 6.0 beta)
    - Arduino IDE 2.1.0 (AppImage para GNU/Linux)
    - Librería LiquidCrystal_I2C 1.1.2

  Probado con:
    - Arduino UNO R3
    - Arduino Mega 2560 R3

  Licencia: GNU GPL v3 (Licencia Pública General de GNU)
            https://www.gnu.org/licenses/gpl-3.0.html

*/

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C pantalla(0x27,20,4); // Pantalla LCD

const int EsperaInicial    = 2000; // Espera inicial, por cartel de activación
const int EsperaIntermedia = 2000; // Espera intermedia, entre ciclos de procesamiento

int ValEncender = 35;
int ValApagar   = 40;

int sensorHumedad_1 = A1; //sensor de humedad 1
int sensorHumedad_2 = A2; //sensor de humedad 2
int bomba_1 = 7;          //bomba de agua 1
int bomba_2 = 6;          //bomba de agua 2

void setup() {
  Serial.begin(9600);
  pinMode(bomba_1,OUTPUT);   // inicialización bombas
  pinMode(bomba_2,OUTPUT);
  digitalWrite(bomba_1,LOW);
  digitalWrite(bomba_2,LOW);
  pantalla.init();           // inicialización pantalla
  pantalla.init();
  pantalla.backlight();
  pantalla.print("Control de Riego");
  Serial.println("Iniciando Control de Riego...");
  delay(EsperaInicial);
}

void loop() {
  // Lectura humedad suelo (ambnos sensores)
  int humedad_suelo_1 = analogRead(sensorHumedad_1);
  int humedad_suelo_2 = analogRead(sensorHumedad_2);
  // conversión/mapeo de lecturas
  int porcentaje_humedad_1 = map(humedad_suelo_1, 0, 1023, 100, 0);
  int porcentaje_humedad_2 = map(humedad_suelo_2, 0, 1023, 100, 0);
  // muestra en terminal
  Serial.print("Humedad del suelo medida: ");
  Serial.print(porcentaje_humedad_1);
  Serial.print(" ");
  Serial.print(humedad_suelo_1);
  Serial.print(" - ");
  Serial.print(porcentaje_humedad_2);
  Serial.print(" ");
  Serial.println(humedad_suelo_2);
  // muestra en LCD
  pantalla.clear();
  pantalla.setCursor(0, 0);
  pantalla.print("Humedad del Suelo:");
  pantalla.setCursor(12, 1); // Valores de Humedad
  pantalla.print(porcentaje_humedad_1);
  pantalla.setCursor(16, 1);
  pantalla.print(humedad_suelo_1);
  pantalla.setCursor(12, 2);
  pantalla.print(porcentaje_humedad_2);
  pantalla.setCursor(16, 2);
  pantalla.print(humedad_suelo_2);
  // Verificación de Rangos (habilitar/suspender riego)
  if(porcentaje_humedad_1 < ValEncender){ // Bomba 1
    digitalWrite(bomba_1,HIGH);
    pantalla.setCursor(0, 1);
    pantalla.print(" Regando >");
    pantalla.setCursor(5, 3);
    pantalla.print("*1*");
  }else if(porcentaje_humedad_1 > ValApagar){
    digitalWrite(bomba_1,LOW);
    pantalla.setCursor(0, 2);
    pantalla.print("          ");
    pantalla.setCursor(5, 3);
    pantalla.print("   ");
  }
  if(porcentaje_humedad_2 < ValEncender){ // Bomba 2
    digitalWrite(bomba_2,HIGH);
    pantalla.setCursor(0, 2);
    pantalla.print(" Regando >");
    pantalla.setCursor(10, 3);
    pantalla.print("*2*");
  }else if(porcentaje_humedad_2 > ValApagar){
    digitalWrite(bomba_2,LOW);
    pantalla.setCursor(0, 2);
    pantalla.print("          ");
    pantalla.setCursor(10, 3);
    pantalla.print("   ");
  }
  delay(EsperaIntermedia);
}
