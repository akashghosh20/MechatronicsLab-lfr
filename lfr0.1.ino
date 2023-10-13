// ----------------- Motor Pins ------------------
#define inA 3
#define inB 4
#define inC 7
#define inD 8
// Enable pin for PID
#define enA 5
#define enB 6

//------------------- PID variables -------------------
int IMS = 70 ;//initial motor speed
int LMS = 100;
int RMS = 180;

int error = 0; 
float P=0,I=0,D=0,PID=0;
float prevErr = 0; //previous error
float prevI = 0; //previous integral
float kp =22 ,kd = 38, ki = 1.7;//tune it


// ----------------- IR Array Values and other variables 
int sensorVal[8];
int sum = 0;
int lFlag=0,rFlag=0;

// ----------------- Function Prototypes -------------------
void readSensor();
void logic();
void Stop();
void Forward();
void softLeft();
void hardLeft();
void softRight();
void hardRight();
void Backward();
void Search();
void Stabilizer();
void pidExecute();
void pidFunction();


// --------------------------- Setup Function ------------------------

void setup() {
  
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(A4,INPUT);
  pinMode(A5,INPUT);
  pinMode(A6,INPUT);
  pinMode(A7,INPUT);
  Serial.begin(9600);
}


// -----------------------------  Loop Function --------------------------
void loop() {
  readSensor(); 
  logic();
  delay(2000);
}










// ------------------- Functions ----------------


// -----------> Left, Right, Forward, Stop, Search, Back <----------------

void Forward(){
  analogWrite(enA, IMS);
  analogWrite(enB, IMS);
  digitalWrite(inA, LOW); //3
  digitalWrite(inB, HIGH); //4

  digitalWrite(inC, LOW); //7
  digitalWrite(inD, HIGH); //8

  Serial.println("------------------------");
  Serial.println("Going Forward");  
}

void hardLeft(){
  analogWrite(enA, IMS);
  analogWrite(enB, IMS);

  digitalWrite(inA, HIGH);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);

  lFlag = 1;

  Serial.println("------------------------");
  Serial.println("Hard Left");  

}

void softLeft(){
  analogWrite(enA, 0);
  analogWrite(enB, IMS);

  digitalWrite(inA, LOW);
  digitalWrite(inB, LOW);
  digitalWrite(inC, LOW);
  digitalWrite(inD, HIGH);

  lFlag = 1;

  Serial.println("------------------------");
  Serial.println("Soft Left");  
}

void hardRight(){

  analogWrite(enA, IMS);
  analogWrite(enB, IMS);

  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, HIGH);
  digitalWrite(inD, LOW);

  rFlag = 1;

  Serial.println("------------------------");
  Serial.println("Hard Right");  

}

void softRight(){
  analogWrite(enA, IMS);
  analogWrite(enB, 0);

  digitalWrite(inA, LOW);
  digitalWrite(inB, HIGH);
  digitalWrite(inC, LOW);
  digitalWrite(inD, LOW);

  rFlag = 1;

  Serial.println("------------------------");
  Serial.println("Soft Right");  
}

void Stop(){
  analogWrite(enA, 0);
  analogWrite(enB, 0);

  digitalWrite(inA, LOW); //3
  digitalWrite(inB, LOW); //4
  digitalWrite(inC, LOW); //7
  digitalWrite(inD, LOW); //8

  Serial.println("------------------------");
  Serial.println("Stopped");
}

void Backward(){
  digitalWrite(inA, HIGH); //3
  digitalWrite(inB, LOW); //4

  digitalWrite(inC, HIGH); //7
  digitalWrite(inD, LOW); //8

  Serial.println("------------------------");
  Serial.println("Going Backrward");  
}

void Search(){
  Serial.println("------------------------");
  Serial.println("Searching "); 

  readSensor();
  if(sum > 24){
    softLeft();
  }else if(sum < 24){
    softRight();
  }else if(sum == 24){
    Forward();
  }else{
    Stop();
    delay(500);

  }
  Serial.println("------- Searching ----------");
}


// -------------------> Read Sensor and Logics <------------------

void readSensor() {
  for (int i = 0; i < 8; i++) {
    if(analogRead(i)> 500)
    {
      sensorVal[i] = 1;
    }else{
      sensorVal[i] = 0;
    }
    Serial.print(sensorVal[i]);
    Serial.print(' ');
  }
  Serial.println();
  

  sum = sensorVal[0]*128+ (sensorVal[1]*64) +(sensorVal[2]*32)+(sensorVal[3]*16)+(sensorVal[4]*8)+(sensorVal[5]*4)+(sensorVal[6]*2)+(sensorVal[7]*1);
  Serial.println(sum);
}

void logic()
{
  if(sum == 231  || sum == 246 || sum == 207 || sum == 230 || sum == 199) { //191 223 239 247 254 251 63 159 250 249 242 143
    Forward();
  }else if(sum==0){  
      Stop();
  }else if(sum == 224 || sum == 240 || sum == 192){
    softLeft();
  }else if(sum == 15 || sum == 7 || sum == 6){
    softRight();
  }else if(sum == 255){
    Search();
  }else{
    Serial.println("No condition is satisfied");
      readSensor();
      Forward();
  }
}

void Stabilizer(){
  
}

void pidFunction(){

}

void pidExecute(){

}