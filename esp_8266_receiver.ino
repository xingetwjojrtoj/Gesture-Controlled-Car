#include <ESP8266WiFi.h>

int LBW1=D0;
int LBW2=D1;
int RBW1=D2;  
int RBW2=D3;
int LFW1=D4;
int LFW2=D5; 
int RFW1=D6; 
int RFW2=D7;

int highSpeedf = 255;
int lowSpeedf =0;

const char* ssid = "Dishank";
const char* password = "dishankj";

// Define server IP and port
const int serverPort = 80; // Port number for TCP server

WiFiServer server(serverPort);

void setup() {
  Serial.begin(9600);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print("wifi not connected");
  }

  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP()); // Print the ESP8266 IP address

  // Set motor pins as outputs
  // pinMode(DIR_PIN_M1, OUTPUT);
  // pinMode(DIR_PIN_M2, OUTPUT);
  pinMode(LBW1,OUTPUT);
  pinMode(LBW2,OUTPUT);
  pinMode(LFW1,OUTPUT);
  pinMode(LFW2,OUTPUT);
  pinMode(RBW1,OUTPUT);
  pinMode(RBW2,OUTPUT);
  pinMode(RFW1,OUTPUT);
  pinMode(RFW2,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  // pinMode(PWM_PIN_M1, OUTPUT);
  // pinMode(PWM_PIN_M2, OUTPUT);

  // Initialize motors to stopped state
  stopMoving();

  // Start the server
  server.begin();
  Serial.println("Server started");
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    Serial.println("Client connected");
    while (client.connected()) {
      while (client.available() > 0) {
        char command = client.read();
        Serial.print("Received command: ");
        Serial.println(command);

        // Process the received command
        switch(command) {
          case 'f' : {
            Serial.println("Forward");
            moveForward();
            break;
          }
          case 'b' : {
            Serial.println("Backward");
            moveBackward();
            break;
          }
          case 'a' : {
            Serial.println("Move Sideways Right");
            moveSidewaysRight();
            break;
          }
          case 'c' : {
            Serial.println("Move Sideways Left");
            moveSidewaysLeft();
            break;
          }
          case 'd' : {
            Serial.println("Rotate Left");
            rotateLeft();
            break;
          }
          case 'e' : {
            Serial.println("Rotate Right");
            rotateRight();
            break;
          }
          case 'g' : {
            Serial.println("Move Right Forward");
            moveRightForward();
            break;
          }
          case 'h' : {
            Serial.println("Move Right Backward");
            moveRightBackward();
            break;
          }
          case 'i' : {
            Serial.println("Move Left Forward");
            moveLeftForward();
            break;
          }
          case 'j' : {
            Serial.println("Move Left Backward");
            moveLeftBackward();
            break;
          }
          case 's' : {
            Serial.println("STOP");
            stopMoving();
            break;
          }
          default:
          break;

        }
      }
        // if (command == "0") {
        //   stopMotors();
        // } else if (command == "1") {
        //   moveForward();
        // } else if (command == "2") {
        //   moveBackward();
        // } else if (command == "3") {
        //   turnRight();
        // } else if (command == "4") {
        //   turnLeft();
        // }

        // Optionally send a response back to the client
        //Serial.println("Command received");
        delay(2);
      }
    client.stop();
    Serial.println("Client disconnected");
    }
     else {
    // No client connected
    Serial.println("Client not connected");
  }
  }


void moveForward() {
  digitalWrite(LFW1,HIGH);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,HIGH);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,HIGH);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,highSpeedf);
  delay(1000);
}

void moveBackward() {
  digitalWrite(LFW1,LOW);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,LOW);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,LOW);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,LOW);
  analogWrite(RBW2,highSpeedf);
delay(1000);}
void moveSidewaysRight() {
  digitalWrite(LFW1,HIGH);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,LOW);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,LOW);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,highSpeedf);
delay(1000);}
void moveSidewaysLeft() {
  digitalWrite(LFW1,LOW);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,HIGH);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,HIGH);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,LOW);
  analogWrite(RBW2,highSpeedf);
delay(1000);}
void rotateLeft() {
  digitalWrite(LFW1,LOW);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,HIGH);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,LOW);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,highSpeedf);
delay(1000);}
void rotateRight() {
  digitalWrite(LFW1,HIGH);
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,LOW);
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LBW1,HIGH);
  analogWrite(LBW2,highSpeedf);
  digitalWrite(RBW1,LOW);
  analogWrite(RBW2,highSpeedf);
delay(1000);}
void moveRightForward() {
  digitalWrite(LFW1,HIGH); //1
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,LOW);
  analogWrite(RFW2,lowSpeedf);
  digitalWrite(LBW1,HIGH);
  analogWrite(LBW2,lowSpeedf);
  digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,highSpeedf);  //3
delay(1000);}
void moveRightBackward() {
  digitalWrite(RFW1,LOW);  //2
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LFW1,HIGH); //1
  analogWrite(LFW2,lowSpeedf);
 digitalWrite(LBW1,LOW);
 analogWrite(LBW2,highSpeedf);   //4
 digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,lowSpeedf);  //3
delay(1000);}
void moveLeftForward() {
  digitalWrite(RFW1,HIGH);  //2
  analogWrite(RFW2,highSpeedf);
  digitalWrite(LFW1,HIGH); //1
  analogWrite(LFW2,lowSpeedf);
 digitalWrite(LBW1,HIGH);
 analogWrite(LBW2,highSpeedf);
 digitalWrite(RBW1,HIGH);
  analogWrite(RBW2,lowSpeedf);  //3
    delay(1000);//4
}
void moveLeftBackward() {
  digitalWrite(LFW1,LOW); //1
  analogWrite(LFW2,highSpeedf);
  digitalWrite(RFW1,HIGH);  //2
  analogWrite(RFW2,lowSpeedf);
  digitalWrite(RBW1,LOW);
  analogWrite(RBW2,highSpeedf);  //3
  digitalWrite(LBW1,HIGH);
 analogWrite(LBW2,lowSpeedf);
delay(1000);}
void stopMoving() {
  digitalWrite(LFW1,LOW); //1
  analogWrite(LFW2,lowSpeedf);
  digitalWrite(RFW1,LOW);  //2
  analogWrite(RFW2,lowSpeedf);
 digitalWrite(LBW1,LOW); 
 analogWrite(LBW2,lowSpeedf);   //4
  digitalWrite(RBW1,LOW);
  analogWrite(RBW2,lowSpeedf);  //3
delay(1000);}
