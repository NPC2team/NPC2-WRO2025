#include <Pixy2.h>     // Librería de Pixy2
#include <SPI.h>       // Librería de comunicación SPI que es un protocolo de comunicación para dispositivos como microcontroladores que utiliza cuatro cables para una rápida transferencia de datos
#include <Servo.h>     // Librería del servo like a boss

// pedimos de  manera  amable la Pixy2 en modo SPI
Pixy2 pixy(Pixy2::SPI);
Servo servoMotor;

// Pines para el servo y motor que esta conectado al puente H
const int SERVO_PIN      = 9;   // Pin del servo

// Pines del motor IN3 que siempre  va en High siguiendo el código de Cesar y IN4 en Low. Todo esto si no mal recuerdo
const int MOTOR_ENABLE   = 3;   // Pin EN (PWM)
const int MOTOR_IN4      = 4;   // Pin IN4
const int MOTOR_IN3      = 5;   // Pin IN3

// Posiciones (en grados) para el servo
const int CENTRO    = 90;        // Posición central del servo
const int DERECHA   = 135;       // Ángulo para giro a la derecha que usaremos para firma 2 que es azul
const int IZQUIERDA = 45;        // Ángulo para giro a la izquierda que usaremos para firma 1  naranja 

// Parámetros de acción
const unsigned long DELAY_GIRO = 1000;  // Tiempo (ms) de mantenimiento del giro
const int MOTOR_SPEED = 165;                // Velocidad del motor que puede ir desde 0 a 255

// Funciones para controlar el motor
void moveForward(int speed) {
  // Para avanzar: IN3 en HIGH y IN4 en LOW
  digitalWrite(MOTOR_IN3, HIGH);
  digitalWrite(MOTOR_IN4, LOW);
  analogWrite(MOTOR_ENABLE, speed);
}

void stopMotor() {
  analogWrite(MOTOR_ENABLE, 0);
}

void setup() {
  Serial.begin(115200);
  
  // Iniciamos la Pixy2 en modo SPI como hizo el profe
  pixy.init();

  // Inicialización del servo y lo colocamos en  90º como pusimo arriva
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(CENTRO);

  // Configurar pines del motor
  pinMode(MOTOR_ENABLE, OUTPUT);
  pinMode(MOTOR_IN4, OUTPUT);
  pinMode(MOTOR_IN3, OUTPUT);

  // Arrancar el motor en movimiento hacia adelante
  moveForward(MOTOR_SPEED);
  
  Serial.println("Sistema iniciado. Carro en movimiento y esperando detección de línea de color...");
}


}

void loop() {
  //muchachos primero  usaremos mi idea de las lineas like a boss  y  por eso haremos el contador de las lineas
  static int turnCounter = 0;//por eso esto
  //y como no se si hay un while en C++ entonces vamos, olvidalo acabo de  ver que hay pero voy a intentar con un if, por  cierto Leo no usaremos el delay  10000
  if (turnCounter < 12) {
    pixy.ccc.getBlocks();//le pedimos imagen a pixy

    if (pixy.ccc.numBlocks > 0) {
      Serial.print("Bloques detectados: ");
      Serial.println(pixy.ccc.numBlocks);
      //usaremos un for para  ver la informacion de cada bloque like a boss
      for (int i = 0; i < pixy.ccc.numBlocks; i++) {
        Serial.print("Bloque #");
        Serial.print(i + 1);
        Serial.print(" | Firma: ");
        Serial.println(pixy.ccc.blocks[i].m_signature);
      }
      //ahora que detecte el color con los signatures guardados
      int signature = pixy.ccc.blocks[0].m_signature;
      //vamos a para el  motor para que haga el giro, creo que es buena idea  aunque esto se  puede cambiar si queremos agilizar más
      stopMotor()
      //ahora  usamos los if de  cada signatures es decir color, like a boss
      if (signature == 1) {  //firma 1 significa color naranja
        Serial.println("→ NARANJA detectado: moviendo servo a la DERECHA.");
        servoMotor.write(DERECHA);
      }
      else if (signature == 2) {  // firma 2 significa color azul
        Serial.println("→ AZUL detectado: moviendo servo a la IZQUIERDA.");
        servoMotor.write(IZQUIERDA);

      // Se mantiene la posición del servo en estos giros por esta variable
      delay(DELAY_GIRO);
      //vuelve al centro el servo 
      servoMotor.write(CENTRO);
      //y se suma 1 al contador
      turnCounter++;
      Serial.print("Giros ejecutados: ");
      Serial.println(turnCounter);
      //y seguimos con el movimiento :)
      moveForward(MOTOR_SPEED);
      //un delay para que no agarre lecturas repetidas
      delay(500);
    }
    //pausa para medir siguiente color
    delay(100)
  }
  else {
    // Cuando se han ejecutado los 12 giros (3 vueltas completas), se detiene el sistema.
    stopMotor();
    servoMotor.write(CENTRO);
    Serial.println("¡Se completaron las 3 vueltas (12 giros)! Fin de la ejecución.");
    
    // Se detiene la ejecución del loop (while true bloqueado)
    while (true) {
      delay(1000);
    }
  }
}
