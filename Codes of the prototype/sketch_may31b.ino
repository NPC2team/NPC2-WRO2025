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
// notas para saber que colores vimos 
bool vioAzul = false;              // ¿pregunta si ya vimos azul
bool vioNaranja = false;           // ↑
bool vueltaRegistrada = false;     // ↑

// reloj para saber cuanto tiempo llevamos sin ver un color
unsigned long tiempoUltimoColor = 0;       
const unsigned long pausaSinColor = 3000;  // espera 3 segundos sin colores para contar la nueva vuelta

void setup() {
  Serial.begin(115200);        // deja ver en la compu
  pixy.init();                 //"prende" la pixy

  // dice a la esp32 que estos son los pines para enviar energia al motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // conexion de servo
  steeringServo.attach(18);
  steeringServo.write(90);    // recto

  moverAdelante();            // se mueve para adelante
}

void loop() {
  pixy.ccc.getBlocks();       // la pixy dice que colores esta viendo 

  if (pixy.ccc.numBlocks > 0) {  // si la pixy esta viendo algun color

    uint8_t signature = pixy.ccc.blocks[0].m_signature; // para que agarre el primero que se ve 

    tiempoUltimoColor = millis(); // guarda en que momento vio el ultimo color

    if (signature == 1) {         // si ese fue azul (1)
      girarIzquierda();           // va a izquierda
      delay(1000);                // espera 1 seg mientras gira 
      steeringServo.write(90);   // se pone recto de nuevo
      moverAdelante();           // seguimos para adelante 
      vioAzul = true;            // resalta que vio azul
    }

    else if (signature == 2) {   // si fue naranja(2)
      girarDerecha();            // gira a la derecha 
      delay(1000);               
      steeringServo.write(90);   // se pone recto de nuevo
      moverAdelante();           // sigue para adelante

      if (vioAzul) {             // Si ya habíamos visto azul
        vioNaranja = true;       // resaltamos que ahora vemos naranja
      }
    }

    // si vimos azul y luego naranja ya podemos contar la vuelta
    if (vioAzul && vioNaranja) {
      vueltaRegistrada = true;   // dice que contamos la vuelta
    }

  } else { // si no vemos ningun color ahorita

    // si ya vimos azul y naranja y pasaron mas de 3 segundos sin ver colores
    if (vueltaRegistrada && millis() - tiempoUltimoColor > pausaSinColor) {
      vueltas++;                    // suma una vuelta
      Serial.print("Vueltas: ");    // muestra cuantas llevamos
      Serial.println(vueltas);

      // borramos todo lo que vimos para que no se confunda con la proxima vuelta
      vioAzul = false;
      vioNaranja = false;
      vueltaRegistrada = false;
    }
  }

  // si el carro ya dio 3 vueltas
  if (vueltas >= 3) {
    detener();              // para el motor por siempre
    while (true);           
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