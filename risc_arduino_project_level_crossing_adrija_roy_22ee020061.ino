//Source Code for Arduino 1
int RED = 11; //Home signal red light
int YELLOW = 12; //Home signal yellow light
int GREEN = 13; //Home signal green light
int CSRED1=6; // light on crossing signal
int CSRED2=5; // light on crossing signal

int sensor1 = 10; //pir sensor 1
int sensor2 = 9; //pir sensor 2

int valA1=LOW; //sensor1 radiation state
int valA2=LOW; //sensor2 radiation state

//to differentiate different signal states
enum SIGNAL_STATES
{
  ST_RED,
  ST_YELLOW,
  ST_GREEN,
};
SIGNAL_STATES signalState=ST_GREEN;


void setup()
{
  pinMode(RED, OUTPUT);
  pinMode(GREEN,OUTPUT);
  pinMode(YELLOW,OUTPUT);
  pinMode(CSRED1,OUTPUT);
  pinMode(CSRED2,OUTPUT);
  pinMode(sensor1, INPUT);
  pinMode(sensor2, INPUT);
  Serial.begin(9600); //exchanges messages with the Serial Monitor at a data rate of 9600 bits per second
}
void crossingoff() //funtion for level crossing light is off
{
  digitalWrite(CSRED1,LOW);
  digitalWrite(CSRED2,LOW);
}
void crossingon() //function for level crossing light is on and blinking
{
  digitalWrite(CSRED1,HIGH);
  digitalWrite(CSRED2,LOW);
  delay(500);  // this is half of the flashing signal and it goes for 0.5 seconds
  digitalWrite(CSRED1,LOW);
  digitalWrite(CSRED2,HIGH);
  delay(500);
}

void loop()
{
  valA1 = digitalRead(sensor1);
  valA2 = digitalRead(sensor2);
  
  switch(signalState) //specifying functions to be called for different signal states
  {
    case ST_RED:
    signalred(valA1,valA2);
    break;
    case ST_YELLOW:
    signalyellow(valA1,valA2);
    break;
    case ST_GREEN:
    signalgreen(valA1,valA2);
    break;
  }
  delay(100); // Wait for 10 millisecond(s)
}

  
  void signalred(int valA1,int valA2)
  {
    digitalWrite(RED, HIGH);
    digitalWrite(YELLOW,LOW);
    digitalWrite(GREEN, LOW);
    crossingon();
    
    if(valA1 == LOW && valA2==HIGH)//as train moves from sensor1 to sensor2
      signalState=ST_YELLOW;
  }
  
  void signalyellow(int valA1,int valA2)
  {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW,HIGH);
    digitalWrite(GREEN, LOW);
    crossingon();

    if(valA1 == LOW && valA2==LOW) //as train exits sensor2 range
      signalState=ST_GREEN;
  }
  
  void signalgreen(int valA1,int valA2)
  {
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW,LOW);
    digitalWrite(GREEN, HIGH);
    crossingoff();
    if(valA1 == HIGH && valA2==LOW) //as train enters sensor1 range
      signalState=ST_RED;
  }