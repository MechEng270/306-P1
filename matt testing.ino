//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 13;
int right =12;
int bottom = 11;
int top =10;

bool L, R, B, T = 0;



volatile int count;
volatile bool dir;
void setup()
{
  Serial.begin(9600);
pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);
pinMode(2, INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(2), countA, RISING);

count = 0;
}
void loop()
{
while(count < 2064){
  digitalWrite(M1,HIGH);
  //digitalWrite(M2, HIGH);
  if(count < 1300){
    analogWrite(E1, 100); //PWM Speed Control
    analogWrite(E2, 100); //PWM Speed Control
  }
  else{
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); //PWM Speed Control
  }
  Serial.println(count);
  
}
analogWrite(E1, 0); //PWM Speed Control
analogWrite(E2, 0); //PWM Speed Control
delay(3000);
count = 0;
while(count > -2064){
  digitalWrite(M1,LOW);
  digitalWrite(M2, LOW);
  if(count > -1300){
    analogWrite(E1, 100); //PWM Speed Control
    analogWrite(E2, 100); //PWM Speed Control
  }
  else{
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); //PWM Speed Control
  }
  Serial.println(count);
}

Serial.println("rev completed");
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0);
delay(3000);
Serial.println(count);
count = 0;

}

void countA(){
if(digitalRead(M1)){
  count++;}
else{
count--;}

/*if(digitalRead(left)){
  L = 1;
}else{
  L = 0;
}
if(digitalRead(right)){
  R = 1;
}else{
  R = 0;
}
if(digitalRead(bottom)){
  B = 1;
}else{
  B = 0;
}
if(digitalRead(top)){
  T = 1;
}else{
  T = 0;
}*/



}



