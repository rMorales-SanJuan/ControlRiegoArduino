# ControlRiegoArduino
Prototipo Escalable de Sistema Básico de Control de Micro Riego (en Contexto Rural Aislado)

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
