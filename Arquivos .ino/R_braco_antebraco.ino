 // PROGRAMA DO BRAÇO //

       // DECLARAÇÃO DAS BIBLIOTECAS //
        
/*/ nota:
           elevação e profundidade = eixo Y
           rotação = eixo Z
           movimento de giro = eixo X /*/
           
#include <VarSpeedServo.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <SPI.h>
       

#define servom1 2 // rotação
#define servom2 3 // base1
#define servom3 1 // base2 
#define servom4 4 // antebraço
/*/#define servom5 6
#define srv 7
#define srv1 8/*/

RF24 radio(9, 10);// CE CSN
const byte endereco[6] = {0xB3B4B5B6F1, 0xB3B4B5B6CD, 0xB3B4B5B6A3};

VarSpeedServo servorot;
VarSpeedServo servobase1;
VarSpeedServo servobase2; 
VarSpeedServo servoant; // servo antebraço - antigo servoomb
/*/VarSpeedServo servouppun; // servo de elevação do punho - antigo servocot
VarSpeedServo servogiropun; // servo de girar o punho - antigo servopun
VarSpeedServo servogar;/*/

int msg [8];
int led = A0;

int psrot;
int psbase1;
int psbase2;
int puppunho;
int pant;
int psgiropun;

int funcao1;
int funcao2;
int funcao3;
int funcao4;
/*/ msg[4] = garra; 
    msg[3] = angX;
    msg[2] = angY;
    msg[1] = angZ;/*/

void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 Serial.print("iniciando");
 
 radio.begin();
 radio.openReadingPipe(0, endereco [0]);
 radio.openReadingPipe(1, endereco [1]);
 radio.openReadingPipe(2, endereco [2]);
 radio.setPALevel(RF24_PA_MAX);
 radio.startListening();
 radio.setChannel(100);

 
  
 servorot.attach (servom1);
 servorot.slowmove(95, 60);
 
 servobase1.attach (servom2);
 servobase2.attach (servom3);
 servobase1.slowmove(100, 60);
 
 servobase2.slowmove(80, 60);
 
 servoant.attach (servom4);
 servoant.slowmove (135, 60);
 
 /*/servouppun.attach (servom5);
 servouppun.slowmove(50, 60);
 delay (2000);
 servogiropun.attach (srv);
 servogiropun.slowmove(160, 60);
 delay (2000);
 servogar.attach (srv1);
 servogar.slowmove(75, 60);
 delay (2000);
 pinMode(led, OUTPUT);/*/

  
}

void loop() {

  
   // comunicação funcionando e comandos pela luva //
   
    while(radio.available()){
  
    digitalWrite(led, HIGH);// comunicação funcionando 

   // LEITURA DAS MSG DA LUVA E ESCRITA NO SERIAL //
   
    radio.read(&msg, sizeof(msg));
    
    Serial.print("tvalorZ :");
    Serial.print(msg[1]);
    Serial.print("\tvalorY :");  
    Serial.print(msg[2]);
    Serial.print("\tvalorX :");            
    Serial.print(msg[3]);
    Serial.print("\tvalor ang garra :");            
    Serial.println(msg[4]);



   // BRAÇO //
   if(msg[0] == 101) {
   psbase1 = map(msg[2], -180, 120, 45, 120); // base 1 = 0 abaixa pra frente, base 2 = 0 abaixa pra traz
   psbase2 = map(msg[2], -180, 120, 135, 60);
    
    if(msg[2] > -200 && msg[2]< 200){
      servobase1.slowmove(psbase1, 30);
      servobase2.slowmove(psbase2, 30);
    }
   }


   // ANTEBRAÇO //

    if (msg [0] == 101) {
      pant = map(msg[2], 80, -100, 180, 90);
      psrot = map(msg[1], -100, 80, 0, 180);
     
      
      if (msg[2] >= -100 && msg[2] <= 100){
        servoant.slowmove(pant, 60);
        }
        
      if(msg[5] >= -560 && msg[5] <= 560) {
        servorot.slowmove(psrot, 60);
      }
    
 // MÃO E PUNHO //
 
/*/

  if (msg [0] == 99){
   puppunho = map(msg[2], -100, 80, 0, 130);

   if (msg[3] > -100){
    funcao1 = 1;
   }
     
   if (msg[3] > 40) {
    funcao1 = 2;
   }
    if (msg[3] < -50) {
    funcao1 = 3;
   }
   

   switch (funcao1){
    case 1: 
    servogiropun.slowmove(90, 60);
    servogar.slowmove(msg[4], 110);
    break;

    case 2:
    servogiropun.slowmove(30, 60);
    servogar.slowmove(msg[4], 110);
    break;

    case 3:
    servogiropun.slowmove(180, 60);
    servogar.slowmove(msg[4], 110);
    break;

    
   }
   
  
   if (msg[2] >= -50 && msg[2] <= 70) {
    servouppun.slowmove (puppunho, 60);
    servogar.slowmove(msg[4], 110);
   }
   servogar.slowmove(msg[4], 110);
   
    delay(15);
}/*/
  
 }

 
}

}

 
  

















 
