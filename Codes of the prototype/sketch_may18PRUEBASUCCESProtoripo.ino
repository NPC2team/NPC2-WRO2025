#include <Pixy2.h>
#include <SPI.h>
#include <ESP32Servo.h>


// Pedimos de manera amable la Pixy2 en modo SPI
Pixy2 pixy;
Servo servoMotor;

// Pines para el servo y motor conectado al puente H
const int SERVO_PIN = 27;  // Pin del servo
const int MOTOR_ENABLE = 12; // Pin EN (PWM)
const int MOTOR_IN4 = 14; // Pin IN4
const int MOTOR_IN3 = 13; // Pin IN3

// Posiciones (en grados) para el servo
const int CENTRO = 90;
const int DERECHA = 135; // Ángulo para giro a la derecha
const int IZQUIERDA = 45; // Ángulo para giro a la izquierda

// Parámetros de acción
const unsigned long DELAY_GIRO = 850;
const int MOTOR_SPEED = 165;

// Funciones para controlar el motor
void moveForward(int speed) {
    digitalWrite(MOTOR_IN3, HIGH);
    digitalWrite(MOTOR_IN4, LOW);
    analogWrite(MOTOR_ENABLE, speed);
}

void stopMotor() {
    analogWrite(MOTOR_ENABLE, 0);
}

void setup() {
    Serial.begin(115200);

    // Iniciamos la Pixy2 en modo SPI
    pixy.init();

    // Inicialización del servo y lo colocamos en 90º
    servoMotor.attach(SERVO_PIN);
    servoMotor.write(CENTRO);

    // Configurar pines del motor
    pinMode(MOTOR_ENABLE, OUTPUT);
    pinMode(MOTOR_IN4, OUTPUT);
    pinMode(MOTOR_IN3, OUTPUT);

    // Arrancar el motor en movimiento hacia adelante
    Serial.println("Sistema iniciado. Carro en movimiento y esperando detección de línea de color...");
}

void loop() {
    static int turnCounter = 0;
    
    moveForward(MOTOR_SPEED);
    pixy.ccc.getBlocks();//le pedimos imagen a pixy
    if (turnCounter < 12) {
        pixy.ccc.getBlocks();  // Pedimos imagen a Pixy

        if (pixy.ccc.numBlocks > 0) {
            Serial.print("Bloques detectados: ");
            Serial.println(pixy.ccc.numBlocks);

            for (int i = 0; i < pixy.ccc.numBlocks; i++) {
                Serial.print("Bloque #");
                Serial.print(i + 1);
                Serial.print(" | Firma: ");
                Serial.println(pixy.ccc.blocks[i].m_signature);
            }

            int signature = pixy.ccc.blocks[0].m_signature;

            // Detener motor antes del giro

            if (signature == 2) { // Naranja detectado
                Serial.println("→ NARANJA detectado: moviendo servo a la DERECHA.");
                servoMotor.write(DERECHA);
                delay(200);
                
            } else if (signature == 1) { // Azul detectado
                Serial.println("→ AZUL detectado: moviendo servo a la IZQUIERDA.");
                servoMotor.write(IZQUIERDA);
                delay(200);
            }

            // Mantener posición del servo
            delay(DELAY_GIRO);
            servoMotor.write(CENTRO);

            // Sumar al contador de giros
            turnCounter++;
            Serial.print("Giros ejecutados: ");
            Serial.println(turnCounter);

            // Volver a avanzar después del giro
            moveForward(MOTOR_SPEED);
            delay(500);
        } else {
            // Si no se detecta ningún bloque, el carro sigue avanzando
            Serial.println("→ No se detectó color, seguimos avanzando.");
            moveForward(MOTOR_SPEED);
        }

        delay(100);
    } else {
        stopMotor();
        servoMotor.write(CENTRO);
        Serial.println("¡Se completaron las 3 vueltas (12 giros)! Fin de la ejecución.");
        
        while (true) {
            delay(1000);
        }
    }
}
