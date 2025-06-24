#include <Servo.h>

// Configuración de pines del motor
#define ENB 10
#define IN4 11
#define IN3 12

// Configuración del servo
#define SERVO_PIN 9
#define SERVO_CENTER 88
#define SERVO_LEFT 43
#define SERVO_RIGHT 133

// Configuración de sensores ultrasónicos
#define TRIG_RIGHT 2
#define ECHO_RIGHT 3
#define TRIG_LEFT 4
#define ECHO_LEFT 5

// Parámetros
#define MOTOR_SPEED 130
#define APERTURA_UMBRAL 70      // 70cm
#define TIEMPO_GIRO 1600        // ms - actualizado
#define DELAY_POST_GIRO 1500    // ms - actualizado
#define NUM_LECTURAS 3          // Número de lecturas para confirmar

// Parámetros de corrección proporcional simple
#define UMBRAL_DIFERENCIA 15    // cm - diferencia mínima entre lados para corregir
#define SERVO_CORRECCION_IZQ 75 // grados - corrección suave a izquierda
#define SERVO_CORRECCION_DER 105 // grados - corrección suave a derecha
#define TIEMPO_CORRECCION 200   // ms - duración de la corrección

// Parámetros de centrado inicial
#define UMBRAL_CENTRADO_INICIAL 10   // cm - diferencia mínima para activar centrado
#define VELOCIDAD_CENTRADO 130       // velocidad del motor durante centrado
#define TIEMPO_CENTRADO_FASE1 1200    // ms - duración del giro inicial
#define TIEMPO_CENTRADO_FASE2 1100    // ms - duración del contra-giro
#define SERVO_CENTRADO_IZQ 43        // grados - ángulo para centrado inicial a izquierda
#define SERVO_CENTRADO_DER 133       // grados - ángulo para centrado inicial a derecha


// Objeto servo
Servo servoMotor;

// Variables globales
float distanciaDerecha = 0;
float distanciaIzquierda = 0;

void setup() {
  Serial.begin(115200);
  
  // Configurar pines del motor
  pinMode(ENB, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN3, OUTPUT);
  
  // Configurar servo
  servoMotor.attach(SERVO_PIN);
  servoMotor.write(SERVO_CENTER);
  
  // Configurar pines de sensores ultrasónicos
  pinMode(TRIG_RIGHT, OUTPUT);
  pinMode(ECHO_RIGHT, INPUT);
  pinMode(TRIG_LEFT, OUTPUT);
  pinMode(ECHO_LEFT, INPUT
  
  Serial.println("Sistema listo!");
  delay(2000);
  
  // Ejecutar centrado inicial
  centradoInicial();
}

void loop() {
  // Leer sensores con múltiples lecturas para confiabilidad
  distanciaDerecha = leerSensorPromedio(TRIG_RIGHT, ECHO_RIGHT);
  distanciaIzquierda = leerSensorPromedio(TRIG_LEFT, ECHO_LEFT);
  
  // Debug - comentar en competencia
  Serial.print("D: ");
  Serial.print(distanciaDerecha);
  Serial.print(" cm | I: ");
  Serial.print(distanciaIzquierda);
  Serial.println(" cm");
  
  // Lógica de control principal
  if (distanciaDerecha > APERTURA_UMBRAL) {
    // Detectada apertura a la derecha
    Serial.println("Apertura detectada a la DERECHA");
    girarDerecha();
    delay(DELAY_POST_GIRO); // Delay adicional para evitar detecciones múltiples
  } 
  else if (distanciaIzquierda > APERTURA_UMBRAL) {
    // Detectada apertura a la izquierda
    Serial.println("Apertura detectada a la IZQUIERDA");
    girarIzquierda();
    delay(DELAY_POST_GIRO); // Delay adicional para evitar detecciones múltiples
  } 
  else {
    // No hay apertura - aplicar corrección proporcional simple
    aplicarCorreccionProporcional();
  }
  
  delay(50); // Pequeña pausa para estabilidad
}

// Función de centrado inicial
void centradoInicial() {
  Serial.println("Iniciando fase de centrado...");
  
  // Leer sensores iniciales
  float distInicialDerecha = leerSensorPromedio(TRIG_RIGHT, ECHO_RIGHT);
  float distInicialIzquierda = leerSensorPromedio(TRIG_LEFT, ECHO_LEFT);
  
  // Mostrar lecturas iniciales
  Serial.print("Distancia inicial - D: ");
  Serial.print(distInicialDerecha);
  Serial.print(" cm | I: ");
  Serial.print(distInicialIzquierda);
  Serial.println(" cm")
  
  // Calcular diferencia
  float diferencia = distInicialIzquierda - distInicialDerecha;
  
  // Si la diferencia es significativa, aplicar centrado
  if (abs(diferencia) > UMBRAL_CENTRADO_INICIAL) {
    
    // Iniciar movimiento
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, VELOCIDAD_CENTRADO);
    
    if (diferencia > 0) {
      // Muy cerca de la pared derecha - maniobra hacia la izquierda
      Serial.println("Centrado inicial: Fase 1 - Girando IZQUIERDA");
      
      // FASE 1: Giro pronunciado hacia el centro
      servoMotor.write(SERVO_CENTRADO_IZQ);
      delay(TIEMPO_CENTRADO_FASE1);
      
      // FASE 2: Contra-giro para enderezar
      Serial.println("Centrado inicial: Fase 2 - Enderezando con contra-giro DERECHA");
      servoMotor.write(SERVO_CENTRADO_CONTRA_IZQ);
      delay(TIEMPO_CENTRADO_FASE2);
      
    } else {
      // Muy cerca de la pared izquierda - maniobra hacia la derecha
      Serial.println("Centrado inicial: Fase 1 - Girando DERECHA");
      
      // FASE 1: Giro pronunciado hacia el centro
      servoMotor.write(SERVO_CENTRADO_DER);
      delay(TIEMPO_CENTRADO_FASE1);
      
      // FASE 2: Contra-giro para enderezar
      Serial.println("Centrado inicial: Fase 2 - Enderezando con contra-giro IZQUIERDA");
      servoMotor.write(SERVO_CENTRADO_CONTRA_DER);
      delay(TIEMPO_CENTRADO_FASE2);
    }
    
    // Detener y enderezar
    analogWrite(ENB, 0);
    servoMotor.write(SERVO_CENTER);
    
    Serial.println("Centrado inicial completado");
    delay(500); // Pequeña pausa antes de continuar
    
  } else {
    Serial.println("Ya está centrado - continuando...");
  }


// Función para leer sensor ultrasónico individual
float leerSensorUltrasonico(int trigPin, int echoPin) {
  // Enviar pulso de trigger
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW)
  
  // Leer el tiempo del echo
  long duracion = pulseIn(echoPin, HIGH, 30000); // Timeout de 30ms
  
  // Calcular distancia en cm
  // Velocidad del sonido = 343 m/s = 0.0343 cm/us
  // Distancia = (tiempo * velocidad) / 2
  float distancia = (duracion * 0.0343) / 2;
  
  // Si no hay lectura válida, retornar valor alto
  if (duracion == 0) {
    return 999;
  }
  
  return distancia;
}

// Función para obtener promedio de múltiples lecturas
float leerSensorPromedio(int trigPin, int echoPin) {
  float suma = 0;
  int lecturasValidas = 0;
  
  // Tomar múltiples lecturas
  for (int i = 0; i < NUM_LECTURAS; i++) {
    float lectura = leerSensorUltrasonico(trigPin, echoPin);
    
    // Solo considerar lecturas válidas (menos de 400cm)
    if (lectura < 400) {
      suma += lectura;
      lecturasValidas++;
    }
    
    delay(10); // Pequeña pausa entre lecturas
  }
  
  // Si tenemos lecturas válidas, retornar promedio
  if (lecturasValidas > 0) {
    return suma / lecturasValidas;
  }
  
  // Si no hay lecturas válidas, retornar valor alto
  return 999;
}

// Funciones de movimiento
void avanzar() {
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  servoMotor.write(SERVO_CENTER);
}

void detener() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void girarDerecha() {
  // Girar servo a la derecha
  servoMotor.write(SERVO_RIGHT);
  
  // Mantener avanzando durante el tiempo de giro
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  
  delay(TIEMPO_GIRO);
  
  // Enderezar servo
  servoMotor.write(SERVO_CENTER);
}

void girarIzquierda() {
  // Girar servo a la izquierda
  servoMotor.write(SERVO_LEFT);
  
  // Mantener avanzando durante el tiempo de giro
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  
  delay(TIEMPO_GIRO);
  
  // Enderezar servo
  servoMotor.write(SERVO_CENTER);
}

// Función para aplicar corrección proporcional simple
void aplicarCorreccionProporcional() {
  // Solo aplicar corrección si ambas paredes están presentes
  if (distanciaDerecha < APERTURA_UMBRAL && distanciaIzquierda < APERTURA_UMBRAL) {
    
    float diferencia = distanciaIzquierda - distanciaDerecha;
    
    // Si está muy cerca de la pared derecha
    if (diferencia > UMBRAL_DIFERENCIA) {
      Serial.print("Muy cerca de pared DERECHA. Dif: ");
      Serial.println(diferencia);
      
      // Aplicar corrección hacia la izquierda
      servoMotor.write(SERVO_CORRECCION_IZQ);
      
      // Avanzar con corrección por tiempo limitado
      unsigned long tiempoInicio = millis();
      while (millis() - tiempoInicio < TIEMPO_CORRECCION) {
        // Verificar si aparece una apertura durante la corrección
        float checkDerecha = leerSensorUltrasonico(TRIG_RIGHT, ECHO_RIGHT);
        float checkIzquierda = leerSensorUltrasonico(TRIG_LEFT, ECHO_LEFT);
        
        if (checkDerecha > APERTURA_UMBRAL || checkIzquierda > APERTURA_UMBRAL) {
          Serial.println("Apertura detectada - cancelando corrección");
          break;
        }
        
        // Mantener movimiento
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, MOTOR_SPEED);
        
        delay(10);
      }
      
      // Enderezar servo
      servoMotor.write(SERVO_CENTER);
      
    } 
    // Si está muy cerca de la pared izquierda
    else if (diferencia < -UMBRAL_DIFERENCIA) {
      Serial.print("Muy cerca de pared IZQUIERDA. Dif: ");
      Serial.println(diferencia);
      
      // Aplicar corrección hacia la derecha
      servoMotor.write(SERVO_CORRECCION_DER);
      
      // Avanzar con corrección por tiempo limitado
      unsigned long tiempoInicio = millis();
      while (millis() - tiempoInicio < TIEMPO_CORRECCION) {
        // Verificar si aparece una apertura durante la corrección
        float checkDerecha = leerSensorUltrasonico(TRIG_RIGHT, ECHO_RIGHT);
        float checkIzquierda = leerSensorUltrasonico(TRIG_LEFT, ECHO_LEFT);
        
        if (checkDerecha > APERTURA_UMBRAL || checkIzquierda > APERTURA_UMBRAL) {
          Serial.println("Apertura detectada - cancelando corrección");
          break;
        }
        
        // Mantener movimiento
        digitalWrite(IN3, HIGH);
        digitalWrite(IN4, LOW);
        analogWrite(ENB, MOTOR_SPEED);
        
        delay(10);
      }
      
      // Enderezar servo
      servoMotor.write(SERVO_CENTER);
      
    } 
    else {
      // Está relativamente centrado - continuar recto
      avanzar();
    }
  } 
  else {
    // No hay dos paredes - solo avanzar
    avanzar();
  }
}
