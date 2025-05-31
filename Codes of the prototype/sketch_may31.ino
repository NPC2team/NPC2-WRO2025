#include <SPI.h>         // libreria para que la pixy hable con el esp32
#include <Pixy2.h>       // libreria de pixy
#include <Servo.h>       // libreria de servo

Pixy2 pixy;// creamos el objeto "pixy"para nombrar/usar la camara
Servo steeringServo;// otro para el servo

// aqui que pines se usan para que el motor mueva el carro
const int ENA = 19;   // esto controla velocidad
const int IN1 = 21;   // este si va para adelante 
const int IN2 = 22;   // y este si va para atras (aunque no lo usaremos para eso)

// contador de vueltas
int vueltas = 0;

// esto es como un failsafe para no contar la misma vuelta dos veces 
bool vueltaRegistrada = false;

void setup() {
  Serial.begin(115200);   // para ver los mensajes en la compu

  pixy.init();            // para prender la pixy
  // pines que mandan energia 
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // para decirle al servo en que pin esta conectado
  steeringServo.attach(18);
  steeringServo.write(90);   // para ponerlo recto

  moverAdelante();  // para que empiece a moverse adelante
}

void loop() {
  pixy.ccc.getBlocks();   // le pedimos que nos diga si vio colores que estan en signatures 

  if (pixy.ccc.numBlocks) {   // si la cam ve algo
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {  // esto es para que lo repita por cada bloque de color que vio 
      uint8_t signature = pixy.ccc.blocks[i].m_signature;  // aqui distinguimos cual es (azul1 naranja2)

      if (signature == 1) {  // si es azul
        girarIzquierda();    // el servo va para la derecha 
        delay(1000);         // esperamos 1 segundo 
        steeringServo.write(90);  // devuelve el servo a recto
        moverAdelante();     // pa que se mueva recto
      } 
      else if (signature == 2) {  // si es naranja
        girarDerecha();      // servo gira para la derecha
        delay(1000);         // esperamos 1 segundo
        steeringServo.write(90);  // servo vuelve al centro
        moverAdelante();     // sigue recto
      }

      // para ver si ya paso por el punto de partida
      static bool vioAzul = false;      // guarda si ya vio azul
      static bool vioNaranja = false;   // guarda si luego vio naranja

      if (signature == 1) vioAzul = true;               // si ve azul lo anota
      if (signature == 2 && vioAzul) vioNaranja = true; // si ve naranja lo anota

      // si vio azul despues naranja y no contamos esa vuelta
      if (vioAzul && vioNaranja && !vueltaRegistrada) {
        vueltas++;                     // contamos una vuelta mas
        Serial.print("Vueltas: ");     //muestra el no de vueltas por la computadora
        Serial.println(vueltas);
        vueltaRegistrada = true;       // ya contamos esta vuelta
        vioAzul = false;               // reiniciamos para buscar la siguiente vuelta
        vioNaranja = false;
      }

      // si no ve ninguno de los dos colores limpiamos los registros
      if (signature != 1 && signature != 2) {
        vioAzul = false;
        vioNaranja = false;
      }
    }
  } else {
    vueltaRegistrada = false;   // si no ve nada dejamos contar la próxima vuelta
  }

  if (vueltas >= 3) {    // si ya dio 3 vueltas
    detener();           // apaga el motor
    while (true);        // para forever
  }
}

// funcion para que avance
void moverAdelante() {
  digitalWrite(IN1, HIGH);    // para que gire adelante 
  digitalWrite(IN2, LOW);     // decir que no queremos que gire al reves 
  analogWrite(ENA, 150);      // velocidad que esta en 150
}

// detiene completamente el motor
void detener() {
  analogWrite(ENA, 0);        // pone la velocidad en 0
  digitalWrite(IN1, LOW);     // apaga el motor
  digitalWrite(IN2, LOW);
}

// gira el servo a la izquierda
void girarIzquierda() {
  steeringServo.write(45);   
}

// gira el servo a la derecha
void girarDerecha() {
  steeringServo.write(135);  
}