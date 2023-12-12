// Motores 6V 300 RPM
// Batería LiPo 3S 450 Mah
// Los sensores de oponentes dan 1 cuando ven al oponente.

#include <xmotion.h> // Biblioteca XMotion incluida
int RightSensor = A5; // Pin del Sensor de Oponente Derecho
int RightDiagonalSensor = 4; // Pin del Sensor Diagonal Derecho del Oponente
int MiddleSensor = 2; // Pin del Sensor Central del Oponente
int LeftDiagonalSensor = 1; // Pin del Sensor Diagonal Izquierdo del Oponente
int LeftSensor = 0; // Pin del Sensor de Oponente Izquierdo

int LeftLine = A2; // Pin del Sensor de Línea Izquierdo
int RightLine = A4; // Pin del Sensor de Línea Derecho
int Start = 10; // Pin del Botón de Inicio

int Led1 = 8;
int BOTON=0;
int Arranque=10;

int LastValue = 0;

void ARRANCADOR(){
BOTON = digitalRead(Arranque);
}
void setup() {
xmotion.StopMotors(100); // Detener motores, en caso de salida de pin abierta.
xmotion.ToggleLeds(100); // Función de Retardo de Parpadeo para parpadear 2 Leds de Usuario
pinMode(Led1, OUTPUT);
pinMode(RightSensor, INPUT); // Declaramos Entradas y Salidas Digitales.
pinMode(RightDiagonalSensor, INPUT);
pinMode(MiddleSensor, INPUT);
pinMode(LeftDiagonalSensor, INPUT);
pinMode(LeftSensor, INPUT);
pinMode(Start, INPUT);
Serial.begin(9600);
}

void loop() {
ARRANCADOR();
if(BOTON==HIGH){
if (analogRead(LeftLine) < 300 && analogRead(RightLine) > 300 ) //El Sensor de Línea Izquierdo Vio la Línea
{
xmotion.Backward(30, 300); // Retroceso al 100% de velocidad, 100 ms de retirada.
xmotion.Right0(30, 200); // Giro Derecho al 100% de velocidad, duración de 200 ms.
} else if (analogRead(LeftLine) > 300 && analogRead(RightLine) < 300 ) //El Sensor de Línea Derecho Vio la Línea
{
xmotion.Backward(30, 300); // Retroceso al 100% de velocidad, 100 ms de retirada.
xmotion.Left0(30, 200); // Giro Izquierdo al 100% de velocidad, duración de 200 ms.
} else if (analogRead(LeftLine) < 300 && analogRead(RightLine) < 300 ) //Ambos Sensores Vieron la Línea
{
xmotion.Backward(30, 200); // Retroceso al 100% de velocidad, 200 ms de retirada.
xmotion.Right0(100, 300); // Giro Derecho al 100% de velocidad, duración de 200 ms.
}
if (digitalRead(MiddleSensor) == 1 )
{
xmotion.Forward(100, 1); // Ambos Motores Hacia Adelante al 100% de Velocidad, 1 Milisegundo
}

else if(digitalRead(MiddleSensor)==0){
  xmotion.StopMotors(100);
}

 // xmotion.Forward(100, 1); // Ambos Motores Hacia Adelante al 100% de Velocidad, 1 Milisegundo
}
}
