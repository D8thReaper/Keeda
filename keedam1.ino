// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  12  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     11  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int motorPin1p = 7,motorPin1n=8,motorOn=true,motorPin2p = 9,motorPin2n=10; // Motor 1 is at left and motor 2 is at right.
int motor1P,motor1N,motor2P,motor2N;
int time = 0;


NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  pinMode(motorPin1p,OUTPUT);  // Setting motor 1 positive as output.
  pinMode(motorPin1n,OUTPUT);  // Setting motor 1 negative as output.
  pinMode(motorPin2p,OUTPUT);  // Setting motor 2 positive as output.
  pinMode(motorPin2n,OUTPUT);  // Setting motor 2 negative as output.
  digitalWrite(motorPin1n,LOW); 
  digitalWrite(motorPin2n,LOW);  
}

void loop() {
  delay(1000);                      // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  unsigned int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  Serial.print("Ping: ");
  int dist = uS / US_ROUNDTRIP_CM;
  if(dist <=5)
  {
    Serial.print(uS / US_ROUNDTRIP_CM); // Convert ping time to distance and print result (0 = outside set distance range, no ping echo)
    Serial.println("cm \n Pass aa gaya bete");
    motorOn = false;
    right();
    motorOn = true;
  }
  else
  {
    Serial.println("Too far");
    motorOn = true;
  }
  
  digitalWrite(motorPin1p,motorOn);
  digitalWrite(motorPin2p,motorOn);

}

void left() {
   Serial.println("Started left movement");
   
   digitalWrite(motorPin1p,false);
   delay(400);
   Serial.println("Moved left");
}


void right() {
   Serial.println("Started right movement");
   
   digitalWrite(motorPin2p,false);
   delay(400);
   Serial.println("Right ho gaya ye to!");
}
