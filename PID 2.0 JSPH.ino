//Arduino PWM Speed Control：
int E1 = 5;
int M1 = 4;
int E2 = 6;
int M2 = 7;
int left = 18;
int right = 19;
int bottom = 3;
int top = 2;
bool PID = true;
int x = 0;
int y = 0;
bool L, R, B, T = 0;
volatile int countL = 0;
volatile int countR = 0;
volatile bool dir;

volatile bool SetLeft = true;
volatile bool SetBottom = true;
volatile bool SetRight = true;
volatile bool SetUp = true;



void setup() {
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
  homie();

  countL = 0;
  countR = 0;
  PIDcircle(1000, 1500);




  //circle(2000,3000,3000.0);
  //PIDtest();
  //SetRight = 1;
}
void loop() {
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
}

//HOMING AND INITALISATION
void homie() {
  while (SetLeft) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 100);  //PWM Speed Control
    analogWrite(E2, 100);  //PWM Speed Control
    Serial.println("going left");
  }

  while (SetBottom) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 100);  //PWM Speed Control
    analogWrite(E2, 100);  //PWM Speed Control
    Serial.println("going butt");
  }
}

/*void circle(float diameter, float xIn, float yIn){
float yO = yIn;
float xO = xIn;
float x1;
float y1;
float r = diameter/2.0;
float res = 8;
int i; // does this need to be an int

PIDtest(xIn,yIn);

x = 0;
y = 0;
Serial.println(r);
for (i=0;i<=res;i++){
 

x1 = r * sin(1.57 * (i/res));
y1 = r * cos(1.57 * (i/res));

PIDtest((x1 + xIn),(y1+yIn));
//PIDtest(x1,y1);                    
delay(100);

}*/


// for (i=0;i<res;i++){
// x1 = r - r * sin(i*1.571/res);
// y1 = sqrt(r*r - x1*x1);
// PIDtest(xIn+x1,yIn - r - y1);
// while(PID)
// {

// }
// PID = true;



// }
// for (i=0;i<res;i++){
// x1 =  r * sin(i*1.571/res);
// y1 = sqrt(r*r - x1*x1);
// PIDtest(xIn-x1,yIn - r + y1);
// while(PID)
// {

// }
// PID = true;

// }
// for (i=0;i<res;i++){

// x1 = r - r * sin(i*1.571/res);
// y1 = sqrt(r*r - x1*x1);
// PIDtest(xIn - x1,yIn - r + y1);
// while(PID)
// {

// }
// PID = true;
// }




bool PIDcircle(int xIn, int yIn) {
  double error = 51;
  float PowL = 0;
  float PowR = 0;
  float kp = 0.05;
  //float ki = 0.03;
  //int effortA = 0;
  //int effortB = 0;
  x = (countL + countR) / 2;
  y = (countL - countR) / 2;
  int errorX = xIn - x;
  int errorY = yIn - y;


  while (errorX > 10) {
    x = (countL + countR) / 2;
    y = (countL - countR) / 2;
    //error = sqrt(errorX*errorX + errorY);
    Serial.print(x);
    Serial.print(", ");
    Serial.print(xIn);
    Serial.print(",");
    Serial.print(y);
    Serial.print(", ");
    Serial.print(yIn);
    Serial.print(", ");
    Serial.print(errorX);
    Serial.print(", ");
    Serial.print(errorY);
    Serial.print(", ");
    Serial.print(countR);
    Serial.print(", ");
    Serial.print(countL);
    Serial.println();

    errorX = xIn - x;
    errorY = yIn - y;


    PowL = (kp * (errorX + errorY));
    PowR = (kp * (errorX - errorY));

    if (PowL >= 0) {
      digitalWrite(M1, LOW);
    } else {
      digitalWrite(M1, HIGH);
    }

    if (PowR >= 0) {
      digitalWrite(M2, LOW);
    } else {
      digitalWrite(M2, HIGH);
    }
    if (abs(PowL) > 255) {
      PowR = 255;
    }
    if (abs(PowR) > 255) {
      PowL = 255;
    }
    if (abs(PowL) < 100) {
      PowR = 100;
    }
    if (abs(PowR) < 100) {
      PowL = 100;
    }
    analogWrite(E1, abs(PowL));
    analogWrite(E2, abs(PowR));
    //delay(50);
  }
  analogWrite(E1, 0);
  analogWrite(E2, 0);
}

//safety responses
void safeR() {
  while (digitalRead(right)) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255);  //PWM Speed Control
    analogWrite(E2, 255);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
  SetRight = false;
  //Serial.println(count);
}

void safeL() {
  while (digitalRead(left)) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255);  //PWM Speed Control
    analogWrite(E2, 255);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);

  SetLeft = false;
  //Serial.println(count);
}
void safeB() {
  while (digitalRead(bottom)) {
    digitalWrite(M1, LOW);
    digitalWrite(M2, HIGH);
    analogWrite(E1, 255);  //PWM Speed Control
    analogWrite(E2, 255);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);

  SetBottom = false;
}
void safeT() {
  while (digitalRead(top)) {
    digitalWrite(M1, HIGH);
    digitalWrite(M2, LOW);
    analogWrite(E1, 255);  //PWM Speed Control
    analogWrite(E2, 255);
  }
  analogWrite(E1, 0);  //PWM Speed Control
  analogWrite(E2, 0);
  SetUp = false;
}

void countA() {
  if (digitalRead(M1)) {
    countL--;
  } else {
    countL++;
  }
}

void countB() {
  if (digitalRead(M2)) {
    countR--;
  } else {
    countR++;
  }
}

void printstats(int errorX, int errorY, int xIn, int yIn) {


  Serial.print(x);
  Serial.print(", ");
  Serial.print(xIn);
  Serial.print(",");
  Serial.print(y);
  Serial.print(", ");
  Serial.print(yIn);
  Serial.print(", ");
  Serial.print(errorX);
  Serial.print(", ");
  Serial.print(errorY);
  Serial.print(", ");
  Serial.print(countR);
  Serial.print(", ");
  Serial.print(countL);
  Serial.println();
}
