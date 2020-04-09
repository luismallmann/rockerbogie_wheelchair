#include <Timing.h>
#include <Servo.h>
#include <SoftwareSerial.h>

//definicao bluetooth
#define RX 0
#define TX 1

//definicao das portas utilizadas
#define RFE 2 //roda frontal esquerda porta 0
#define RME 3 //roda meio esquerda porta 1
#define RTE 4 //roda traseira esquerda porta 2
#define RFD 5 //roda frontal direita porta 3
#define RMD 6 //roda meio direita porta 4
#define RTD 7 //roda traseira direita porta 5
#define GFE 8 //giro frontal esquerda porta 6
#define GME 9 //giro meio esquerda porta 7
#define GTE 10 //giro traseira esquerda porta 8
#define GFD 11 //giro frontal direita porta 9
#define GMD 12 //giro meio direita porta 10
#define GTD 13 //giro traseira direita porta 11

SoftwareSerial bluetooth(RX, TX); // RX, TX

//servos
Servo ServoRFD;
Servo ServoRMD;
Servo ServoRTD;
Servo ServoRFE;
Servo ServoRME;
Servo ServoRTE;
Servo ServoGFD;
Servo ServoGMD;
Servo ServoGTD;
Servo ServoGFE;
Servo ServoGME;
Servo ServoGTE;

int hor = 0; //sentido horario
int anti = 180;
int pare = 90;
int leitura = 0;
char posicao = 'n';

Timing timerVelocidade;

void setup ()
{

  ServoRFD.attach(RFD);
  ServoRMD.attach(RMD);
  ServoRTD.attach(RTD);
  ServoRFE.attach(RFE);
  ServoRME.attach(RME);
  ServoRTE.attach(RTE);
  ServoGFD.attach(GFD);
  ServoGMD.attach(GMD);
  ServoGTD.attach(GTD);
  ServoGFE.attach(GFE);
  ServoGME.attach(GME);
  ServoGTE.attach(GTE);

  Serial.begin(9600); // Inicializa a serial nativa do Arduino
  bluetooth.begin(9600); // Inicializa a serial via software (Onde está conectado o nosso módulo bluetooth)
  timerVelocidade.begin(0);

  alinhado();
  parado();
}

void verificaBluetooth() { // Verifica se existe algum dado a ser lido da serial  
  if (bluetooth.available()) { // verifica se existem bytes a serem lidos da porta serial virtual
    char dados = bluetooth.read(); // Lê 1 byte da porta serial
    Serial.print(dados); // Mostra esse dado lido na porta serial
    

        if (dados == 'p') { // Se o byte lido for igual a p
          parado();
        }
        else if (dados == 'f'){
            // Se o byte lido for igual a f
            andar();
            //delay faz o prototipo andar por por um meio segundo
            delay(500);
        }
            else if (dados == 'r'){
            // Se o byte lido for igual a r
            re();
            //delay faz o prototipo andar por por um meio segundo
            delay(500);
        }
        else if (dados == 'e'){
            // Se o byte lido for igual a e
            esquerda();
            //delay faz o prototipo andar por por um meio segundo
            delay(200);
        }
        else if (dados == 'd'){
            // Se o byte lido for igual a d
            direita();
            //delay faz o prototipo andar por por um meio segundo
            delay(200);
        }
        else if (dados == 'a'){
            // Se o byte lido for igual a a
            alinhado();
        }
   }
   else{
    if (timerVelocidade.onTimeout(20)){
      parado();
    }
  }
}

void loop()
{

  verificaBluetooth();
}
void re()
{
  if(posicao == 'n'){
    ServoRFD.write(hor);
    ServoRMD.write(hor);
    ServoRTD.write(hor);
    ServoRFE.write(anti);
    ServoRME.write(anti);
    ServoRTE.write(anti);
  }
  else if(posicao == 'e' || posicao == 'd'){
    ServoRFD.write(anti);
    ServoRMD.write(anti);
    ServoRTD.write(anti);
    ServoRFE.write(anti);
    ServoRME.write(anti);
    ServoRTE.write(anti);
  }
  
}
void parado() {
  ServoRFD.write(pare);
  ServoRMD.write(pare);
  ServoRTD.write(pare);
  ServoRFE.write(pare);
  ServoRME.write(pare);
  ServoRTE.write(pare);
}
void andar()
{
  if(posicao == 'n'){ 
      ServoRFD.write(anti);
      ServoRMD.write(anti);
      ServoRTD.write(anti);
      ServoRFE.write(hor);
      ServoRME.write(hor);
      ServoRTE.write(hor);
  }  
  else if(posicao == 'e' || posicao == 'd'){
    ServoRFD.write(hor);
    ServoRMD.write(hor);
    ServoRTD.write(hor);
    ServoRFE.write(hor);
    ServoRME.write(hor);
    ServoRTE.write(hor);
  }
}
void alinhado()
{
  ServoGFD.write(90);
  ServoGMD.write(90);
  ServoGTD.write(90);
  ServoGFE.write(90);
  ServoGME.write(90);
  ServoGTE.write(90);

  posicao = 'n';
}
void esquerda()
{
  ServoRFD.write(hor);
  ServoRMD.write(hor);
  ServoRTD.write(hor);
  ServoRFE.write(hor);
  ServoRME.write(hor);
  ServoRTE.write(hor);

}
void direita()
{
  ServoRFD.write(anti);
  ServoRMD.write(anti);
  ServoRTD.write(anti);
  ServoRFE.write(anti);
  ServoRME.write(anti);
  ServoRTE.write(anti);
}
