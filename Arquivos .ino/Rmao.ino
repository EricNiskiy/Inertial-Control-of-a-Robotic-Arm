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
       



#define servom5 6
#define srv 7
#define srv1 8

RF24 radio(9, 10);// CE CSN
const byte endereco[6] = {0xB3B4B5B6F1, 0xB3B4B5B6CD, 0xB3B4B5B6A3};

  
VarSpeedServo servouppun; // servo de elevação do punho - antigo servocot
VarSpeedServo servogiropun; // servo de girar o punho - antigo servopun
VarSpeedServo servogar;

int msg [9];
int led = A0;

/*/int psrot;

int pant;/*/
int puppunho;
int psgiropun;
int psbase1;
int psbase2;
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
 radio.setChannel(80);

 
  
 /*/servorot.attach (servom1);
 servorot.slowmove(95, 60);
 delay (2000);
 
 servoant.attach (servom4);
 servoant.slowmove (50, 60);
 delay (2000);/*/
/*/ servobase1.attach (servom2);
 servobase2.attach (servom3);
 servobase1.slowmove(120, 60);
 
 servobase2.slowmove(60, 60);/*/
 
 servouppun.attach (servom5);
 servouppun.slowmove(73, 60);

 servogiropun.attach (srv);
 servogiropun.slowmove(90, 60);

 servogar.attach (srv1);
 servogar.slowmove(75, 60);
 
 pinMode(led, OUTPUT);

  
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

    servogar.slowmove(msg[4], 60);




 
    
if (msg [0] == 99){
    
// CONTROLE DO PUNHO GIRO E ELEVAÇÃO //

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
}
  
 }
}


 


 
  

















 
