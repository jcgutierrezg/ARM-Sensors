#include <Wire.h>
#include <Servo.h>



//Código del reader para la comunicación con el protocolo I2C entre 2 arduinos. 
//El Arduino principal le envía a este Arduino la información con el servo a mover.

int servo = 0;
int senal = 0;

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(0x28);
  Serial.begin(57600);
  Wire.onReceive(recieveEvent);
  servo0.attach(3);
  servo1.attach(4);
  servo2.attach(5);
  servo3.attach(6);
  servo4.attach(7);
  servo5.attach(8);
  servo6.attach(9);

}
void loop() {
}

void recieveEvent(int howMany){
  Serial.println(Wire.available());
  while (1 < Wire.available()){
    Serial.println("entra");  
    servo=int(Wire.read());
    senal=int(Wire.read());
    Serial.println("servo: "+String(servo));
    Serial.println("senal: "+String(senal));

    if (servo==0){
      servo0.write(senal);
    }
    else if (servo==1){
      servo1.write(senal);
    }
    else if (servo==2){
      servo2.write(senal);
    }
    else if (servo==3){
      servo3.write(senal);
    }
    else if (servo==4){
      servo4.write(senal);
    }
    else if (servo==5){
      servo5.write(senal);
    }
    else if (servo==6){
      servo6.write(senal);
    }
    
    }
  
  }  
