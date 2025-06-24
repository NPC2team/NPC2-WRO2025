#include <Servo.h>
#include <Pixy2.h>

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

// Parámetros generales
#define MOTOR_SPEED 110              // Velocidad reducida para mejor control
#define MOTOR_SPEED_EVASION 100      // Velocidad durante evasión
#define APERTURA_UMBRAL 70           // 70cm
#define TIEMPO_GIRO 1500             // ms
#define DELAY_POST_GIRO 1200         // ms
#define NUM_LECTURAS 3               // Número de lecturas para confirmar
#define MAX_GIROS 12                 // número máximo de giros antes de detenerse
#define TIEMPO_AVANCE_FINAL 800      // ms - tiempo de avance después del último giro

// Parámetros de navegación visual
#define GANANCIA_CAMARA 0.0          // Qué tan agresivo seguir el obstáculo
#define DISTANCIA_EVASION 25         // cm - cuándo empezar a evadir
#define ANCHO_MIN_OBSTACULO 15       // píxeles - tamaño mínimo para considerar válido
#define CENTRO_CAMARA 158            // Centro horizontal de la Pixy (315/2)

// Parámetros de evasión
#define SERVO_EVASION_IZQ 60         // Ángulo para evadir por izquierda
#define SERVO_EVASION_DER 120        // Ángulo para evadir por derecha
#define TIEMPO_EVASION_FASE1 700     // ms - Alejarse del obstáculo
#define TIEMPO_EVASION_FASE2 700     // ms - Volver al centro

// Parámetros de centrado inicial
#define UMBRAL_CENTRADO_INICIAL 10
#define VELOCIDAD_CENTRADO 130
#define TIEMPO_CENTRADO_FASE1 1200
#define TIEMPO_CENTRADO_FASE2 1100
#define SERVO_CENTRADO_IZQ 43
#define SERVO_CENTRADO_DER 133
#define SERVO_CENTRADO_CONTRA_IZQ 110
#define SERVO_CENTRADO_CONTRA_DER 80

// Configuración de Pixy - Signatures
#define SIG_ROJO 3    // Asignar en Pixy
#define SIG_VERDE 2   // Asignar en Pixy

// Objetos
Servo servoMotor;
Pixy2 pixy;

// Variables globales
float distanciaDerecha = 0;
float distanciaIzquierda = 0;
int contadorGiros = 0;
bool carreraTerminada = false

// Estructura para info del obstáculo
struct Obstaculo {
  bool detectado;
  int x;
  int y;
  int ancho;
  int alto;
  int signature;  // 1=rojo, 2=verde
  float distanciaEstimada;
};

Obstaculo obstaculoActual;

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
  pinMode(ECHO_LEFT, INPUT);
  
  // Inicializar Pixy
  pixy.init();
  
  Serial.println("Sistema listo!");
  Serial.print("Configurado para ");
  Serial.print(MAX_GIROS);
  Serial.println(" giros máximo");
  delay(2000);
  
  // Ejecutar centrado inicial
  centradoInicial();
}

void loop() {
  // Si ya se completaron los giros máximos, no hacer nada
  if (carreraTerminada) {
    detener(
    return
  }
  
  // Leer sensores ultrasónicos
  distanciaDerecha = leerSensorPromedio(TRIG_RIGHT, ECHO_RIGHT);
  distanciaIzquierda = leerSensorPromedio(TRIG_LEFT, ECHO_LEFT);
  
  // Buscar obstáculos con Pixy
  detectarObstaculo();
  
   Debug
  Serial.print("Giro #");
  Serial.print(contadorGiros);
  Serial.print(" | D: ");
  Serial.print(distanciaDerecha);
  Serial.print(" | I: ");
  Serial.print(distanciaIzquierda);
  if (obstaculoActual.detectado) {
    Serial.print(" | Obs: ");
    Serial.print(obstaculoActual.signature == SIG_ROJO ? "ROJO" : "VERDE");
    Serial.print(" X:");
    Serial.print(obstaculoActual.x);
    Serial.print(" Dist:");
    Serial.print(obstaculoActual.distanciaEstimada);
  }
  Serial.println();
  
  // Lógica de control principal
  if (obstaculoActual.detectado) {
    // Modo navegación visual
    navegarHaciaObstaculo();
  } 
  else if (distanciaDerecha > APERTURA_UMBRAL) {
    // Detectada apertura a la derecha
    Serial.println("Apertura detectada a la DERECHA");
    girarDerecha();
    delay(DELAY_POST_GIRO);
  } 
  else if (distanciaIzquierda > APERTURA_UMBRAL) {
    // Detectada apertura a la izquierda
    Serial.println("Apertura detectada a la IZQUIERDA");
    girarIzquierda();
    delay(DELAY_POST_GIRO);
  } 
  else {
    // Sin obstáculos ni aperturas - avanzar recto
    avanzar();
  }
  
  delay(50); // Pequeña pausa para estabilidad
}

// Función para detectar obstáculos con Pixy
void detectarObstaculo() {
  obstaculoActual.detectado = false;
  
  // Obtener bloques de la Pixy
  pixy.ccc.getBlocks();
  
  if (pixy.ccc.numBlocks) {
    // Buscar el obstáculo más grande/cercano
    int mejorBloque = -1;
    int mayorArea = 0;
    
    for (int i = 0; i < pixy.ccc.numBlocks; i++) {
      // Solo considerar bloques rojos o verdes
      if (pixy.ccc.blocks[i].m_signature == SIG_ROJO || 
          pixy.ccc.blocks[i].m_signature == SIG_VERDE) {
        
        int area = pixy.ccc.blocks[i].m_width * pixy.ccc.blocks[i].m_height;
        
        // Filtrar por tamaño mínimo
        if (area > mayorArea && pixy.ccc.blocks[i].m_width > ANCHO_MIN_OBSTACULO) {
          mejorBloque = i;
          mayorArea = area;
        }
      }
    }
    
    // Si encontramos un bloque válido
    if (mejorBloque >= 0) {
      obstaculoActual.detectado = true;
      obstaculoActual.x = pixy.ccc.blocks[mejorBloque].m_x;
      obstaculoActual.y = pixy.ccc.blocks[mejorBloque].m_y;
      obstaculoActual.ancho = pixy.ccc.blocks[mejorBloque].m_width;
      obstaculoActual.alto = pixy.ccc.blocks[mejorBloque].m_height;
      obstaculoActual.signature = pixy.ccc.blocks[mejorBloque].m_signature;
      
      // Estimar distancia basada en el tamaño del objeto
      // Calibrar estos valores según pruebas reales
      obstaculoActual.distanciaEstimada = 3000.0 / obstaculoActual.alto;
    }
  }
}

// Función para navegar hacia el obstáculo detectado
void navegarHaciaObstaculo() {
  // Verificar si estamos lo suficientemente cerca para evadir
  if (obstaculoActual.distanciaEstimada < DISTANCIA_EVASION) {
    if (obstaculoActual.signature == SIG_VERDE) {
      Serial.println("Evadiendo obstáculo VERDE por la IZQUIERDA");
      evadirPorIzquierda();
    } else {
      Serial.println("Evadiendo obstáculo ROJO por la DERECHA");
      evadirPorDerecha();
    }
  } else {
    // Navegar hacia el obstáculo manteniéndolo centrado
    int error = obstaculoActual.x - CENTRO_CAMARA;
    
    // Calcular ángulo del servo basado en el error
    // El error puede ser de -158 a +158, queremos mapear a un rango de servo útil
    float errorNormalizado = (float)error / CENTRO_CAMARA; // -1 a +1
    int anguloServo = SERVO_CENTER + (errorNormalizado * 20 * GANANCIA_CAMARA);
    
    // Limitar el ángulo
    anguloServo = constrain(anguloServo, 70, 110);
    
    // Aplicar corrección
    servoMotor.write(anguloServo);
    
    // Avanzar
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, MOTOR_SPEED);
  }
}

// Función para evadir por la izquierda
void evadirPorIzquierda() {
  // Fase 1: Girar a la izquierda
  servoMotor.write(SERVO_EVASION_IZQ);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED_EVASION);
  delay(TIEMPO_EVASION_FASE1);
  
  // Fase 2: Enderezar con contra-giro
  servoMotor.write(SERVO_EVASION_DER - 20); // Contra-giro suave
  delay(TIEMPO_EVASION_FASE2);
  
  // Volver al centro
  servoMotor.write(SERVO_CENTER);
  
  // Pequeña pausa para estabilizar
  delay(200);
}

// Función para evadir por la derecha
void evadirPorDerecha() {
  // Fase 1: Girar a la derecha
  servoMotor.write(SERVO_EVASION_DER);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED_EVASION);
  delay(TIEMPO_EVASION_FASE1);
  
  // Fase 2: Enderezar con contra-giro
  servoMotor.write(SERVO_EVASION_IZQ + 20); // Contra-giro suave
  delay(TIEMPO_EVASION_FASE2);
  
  // Volver al centro
  servoMotor.write(SERVO_CENTER);
  
  // Pequeña pausa para estabilizar
  delay(200);
}

// [Mantener todas las funciones anteriores sin cambios]
// Función para leer sensor ultrasónico individual
float leerSensorUltrasonico(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duracion = pulseIn(echoPin, HIGH, 30000);
  float distancia = (duracion * 0.0343) / 2;
  
  if (duracion == 0) {
    return 999;
  }
  
  return distancia;
}

// Función para obtener promedio de múltiples lecturas
float leerSensorPromedio(int trigPin, int echoPin) {
  float suma = 0;
  int lecturasValidas = 0;
  
  for (int i = 0; i < NUM_LECTURAS; i++) {
    float lectura = leerSensorUltrasonico(trigPin, echoPin);
    
    if (lectura < 400) {
      suma += lectura;
      lecturasValidas++;
    }
    
    delay(10);
  }
  
  if (lecturasValidas > 0) {
    return suma / lecturasValidas;
  }
  
  return 999;
}

// Funciones de movimiento básicas
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
  contadorGiros++;
  Serial.print("Giro #");
  Serial.print(contadorGiros);
  Serial.println(" a la DERECHA");
  
  servoMotor.write(SERVO_RIGHT);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  
  delay(TIEMPO_GIRO);
  servoMotor.write(SERVO_CENTER);
  
  if (contadorGiros >= MAX_GIROS) {
    Serial.println("¡Último giro completado! Avanzando un poco más...");
    avanzar();
    delay(TIEMPO_AVANCE_FINAL);
    detener();
    carreraTerminada = true;
    Serial.println("¡Carrera completada!");
  }
}

void girarIzquierda() {
  contadorGiros++;
  Serial.print("Giro #");
  Serial.print(contadorGiros);
  Serial.println(" a la IZQUIERDA");
  
  servoMotor.write(SERVO_LEFT);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, MOTOR_SPEED);
  
  delay(TIEMPO_GIRO);
  servoMotor.write(SERVO_CENTER);
  
  if (contadorGiros >= MAX_GIROS) {
    Serial.println("¡Último giro completado! Avanzando un poco más...");
    avanzar();
    delay(TIEMPO_AVANCE_FINAL);
    detener();
    carreraTerminada = true;
    Serial.println("¡Carrera completada!");
  }
}

// Función de centrado inicial
void centradoInicial() {
  Serial.println("Iniciando fase de centrado...");
  
  float distInicialDerecha = leerSensorPromedio(TRIG_RIGHT, ECHO_RIGHT);
  float distInicialIzquierda = leerSensorPromedio(TRIG_LEFT, ECHO_LEFT);
  
  Serial.print("Distancia inicial - D: ");
  Serial.print(distInicialDerecha);
  Serial.print(" cm | I: ");
  Serial.print(distInicialIzquierda);
  Serial.println(" cm");
  
  float diferencia = distInicialIzquierda - distInicialDerecha;
  
  if (abs(diferencia) > UMBRAL_CENTRADO_INICIAL) {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(ENB, VELOCIDAD_CENTRADO);
    
    if (diferencia > 0) {
      Serial.println("Centrado inicial: Fase 1 - Girando IZQUIERDA");
      servoMotor.write(SERVO_CENTRADO_IZQ);
      delay(TIEMPO_CENTRADO_FASE1);
      
      Serial.println("Centrado inicial: Fase 2 - Enderezando con contra-giro DERECHA");
      servoMotor.write(SERVO_CENTRADO_CONTRA_IZQ);
      delay(TIEMPO_CENTRADO_FASE2);
    } else {
      Serial.println("Centrado inicial: Fase 1 - Girando DERECHA");
      servoMotor.write(SERVO_CENTRADO_DER);
      delay(TIEMPO_CENTRADO_FASE1);
      
      Serial.println("Centrado inicial: Fase 2 - Enderezando con contra-giro IZQUIERDA");
      servoMotor.write(SERVO_CENTRADO_CONTRA_DER);
      delay(TIEMPO_CENTRADO_FASE2);
    }
    
    analogWrite(ENB, 0);
    servoMotor.write(SERVO_CENTER);
    
    Serial.println("Centrado inicial completado");
    delay(500);
  } else {
    Serial.println("Ya está centrado - continuando...");
  }
}
