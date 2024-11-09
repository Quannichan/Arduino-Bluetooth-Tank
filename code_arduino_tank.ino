 
#include <Servo.h>


#include <SoftwareSerial.h>

Servo shoulder;
Servo arm;
Servo hand;
Servo finger;

int enA = 1;
int lb = 2;
int lf = 3;
int rf = 4;
int rb = 5;
int enB = 6; 


int bluetoothTx = 10;  // bluetooth tx to 10 pin
int bluetoothRx = 11;  // bluetooth rx to 11 pin




short shoul_stat = 0; // 0 là đứng yên, 1 là trái, 2 là phải

short arm_stat = 0; // 0 là đứng yên, 1 là tới, 2 là lui

short hand_stat = 0;

short finger_stat = 0;

short runVert = 0; // 0 đứng yên, 1 đi tới, 2 đi lùi

short runRotate = 0;

SoftwareSerial bluetooth(bluetoothTx, bluetoothRx);

byte sh_pos = 90;

byte arm_pos = 90;  // Changed data type to byte

byte hand_pos = 50;   // Changed data type to byte

byte fin_pos = 50;    // Changed data type to byte

void setup() {

Serial.begin(9600);

pinMode(lf,OUTPUT);   //left motors  fwd
pinMode(lb,OUTPUT);  //left motors bwd
pinMode(rf,OUTPUT);   //right  motors fwd
pinMode(rb,OUTPUT);
pinMode(enA,OUTPUT);
//pinMode(enB,OUTPUT);

//
//analogWrite(enA, 0);
//analogWrite(enB, 0);

  bluetooth.begin(9600);


  shoulder.attach(8);


  arm.attach(7);
 
  hand.attach(9);

 finger.attach(13);


  shoulder.write(sh_pos);


  arm.write(arm_pos);


  hand.write(hand_pos);


  finger.write(fin_pos);




}




void loop() {
  if (bluetooth.available() > 0) {


    char command = bluetooth.read();


    switch(command){


      case 'K': shoul_stat = 1;break;


      case 'L': shoul_stat = 0;break;


      case 'M': shoul_stat = 2;break;


      case 'N': shoul_stat = 0;break;


      case 'G': arm_stat = 1;break;


      case 'H': arm_stat = 0;  ;break;


      case 'I': arm_stat = 2;break;


      case 'J': arm_stat = 0;  ;break;


      case 'C': hand_stat = 1;break;


      case 'D': hand_stat = 0;  ;break;


      case 'E': hand_stat = 2;break;


      case 'F': hand_stat = 0; break;


      case 'A': {        


        if (finger_stat == 1) {
          finger_stat = 0;
          fin_pos = 34;
        } else if(finger_stat == 0){
          finger_stat = 1;
          fin_pos = 55;
        }
        finger.write(fin_pos);
       
        shoul_stat = 0;


        arm_stat = 0;


        hand_stat = 0;


        runVert = 0;
       
        break;


      }


      case '1': runVert = 1 ;break;
      case '2': runVert = 0; break;
      case '5': runVert = 2; break;
      case '6': runVert = 0; break;
      case '3': runVert = 3; break;
      case '4': runVert = 0; break;
      case '7': runVert = 4; break;
      case '8': runVert = 0; break;
   }


  }


  if (shoul_stat == 1) {


    if (sh_pos < 180) {


      sh_pos += 2;


      shoulder.write(sh_pos);


    } else {


      shoul_stat = 0;


    }


  } else if (shoul_stat == 2) {


    if (sh_pos > 0) {


      sh_pos -= 2;


      shoulder.write(sh_pos);


    } else {


      shoul_stat = 0;


    }


  }


  if (arm_stat == 1) {


    if (arm_pos > 90) {


      arm_pos -= 2;


      arm.write(arm_pos);


    } else {


      arm_stat = 0;


    }


  } else if (arm_stat == 2) {


    if (arm_pos < 180) {


      arm_pos += 2;


      arm.write(arm_pos);


    } else {


      arm_stat = 0;


    }


  }


  if (hand_stat == 1) {


    if (hand_pos > 25) {


      hand_pos -= 2;


      hand.write(hand_pos);


    } else {


      hand_stat = 0;


    }


  } else if (hand_stat == 2) {


    if (hand_pos < 87) {


      hand_pos += 2;


      hand.write(hand_pos);


    } else {


      hand_stat = 0;


    }


  }


  if(runVert == 1){
    digitalWrite(rf,HIGH);
    digitalWrite(lf,HIGH);
    digitalWrite(rb,LOW);
    digitalWrite(lb,LOW);
    analogWrite(enA, 225);
    analogWrite(enB, 225);

  }else if(runVert == 2){
      digitalWrite(rf,LOW);
      digitalWrite(lf,LOW);
      digitalWrite(rb,HIGH);
      digitalWrite(lb,HIGH);
      analogWrite(enA, 225);
      analogWrite(enB, 225);

//  } 
//  else if(runVert = 3){
//     digitalWrite(rb,LOW);
//
//
// digitalWrite(lf,LOW);
//
//
// digitalWrite(rf,HIGH);
//
//
// digitalWrite(lb,HIGH);
//analogWrite(enA, 225);
////analogWrite(enB, 225);
//
//  } else if(runVert == 4){
// digitalWrite(rf,LOW);
//
//
// digitalWrite(lb,LOW);
//
//
// digitalWrite(lf,HIGH);
//
//
// digitalWrite(rb,HIGH);
//
//analogWrite(enA, 225);
////analogWrite(enB, 225);
  }else if(runVert == 0){
    digitalWrite(rf,LOW);
    digitalWrite(lf,LOW);
    digitalWrite(rb,LOW);
    digitalWrite(lb,LOW);
    analogWrite(enA, LOW);
    analogWrite(enB, LOW);
  } 


//if(runRotate == 1){
//    digitalWrite(rf,LOW);
//    digitalWrite(lf,HIGH);
//    digitalWrite(rb,LOW);
//    digitalWrite(lb,HIGH);
//    analogWrite(enB, 225);
//    analogWrite(enA, 225);
//
//  }else if(runRotate == 2){
//      digitalWrite(rf,HIGH);
//
//
//      digitalWrite(lf,LOW);
//
//
//      digitalWrite(rb,HIGH);
//
//
//      digitalWrite(lb,LOW);
//      analogWrite(enB, 225);
//    analogWrite(enA, 225);
//
//  } else if(runRotate == 0){
//  digitalWrite(rf,LOW);
//
//
//      digitalWrite(lf,LOW);
//
//
//      digitalWrite(rb,LOW);
//
//
//      digitalWrite(lb,LOW);
//      analogWrite(enA, 0);
//      analogWrite(enB, 0);
//
//  }
  


  delay(20);


}
