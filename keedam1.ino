#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int motorPin1p = 7,motorPin1n=8;  // Motor 1 is at left. p indicates the positive termial.
int motorPin2p = 9,motorPin2n=10; // Motor 2 is at right. n indicates the negative terminal.
int motorOn = true; // Sets the motorPin's state.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(motorPin1p,OUTPUT);  // Setting motor 1 positive as output.
  pinMode(motorPin1n,OUTPUT);  // Setting motor 1 negative as output.
  pinMode(motorPin2p,OUTPUT);  // Setting motor 2 positive as output.
  pinMode(motorPin2n,OUTPUT);  // Setting motor 2 negative as output.
  digitalWrite(motorPin1n,LOW); // The negative pins always stay at LOW output.
  digitalWrite(motorPin2n,LOW); // While the positive pins will be varying in the output signals.
}

void loop() {
  delay(1000);    // Wait 1000ms between pings. (Can be different for different motor speeds.)
  int dist = checkDist();
  Serial.print(dist); 
  if(dist <=5)
  {
    Serial.println("cm : Obstruction detected");
    halt(motorOn);  // Stop the bot motion till it manuevers.
    maneuver();
    motorOn = true; // Starts up the bot motion.
  }
  else
  {
    Serial.println("Path clear.");
  }
  
  digitalWrite(motorPin1p,motorOn);
  digitalWrite(motorPin2p,motorOn);

}

void halt(int motorOn){  // Stops the bot.
  motorOn = false;
  digitalWrite(motorPin1p,motorOn);
  digitalWrite(motorPin2p,motorOn);
}

void left() {
   Serial.println("Started left movement");
   digitalWrite(motorPin2p,true);
   delay(400);
   digitalWrite(motorPin2p,false);
   Serial.println("Moved left!");
}


void right() {
   Serial.println("Started right movement");  
   digitalWrite(motorPin1p,true);
   delay(400);
   digitalWrite(motorPin1p,false);
   Serial.println("Moved right! I am always right baby! :*");
}


int checkDist(){
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int dist = uS / US_ROUNDTRIP_CM; // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
  return dist;
}


void maneuver(){
  Serial.println("Starting maneuver.");
  left();
  int lDist = checkDist(), rDist;
  Serial.println("Took left distance moving to right path to check the right path distance for best path.");
  turnBack();
  rDist = checkDist();
  if ( lDist <= 10)
  {
    Serial.println(lDist + " Left is not an option.");
    if (rDist <= 10){
      Serial.println(rDist + " Right is also not an option.\n Going Back!");
      right();  
    }
  }
  else{
    Serial.println(lDist + " Left might be an option. Checking right path distance.");
    if (rDist <= 10 || rDist < lDist)
    {
      Serial.println(rDist + " Right is not an option. Going to left path.");
      turnBack();
    }
    Serial.println(rDist + " Right is the best available option.");
  }
  Serial.println("Finished maneuver.");    
}

void turnBack(){
  Serial.println("Starting turn back movement");
  digitalWrite(motorPin2p,true);
  delay(800);
  digitalWrite(motorPin1p,false);
  Serial.println("Finished turn back movement");
}
