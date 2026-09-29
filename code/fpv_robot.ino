what should be file name for code week 2 #include <WiFi.h>
#include <WebServer.h>

const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

// Pin mapping matching the ESP32-S3 Manual connections
int ENA = 1;   // Motor A Speed Control (PWM)
int IN1 = 2;   // Motor A Direction 1
int IN2 = 3;   // Motor A Direction 2

int IN3 = 14;  // Motor B Direction 1
int IN4 = 41;  // Motor B Direction 2
int ENB = 42;  // Motor B Speed Control (PWM)

// Speed calculations (0 to 255)
const int DRIVE_SPEED = 100;  // Reduced by 20% from 204
const int TURN_SPEED  = 75;  // Reduced by an extra 20% for smooth turning

void setup() {
  Serial.begin(115200);

  // Set motor control pins as outputs
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Connect to WiFi with 0 delay loop
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(0); 
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // ROUTES (Commands from App)
  server.on("/f", forward);
  server.on("/b", backward);
  server.on("/l", left);
  server.on("/r", right);
  server.on("/s", stopMotor);

  server.begin();
}

void loop() {
  server.handleClient();
}

//
// 🚗 MOVEMENT FUNCTIONS
//

void forward() {
  analogWrite(ENA, DRIVE_SPEED);
  analogWrite(ENB, DRIVE_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Forward");
}

void backward() {
  analogWrite(ENA, DRIVE_SPEED);
  analogWrite(ENB, DRIVE_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  server.send(200, "text/plain", "Backward");
}

void left() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  server.send(200, "text/plain", "Left");
}

void right() {
  analogWrite(ENA, TURN_SPEED);
  analogWrite(ENB, TURN_SPEED);

  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  server.send(200, "text/plain", "Right");
}

void stopMotor() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  server.send(200, "text/plain", "Stop");
} also put placeholder wehere required
