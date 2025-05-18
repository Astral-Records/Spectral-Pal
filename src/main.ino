const int LED_GREEN = 3; 
const int LED_RED = 4;           
const int TRIGGER_PIN = 9;   // sending v              
const int ECHO_PIN= 10;   // recieving v
const int BUZZER_PIN = 6;
const float MS = 0.0343;

long duration; //long cuz int holds smaller values
int distance;
int prevDist = 0; // saved value so that it wont print  
			             // same values repeatedly

bool buzzON = false;



void setup() {

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT); 
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  

  Serial.println();
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.print(".");
  delay(500);
  Serial.println();
  
}


void loop(){
  
digitalWrite(TRIGGER_PIN, LOW); //clearing prev signals
  delayMicroseconds(2);
  
digitalWrite(TRIGGER_PIN, HIGH); //sending value to trigger
  delayMicroseconds(10);
digitalWrite(TRIGGER_PIN, LOW);
 
duration = pulseIn(ECHO_PIN, HIGH, 17500); 
//measures s-6 how long stays HIGH
  
// timeout if after 3 meters there is no response - 
//measuring again

  // (2*300cm)/0.0343cm =17,490 s-6

//distance in cm
distance = duration*MS/2.0;
//cuz 343m/s sound + bounces back thus /2
  							                      //2.0 float
 
  
//distance check:
  if(distance != prevDist){
    
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.print("cm");  
    
//text
    
	if (distance>0 && distance<=20) {  
     Serial.println(" - Too close to the screen pal !");
     delay(100); 
      
    } else{
      Serial.println(" - OH YEAH keep that distance !!");
      delay(100);
    }
    
prevDist = distance;
   
  
//buzz 
    
	if (distance>0 && distance<=20) {  
      if(!buzzON){

       tone(BUZZER_PIN, 440);
       buzzON = true;
      }
    
    } else{
      if (buzzON){
        noTone(BUZZER_PIN);
        buzzON = false;
      }
 }
    
    
 //flickering leds - gotta redo this part with millis() proly cuz no flicker so far
    
	if (distance>0 && distance<=20) {  

     digitalWrite(LED_GREEN, LOW); 
     digitalWrite(LED_RED, HIGH);                     
 } else {
     digitalWrite(LED_RED, LOW);    
     digitalWrite(LED_GREEN, HIGH); 

 }
   
    
 }
}
