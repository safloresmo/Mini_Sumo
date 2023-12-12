/*----------------------------------------------------------------------------------*/
//                Traqueo
/*----------------------------------------------------------------------------------*/
#include <xmotion.h> //incluida la biblioteca XMotion
int RightSensor = A5; //Pin del sensor oponente derecho
int RightDiagonalSensor = 4; //Pin del sensor oponente diagonal derecho
int MiddleSensor = 2; //Pin del sensor oponente medio
int LeftDiagonalSensor = 1; //Pin del sensor oponente diagonal izquierdo
int LeftSensor = 0; //Pin del sensor oponente izquierdo
int LeftLine = A2; //Pin del sensor de línea izquierdo
int RightLine = A1; //Pin del sensor de línea derecho
int Start = 10; //Pin del botón de inicio
int Led1 = 8;
int BOTON = 0;
int Arranque = 10;
int LastValue = 0;
/*----------------------------------------------------------------------------------*/
void ARRANCADOR(){
  BOTON = digitalRead(Arranque);
}
/*----------------------------------------------------------------------------------*/
void setup() {
  xmotion.StopMotors(100); //detener los motores, en caso de que el pin tenga una salida abierta.
  xmotion.ToggleLeds(100); //Función de retardo de parpadeo para parpadear 2 LED del usuario
  pinMode(Led1, OUTPUT);
  pinMode(RightSensor, INPUT); //Declaramos los entradas y salidas digitales.
  pinMode(RightDiagonalSensor, INPUT);
  pinMode(MiddleSensor, INPUT);
  pinMode(LeftDiagonalSensor, INPUT);
  pinMode(LeftSensor, INPUT);
  pinMode(Start, INPUT);
  Serial.begin(9600);
}
/*----------------------------------------------------------------------------------*/
void loop() {
  ARRANCADOR(); //Llama a la función ARRANCADOR
  
   if (BOTON==HIGH){
/*-------------------------------------------Sensores de linea-------------------------------------------------------------*/
    if (analogRead(LeftLine) < 300 && analogRead(RightLine) > 300 ){ //Si el sensor de línea izquierdo ve la línea
      xmotion.Backward(30, 200); //Retrocede a una velocidad del 30% durante 300ms
      xmotion.Right0(30, 200); //Gira a la derecha a una velocidad del 30% durante 200ms
      }else if (analogRead(LeftLine) > 300 && analogRead(RightLine) < 300 ){ //Si el sensor de línea derecho ve la línea
        xmotion.Backward(30, 200); //Retrocede a una velocidad del 30% durante 300ms
        xmotion.Left0(30, 200); //Gira a la izquierda a una velocidad del 30% durante 200ms
        } else if (analogRead(LeftLine) < 300 && analogRead(RightLine) < 300 ){ //Si ambos sensores de línea ven la línea
          xmotion.Backward(30, 200); //Retrocede a una velocidad del 30% durante 200ms
          xmotion.Right0(100, 200); //Gira a la derecha a una velocidad del 100% durante 300ms
          }
/*----------------------------------------Sensores de oponente central------------------------------------------------------*/
        else if (digitalRead(MiddleSensor) == 1 ){ //Si el sensor central detecta algo
            //xmotion.Forward(100,1); //Avanza a una velocidad del 100% durante 1ms
            LastValue = 0;
            }
/*----------------------------------------Sensores de oponente Derecho------------------------------------------------------*/
       else if (digitalRead(RightSensor) == 1){ // El sensor derecho ve al oponente
        xmotion.Right0(70, 1); // Girar a la derecha con %70 de potencia durante 1 milisegundo
        LastValue = 1;
       }
/*----------------------------------------Sensores de oponente Izquierdo------------------------------------------------------*/
       else if (digitalRead(LeftSensor) == 1){ // El sensor izquierdo ve al oponente
        xmotion.Left0(70, 1); // Girar a la izquierda con %70 de potencia durante 1 milisegundo
        LastValue = 2;
       }
/*----------------------------------------Sensores de oponente Diagonal Izquierdo--------------------------------------------*/
       else if (digitalRead(LeftDiagonalSensor) == 1){ // El sensor diagonal izquierdo ve al oponente
        xmotion.ArcTurn(20, 70, 1); // Motor izquierdo con %20 de velocidad, derecho con %70 de velocidad durante 1 ms
        LastValue = 2;
       }
/*----------------------------------------Sensores de oponente central------------------------------------------------------*/
       else if (digitalRead(RightDiagonalSensor) == 1){ // El sensor diagonal derecho ve al oponente
        xmotion.ArcTurn(70, 20, 1); // Motor izquierdo con %70 de velocidad, derecho con %20 de velocidad durante 1 ms
        LastValue = 1;
       }
/*----------------------------------------   ------------------------------------------------------*/
   else if (LastValue == 0) { // El sensor central vio al oponente
     xmotion.Forward(20, 1);
   } else if (LastValue == 1) { // El sensor derecho o diagonal derecho vieron al oponente
      xmotion.Right0(30, 1);
    } else if (LastValue == 2) { // El sensor izquierdo o diagonal izquierdo vieron al oponente
      xmotion.Left0(30, 1);
    }
  }
  else{
    xmotion.StopMotors(100);
  }
}
