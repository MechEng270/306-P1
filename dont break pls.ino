int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top =2;


void setup() {
  // put your setup code here, to run once:




pinMode(18, INPUT_PULLUP);
pinMode(19, INPUT_PULLUP);
pinMode(20, INPUT_PULLUP);
pinMode(21, INPUT_PULLUP);

pinMode(M1, OUTPUT);
pinMode(M2, OUTPUT);

attachInterrupt(digitalPinToInterrupt(left), safeL, HIGH);
attachInterrupt(digitalPinToInterrupt(right), safeR, HIGH);
attachInterrupt(digitalPinToInterrupt(bottom), safeB, HIGH);
attachInterrupt(digitalPinToInterrupt(top), safeT, HIGH);



}

void loop() {
  // put your main code here, to run repeatedly:

}

void safeL(){
  while(digitalRead(left)){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
}

void safeR(){
  while(digitalRead(right)){
    digitalWrite(M1,LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
}
void safeT(){
  while(digitalRead(top)){
    digitalWrite(M1,LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
}
void safeB(){
  while(digitalRead(bottom)){
    digitalWrite(M1,HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 50); //PWM Speed Control
    analogWrite(E2, 50); 
  }
  analogWrite(E1, 0); //PWM Speed Control
  analogWrite(E2, 0); 
}
