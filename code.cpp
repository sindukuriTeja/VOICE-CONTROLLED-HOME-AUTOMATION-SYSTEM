//Voice Controlled Light
String voice;
#define relay1 10
#define relay2 11
#define relay3 12
#define relay4 13
#define echo A4 // echo pin
#define trig A5 // Trigger pin
int sensorPin = A0; // select the input pin for the LDR
int sensorValue = 0; // variable to store the value coming from the sensor
void setup() 
{                                            // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  digitalWrite(relay4, LOW);
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);
  delay(1000);
  delay(1000); 
  digitalWrite(relay1, LOW); 
  digitalWrite(relay2, LOW);
  digitalWrite(relay3, LOW);
  digitalWrite(relay3, LOW);
  pinMode(relay4, OUTPUT); 
  pinMode (trig, OUTPUT);
  pinMode (echo, INPUT);
}

  int relayVal; 

void loop() {
 
  while (Serial.available())   //Check if there is an available byte to read
  {                            
  delay(10);                   //Delay added to make thing stable
  char c = Serial.read();      //Conduct a serial read
  if (c == '#') {break;}       //Exit the loop when the # is detected after the word
  voice += c;                  //Shorthand for voice = voice + c
  } 
  int distance=getDistance();
  Serial.print("Distance :");
  Serial.println(distance);
  if(distance<30)
  {
     digitalWrite(relay3, HIGH);
     delay(3000);
  }
  else{
    digitalWrite(relay3,LOW);
  }
  sensorValue = analogRead(sensorPin);
  Serial.print("LDR :");
  Serial.println(sensorValue);
  if (sensorValue < 900)
  {
      Serial.println("LED light on");
      digitalWrite(relay4, HIGH);
      delay(1000);
  }
  else{
    digitalWrite(relay4, LOW);
    delay(100);
  }
  if (voice.length() > 0) {
    Serial.println(voice);
  //----------Control Light----------// 
 if((voice == "*turn on the light white")||(voice == "*Turn on the light white"))       // To tune ON the bulb                   
  {
     digitalWrite(relay1, HIGH); 
  }  
  else if((voice == "*turn off the light white")||(voice == "*Turn off the light white"))      // To turn OFF the bulb                        
  {
    digitalWrite(relay1, LOW);
  }     
  else if((voice == "*turn on the light green")||(voice == "*Turn on the light green"))       // To tune ON the bulb                   
  {
     digitalWrite(relay2, HIGH); 
  }  
  else if((voice == "*turn off the light green")||(voice == "*Turn off the light green"))      // To turn OFF the bulb                        
  {
    digitalWrite(relay2, LOW);
  } 
  else if((voice == "*turn on the light red")||(voice == "*Turn on the light red"))       // To tune ON the bulb                   
  {
     digitalWrite(relay3, HIGH); 
  }  
  else if((voice == "*turn off the light red")||(voice == "*Turn off the light red") )    // To turn OFF the bulb                        
  {
    digitalWrite(relay3, LOW);
  }
  else if((voice =="*emergency")||(voice =="*Emergency")){
    for(int i=0;i<20;i++)
    {
        digitalWrite(relay2, HIGH);
        delay(100);
        digitalWrite(relay2,LOW);
        delay(100);  
    }
  }
  else if(voice=="*turn off")
  {
    digitalWrite(relay1, LOW);
    digitalWrite(relay2, LOW);
    digitalWrite(relay3, LOW);
    digitalWrite(relay4, LOW);
  }
  voice="";                            //Reset the variable after initiating
}
}
int getDistance()
{
  digitalWrite (trig, LOW);
  delayMicroseconds (2);
  digitalWrite (trig, HIGH);
  delayMicroseconds (10);
  float duration= pulseIn (echo, HIGH);
  float distance;
  distance= (0.0061*duration) + 2.5923;
  return distance;
}
