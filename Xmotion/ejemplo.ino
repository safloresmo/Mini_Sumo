#include <xmotion.h> //Librería XMotion incluida
int RightSensor = A5; //Pin del sensor del oponente derecho
int RightDiagonalSensor = 4; //Pin del sensor diagonal derecho del oponente
int MiddleSensor = 2; //Pin del sensor central del oponente
int LeftDiagonalSensor = 1; //Pin del sensor diagonal izquierdo del oponente
int LeftSensor = 0; //Pin del sensor izquierdo del oponente

int LeftLine = A2; //Pin del sensor de línea izquierdo
int RightLine = A4; //Pin del sensor de línea derecho
int Start = 10; //Pin del botón de inicio

int Led1 = 8;

int LastValue = 0;

void setup() {
xmotion.StopMotors(100); //Detener los motores, en caso de que el pin tenga una salida abierta.
xmotion.ToggleLeds(100); //Función de retardo de parpadeo para dos luces de usuario
pinMode(Led1, OUTPUT);
pinMode(RightSensor, INPUT); //Declaramos entradas y salidas digitales.
pinMode(RightDiagonalSensor, INPUT);
pinMode(MiddleSensor, INPUT);
pinMode(LeftDiagonalSensor, INPUT);
pinMode(LeftSensor, INPUT);
pinMode(Start, INPUT);
Serial.begin(9600);
}
void loop() {
  
while (digitalRead(Start) == 0) { // Se espera la pulsación del botón. Cuando se presiona el botón, devuelve un valor de 1.
if (digitalRead(LeftSensor) == 1 || digitalRead(MiddleSensor) == 1 || digitalRead(RightSensor) == 1 || digitalRead(RightDiagonalSensor) == 1 || digitalRead(LeftDiagonalSensor) == 1)
{
digitalWrite(Led1, HIGH); //Enciende Led1
} else {
digitalWrite(Led1, LOW); //Apaga Led1
}
xmotion.UserLed2(100); //Parpadeo de User Led 2 con intervalos de 100 milisegundos.
}

xmotion.CounterLeds(1000, 5); //Cuenta con retraso de 1000 milisegundos y 5 veces.

while (1) {
  
if (analogRead(LeftLine) < 300 && analogRead(RightLine) > 300 ) { //El sensor de línea izquierdo ve la línea
xmotion.Backward(100, 100); //Marcha hacia atrás con velocidad al 100% y retraso de 100 milisegundos.
xmotion.Right0(100, 200); //Giro hacia la derecha con velocidad al 100% y duración de 200 milisegundos.
} else if (analogRead(LeftLine) > 300 && analogRead(RightLine) < 300 ) { //El sensor de línea derecha ve la línea
xmotion.Backward(100, 100); //Marcha hacia atrás con velocidad al 100% y retraso de 100 milisegundos.
xmotion.Left0(100, 200); //Giro hacia la izquierda con velocidad al 100% y duración de 200 milisegundos.
} else if (analogRead(LeftLine) < 300 && analogRead(RightLine) < 300 ) { //Ambos sensores ven la línea
xmotion.Backward(100, 200); //Marcha hacia atrás con velocidad al 100% y retraso de 200 milisegundos.
xmotion.Right0(100, 300); //Giro hacia la derecha con velocidad al 100% y duración de 300 milisegundos.


} else if (digitalRead(MiddleSensor) == 1 ) { //El sensor central ve al oponente (0 no visto, 1 visto)
xmotion.Forward(100, 1); //Ambos motores hacia adelante con velocidad al 100% y retraso de 1 milisegundo.
LastValue = 0;
}


else if (digitalRead(RightSensor) == 1) // El sensor derecho ve al oponente
{
xmotion.Right0(70, 1); // Girar a la derecha con %70 de potencia durante 1 milisegundo
LastValue = 1;
}
else if (digitalRead(LeftSensor) == 1) // El sensor izquierdo ve al oponente
{
xmotion.Left0(70, 1); // Girar a la izquierda con %70 de potencia durante 1 milisegundo
LastValue = 2;
}
else if (digitalRead(LeftDiagonalSensor) == 1) // El sensor diagonal izquierdo ve al oponente
{
xmotion.ArcTurn(20, 70, 1); // Motor izquierdo con %20 de velocidad, derecho con %70 de velocidad durante 1 ms
LastValue = 2;
}


else if (digitalRead(RightDiagonalSensor) == 1) // El sensor diagonal derecho ve al oponente
{
xmotion.ArcTurn(70, 20, 1); // Motor izquierdo con %70 de velocidad, derecho con %20 de velocidad durante 1 ms
LastValue = 1;
} else if (LastValue == 0) { // El sensor central vio al oponente
xmotion.Forward(20, 1);
} else if (LastValue == 1) { // El sensor derecho o diagonal derecho vieron al oponente
xmotion.Right0(30, 1);
} else if (LastValue == 2) { // El sensor izquierdo o diagonal izquierdo vieron al oponente
xmotion.Left0(30, 1);
}
}
}
