//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top =2;

bool L, R, B, T = 0;



volatile int countL = 0;
volatile int countR = 0;
volatile bool dir;

volatile bool SetLeft = true;
volatile bool SetBottom = true;

void setup()
{
Serial.begin(9600);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(18, INPUT_PULLUP);
pinMode(19, INPUT_PULLUP);
pinMode(21, INPUT_PULLUP);
pinMode(20, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(21), countA, RISING);
attachInterrupt(digitalPinToInterrupt(20), countB, RISING);
attachInterrupt(digitalPinToInterrupt(left), safeL, HIGH);
attachInterrupt(digitalPinToInterrupt(right), safeR, HIGH);
attachInterrupt(digitalPinToInterrupt(bottom), safeB, HIGH);
attachInterrupt(digitalPinToInterrupt(top), safeT, HIGH);


}
void loop()
{
 
    // digitalWrite(M1, LOW);
    // digitalWrite(M2, LOW);
    // analogWrite(E1, 255); //PWM Speed Control
    // analogWrite(E2, 255);

// digitalWrite(M1,HIGH);
// digitalWrite(M2,LOW);
// analogWrite(E1, 0); //PWM Speed Control
// analogWrite(E2, 0); //PWM Speed Control

while(SetLeft){
  digitalWrite(M1,HIGH);
  digitalWrite(M2,HIGH);
  analogWrite(E1, 100); //PWM Speed Control
  analogWrite(E2, 100); //PWM Speed Control
  Serial.println("going left");
}

while(SetBottom){
  digitalWrite(M1,HIGH);
  digitalWrite(M2, LOW);
  analogWrite(E1, 100); //PWM Speed Control
  analogWrite(E2, 100); //PWM Speed Control
  Serial.println("going butt");
}




// while(count < 2064){
//   digitalWrite(M1,HIGH);
//   //digitalWrite(M2, HIGH);
//   if(count < 1300){
//     analogWrite(E1, 100); //PWM Speed Control
//     analogWrite(E2, 100); //PWM Speed Control
//   }
//   else{
//     analogWrite(E1, 50); //PWM Speed Control
//     analogWrite(E2, 50); //PWM Speed Control
//   }
//   Serial.println(count);
  
// }
// analogWrite(E1, 0); //PWM Speed Control
// analogWrite(E2, 0); //PWM Speed Control
// delay(3000);
// count = 0;
// while(count > -2064){
//   digitalWrite(M1,LOW);
//   digitalWrite(M2, LOW);
//   if(count > -1300){
//     analogWrite(E1, 100); //PWM Speed Control
//     analogWrite(E2, 100); //PWM Speed Control
//   }
//   else{
//     analogWrite(E1, 50); //PWM Speed Control
//     analogWrite(E2, 50); //PWM Speed Control
//   }
//   Serial.println(countL);
//   Serial.println(countR);
// }





// Serial.println("rev completed");
//   analogWrite(E1, 0); //PWM Speed Control
//   analogWrite(E2, 0);
// delay(3000);
// Serial.println(count);
// count = 0;

}

// void Rectangle(Width,Height){

//   W =  Width*
//   H = Height*

// }







void safeR(){
  while(digitalRead(right)){
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  //Serial.println(count); 
}

void safeL(){
  while(digitalRead(left)){
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255);
    
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
 
  SetLeft = false;
  //Serial.println(count); 
}
void safeB(){
  while(digitalRead(bottom)){
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
  
  SetBottom = false;
}
void safeT(){
  while(digitalRead(top)){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255); //PWM Speed Control
    analogWrite(E2, 255); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
}





void countA(){
if(digitalRead(M1)){
  countL--;}
else{
countL++;}

}

void countB(){
if(digitalRead(M2)){
  countR--;}
else{
countR++;}

}


