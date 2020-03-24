#include <Servo.h> // библиотека для серво

//--создаем объекты--//
Servo hvost_d; // первый сервопривод
Servo hvost_b; // второй сервопривод
Servo last_r; // серво для правого ласта
Servo last_l; // серво для левого ласта
//-------------------//

int i; // переменная для вращения хвоста


void setup() {
//--подключение серво к пинам--//
  hvost_d.attach(7);
  hvost_b.attach(8);
  last_r.attach(12);
  last_l.attach(4);
//-----------------------------//
  /* питание от внешнего блока питания */
  
  hvost_d.write(90 + 15);
  hvost_b.write(90 - 15);
  last_r.write(90);
  last_l.write(90);
  
}

void loop() {
  
  for (i = -15; i <= 15; i++) {
    delay(15);
    hvost_b.write(90 + i);
  }
  
   for (i = 15; i >= -15; i--) {
    delay(15);
    hvost_d.write(90 + i);
  }
  
   for (i = -15; i <= 15; i++) {
    delay(15);
    hvost_b.write(90 - i);
  }

  for (i = 0; i <= 15; i++) {
    last_r.write(90 + i);
    last_l.write(90 - i);
    delay(15);
  }

  for (i = 0; i <= 15; i++) {
    last_r.write(105 - i);
    last_l.write(75 + i);
    delay(15);
  }
  
   for (i = 15; i >= -15; i--) {
    delay(15);
    hvost_d.write(90 - i);
  }
}
