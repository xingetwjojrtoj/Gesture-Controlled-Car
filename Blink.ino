#include <ESP8266WiFi.h>

const char* ssid = "Dishank";         // Replace with your network SSID
const char* password = "dishankj"; // Replace with your network password

void setup() {
  Serial.begin(9600); // Start the Serial communication
  delay(10);

  // Connecting to Wi-Fi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  // Nothing needed here for this example
}


// Dishank: 192.168.74.232


// int mr1= D5;  //motor right 1
  
// int ml1 =D6;   //motor left 1




// int led =13;
// int enr  =D1; 
// int enl  =D2;

// int vspeed=255;    
// int tspeed=80;
// int tdelay=20;

// void   setup()
// {
//  pinMode(mr1,OUTPUT);
 
//  pinMode(ml1,OUTPUT);
   
//  pinMode(led,OUTPUT);
 
   
//  delay(2000);
// }

// void loop()
// {
 
//    digitalWrite(mr1,HIGH);
//  analogWrite (enr,vspeed);
//   delay(1000);
//   digitalWrite(mr1,LOW);
//   analogWrite (enr,vspeed);
//   delay(1000);

//  // left(); //belok kiri

 
  
    
  
  
  
// }

// void forward()
//  {
//   digitalWrite(mr1,HIGH);
   
//   digitalWrite(ml1,HIGH);
 
//    analogWrite (enr,vspeed);
//   analogWrite (enl,vspeed);
//    delay(tdelay);
//  } 

// void backward()
//    {
//   digitalWrite(mr1,LOW);
  
//   digitalWrite(ml1,LOW);
   
//   digitalWrite (enr,vspeed);
//   digitalWrite (enl,vspeed);
//    delay(tdelay);
//    }

// void right()
//  {
//   digitalWrite(mr1,LOW);
  
//    digitalWrite(ml1,HIGH);
  
//   digitalWrite (enr,tspeed);
//    digitalWrite (enl,tspeed);
//   delay(tdelay);
//  } 

// void left()
//  {
//    digitalWrite(mr1,HIGH);
  
//   digitalWrite(ml1,LOW);
   
//   digitalWrite (enr,tspeed);
//   digitalWrite (enl,tspeed);
//    delay(tdelay);
// }
