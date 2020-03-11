#include <Servo.h> // библиотека для серво
#include <NewPing.h> // библиотека для echo

//--создаем объекты--//
Servo hvost_d; // первый сервопривод
Servo hvost_b; // второй сервопривод
Servo last_r; // серво для правого ласта
Servo last_l; // серво для левого ласта
//-------------------//

//--подключаем echo--//
#define TRIGGER_PIN  2  // пин trig датчика
#define ECHO_PIN     4  // пин echo датчика
#define MAX_DISTANCE 400 // максимальная дистанция echo
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
//-------------------//

int i; // переменная для вращения хвоста
int angle; // переменная угла поворота ласт

ISR(TIMER0_COMPA_vect) { // функция прерывания(каждую мс)
  if (Serial.available() > 0) { // условие поворота ласт
    angle = Serial.parseInt();
    last_r.write(90 + angle);
    last_l.write(90 + angle);
    delay(1000); // ласты будут стоять 1 с
    angle = 0;
    last_r.write(90 + angle);
    last_l.write(90 + angle);
    Serial.flush(); // очищаем буфер порта
  }
}

void setup() {
//--подключение серво к пинам--//
  hvost_d.attach(7);
  hvost_b.attach(8);
  last_r.attach(12);
  last_l.attach(5);
//-----------------------------//
  /* питание от внешнего блока питания */
  Serial.begin(9600); // монитор порта
//--настройка прерывания по таймеру--//  
  TCCR0A |= (1 << WGM01);
  OCR0A = 0xF9;
  TIMSK0 |= (1 << OCIE0A);
  TCCR0B |= (1 << CS01) | (1 << CS00);
  sei();
//-----------------------------------//

  hvost_d.write(90 + 15);
  hvost_b.write(90 - 15);
  last_r.write(90);
  last_l.write(90);

}

void loop() {
  for (i = -15; i <= 15; i++) {
    hvost_b.write(90 + i);
    delay(rost());
  }
  
   for (i = 15; i >= -15; i--) {
    hvost_d.write(90 + i);
    delay(rost());
  }
  
   for (i = -15; i <= 15; i++) {
    hvost_b.write(90 - i);
    delay(rost());
  }
  
   for (i = 15; i >= -15; i--) {
    hvost_d.write(90 - i);
    delay(rost());
  }
}

//--функции, используемые в коде--//

int rost() { // функция, возращающая нужную задержку для серво
  int a; // возвращаемая переменная
  unsigned int distance = sonar.ping_cm(); // сохраняем в переменную дистанцию
  
  Serial.print("disttance "); 
  Serial.println(distance);   // выводим дистанцию в порт

  if (distance < 100) { // изменяем задержку в зависимости от растояния
    a = 10;
  } else if (distance < 150) {
    a = 15;
  } else if (distance < 200) {
    a = 20;
  } else if (distance < 250) {
    a = 25;
  } else if (distance < 300) {
    a = 30;
  }
  return a;
}
