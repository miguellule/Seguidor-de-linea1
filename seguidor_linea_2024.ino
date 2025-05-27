// Definiciones de pines y constantes
#define IR_SENSOR_RIGHT 11  // Pin del sensor infrarrojo derecho
#define IR_SENSOR_LEFT 12   // Pin del sensor infrarrojo izquierdo
#define MOTOR_SPEED 210    // Velocidad predeterminada de los motores MAX 255

// Pines del motor derecho
int enableRightMotor = 3;   // Pin PWM que controla la velocidad del motor derecho
int rightMotorPin1 = 7;     // Pin que controla la dirección del motor derecho
int rightMotorPin2 = 8;     // Pin que controla la dirección inversa del motor derecho

// Pines del motor izquierdo
int enableLeftMotor = 5;    // Pin PWM que controla la velocidad del motor izquierdo
int leftMotorPin1 = 9;      // Pin que controla la dirección del motor izquierdo
int leftMotorPin2 = 10;     // Pin que controla la dirección inversa del motor izquierdo

void setup() {
  // Configuración de los pines como salidas (OUTPUT) para los motores
  pinMode(enableRightMotor, OUTPUT);   // Pin para controlar la velocidad del motor derecho
  pinMode(rightMotorPin1, OUTPUT);     // Pin para controlar la dirección del motor derecho
  pinMode(rightMotorPin2, OUTPUT);     // Pin para controlar la dirección inversa del motor derecho

  pinMode(enableLeftMotor, OUTPUT);    // Pin para controlar la velocidad del motor izquierdo
  pinMode(leftMotorPin1, OUTPUT);      // Pin para controlar la dirección del motor izquierdo
  pinMode(leftMotorPin2, OUTPUT);      // Pin para controlar la dirección inversa del motor izquierdo

  // Configuración de los pines de los sensores infrarrojos como entradas (INPUT)
  pinMode(IR_SENSOR_RIGHT, INPUT);     // Pin del sensor infrarrojo derecho
  pinMode(IR_SENSOR_LEFT, INPUT);      // Pin del sensor infrarrojo izquierdo

  // Inicializa los motores en estado apagado
  rotateMotor(0, 0);  // Llama a la función para detener ambos motores
}

void loop() {
  // Lecturas de los sensores de infrarrojos
  int rightIRSensorValue = digitalRead(IR_SENSOR_RIGHT);   // Lee el valor del sensor derecho (HIGH o LOW)
  int leftIRSensorValue = digitalRead(IR_SENSOR_LEFT);     // Lee el valor del sensor izquierdo (HIGH o LOW)

  // Si ambos sensores detectan una línea blanca (HIGH), el robot avanza recto
  if (rightIRSensorValue == HIGH && leftIRSensorValue == HIGH) {
    rotateMotor(-MOTOR_SPEED, MOTOR_SPEED);  // Ambos motores a la misma velocidad
  }
  // Si el sensor derecho detecta línea negra (LOW) y el izquierdo línea blanca (HIGH), gira a la derecha
  else if (rightIRSensorValue == LOW && leftIRSensorValue == HIGH) {
  //rotateMotor(0, 0); // Detener los motores antes de girar
  //delay(100); // Esperar 100 milisegundos (ajusta este valor según sea necesario)
  rotateMotor(-MOTOR_SPEED, -MOTOR_SPEED); // Girar a la derecha
}
// Si el sensor izquierdo detecta línea negra (LOW) y el derecho línea blanca (HIGH), gira a la izquierda
else if (rightIRSensorValue == HIGH && leftIRSensorValue == LOW) {
  //rotateMotor(0, 0); // Detener los motores antes de girar
  //delay(100); // Esperar 100 milisegundos (ajusta este valor según sea necesario)
  rotateMotor(MOTOR_SPEED, MOTOR_SPEED); // Girar a la izquierda
}
  // Si ambos sensores detectan línea negra (LOW), el robot se detiene
  else {
    rotateMotor(0, 0);  // Ambos motores se detienen
  }
}

// Función para controlar los motores
void rotateMotor(int rightMotorSpeed, int leftMotorSpeed) {
  // Control del motor derecho
  if (rightMotorSpeed < 0) {
    // Si la velocidad es negativa, el motor gira hacia atrás
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, HIGH);
  } else if (rightMotorSpeed > 0) {
    // Si la velocidad es positiva, el motor gira hacia adelante
    digitalWrite(rightMotorPin1, HIGH);
    digitalWrite(rightMotorPin2, LOW);
  } else {
    // Si la velocidad es 0, el motor se detiene
    digitalWrite(rightMotorPin1, LOW);
    digitalWrite(rightMotorPin2, LOW);
  }

  // Control del motor izquierdo
  if (leftMotorSpeed < 0) {
    // Si la velocidad es negativa, el motor gira hacia atrás
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, HIGH);
  } else if (leftMotorSpeed > 0) {
    // Si la velocidad es positiva, el motor gira hacia adelante
    digitalWrite(leftMotorPin1, HIGH);
    digitalWrite(leftMotorPin2, LOW);
  } else {
    // Si la velocidad es 0, el motor se detiene
    digitalWrite(leftMotorPin1, LOW);
    digitalWrite(leftMotorPin2, LOW);
  }

  // Control de la velocidad mediante PWM (modulación por ancho de pulso)
  analogWrite(enableRightMotor, abs(rightMotorSpeed));  // Establece la velocidad del motor derecho
  analogWrite(enableLeftMotor, abs(leftMotorSpeed));    // Establece la velocidad del motor izquierdo
}