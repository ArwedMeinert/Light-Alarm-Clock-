#define DS1307_ADDRESS 0x68

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET     -1
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define transistor 16
#define button 25
#define poti 34
#include <WiFi.h>
  #include <WiFiClient.h>
#include <WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Arduino.h>
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
 const char* ssid = "your SSID";
const char* password = "Your Password";
WebServer server(80);
String currentTime;
String alarmTime;
int year ;
int month ;
int day ;
int hour ;
int minute ;
int potvalue=0;
bool buttonState = false;
bool PhysicalButton;
void handleRoot() {
  String html = "<html><body><h1>ESP8266 Web Server</h1>"
                "<p>Current time: " + currentTime + "</p>"
                "<form action='/setAlarm' method='POST'>"
                "<label for='alarm'>Set alarm time:</label>"
                "<input type='text' name='alarm' value='" + alarmTime + "'>"
                "<br><br>"
          
               
                "<label for='button'>Button state:</label>"
                "<input type='text' name='button' value='" + (buttonState ? "pressed" : "not pressed") + "'>"
                "<br><br>"
                
                "<input type='submit' value='Set Alarm'>"
                "</form>"
                "</body></html>";
  server.send(200, "text/html", html);
}
void handleSubmit() {
  Serial.println("submitted");
  alarmTime = server.arg("alarm");
  
  buttonState = (server.arg("button") == "pressed");
  server.send(200, "text/html", "<html><body><h1>Data received</h1>"
                                 "<p>Alarm time: " + alarmTime + "</p>"
                
                "<p>Button state: " + (buttonState ? "pressed" : "not pressed") + "</p>"
                "<br><br>"
                "<a href='/'>Go back</a>"
                "</body></html>");
}
void setButtonState(bool state) {
  buttonState = state;
}


void setup() {
  // put your setup code here, to run once:
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  pinMode(button, INPUT_PULLUP);
  ledcAttachPin(27, 0);
  ledcSetup(0, 5000, 8);
 

Wire.begin();
  Serial.begin(9600);
  WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
timeClient.begin();
  timeClient.setTimeOffset(3600);
  server.on("/", handleRoot);
  server.on("/setAlarm", handleSubmit);
  server.begin();
  Serial.println("Web server started");
 Serial.println(WiFi.localIP());
display.clearDisplay();
 
}

void loop() {
  potvalue=analogRead(poti);
  timeClient.update();
  if(timeClient.getFormattedTime()!=currentTime){
  int hour, minute, second;
  String formattedTime=timeClient.getFormattedTime();
    int firstColon = formattedTime.indexOf(":");
  int secondColon = formattedTime.indexOf(":", firstColon + 1);

  String hourString = formattedTime.substring(0, firstColon);
  String minuteString = formattedTime.substring(firstColon + 1, secondColon);
  String secondString = formattedTime.substring(secondColon + 1);

  hour = hourString.toInt();
  minute = minuteString.toInt();
  second = secondString.toInt();
  setDateTime(hour, minute, second);
  }
refreshTime();
display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(currentTime.substring(0,5));
  display.setCursor(0, 40);
  if(alarmTime.substring(0,5)==""){
display.println("Alarm");
    
  }else{
  display.println(alarmTime.substring(0,5));
  }
  display.display(); 
Serial.println(buttonState);
if(digitalRead(button)==0){
buttonState= not(buttonState);
  delay(500);
}
if(currentTime.substring(0,5)==alarmTime.substring(0,5)){
for(int i=0;i<=255;i++){
ledcWrite(0,i);
delay(150);
display.clearDisplay();
  display.setTextSize(3);
  display.setTextColor(WHITE);
  display.setCursor(0, 10);
  // Display static text
  display.println(currentTime.substring(0,5));
  display.setCursor(0, 40);
  if(alarmTime.substring(0,5)==""){
display.println("Get Up");
    
  }else{
  display.println(alarmTime.substring(0,5));
  }
  display.display(); 
  }
  delay(4000);
ledcWrite(0,0);
  
}
if(buttonState==true){

  ledcWrite(0,map(potvalue, 0, 4095, 0, 255));
}else{
ledcWrite(0,0);
  
}





//Serial.println(currentTime);// use a dummy time value for demonstration purposes
  server.handleClient();

}
  // put your main code here, to run repeatedly:
  //for(int i=0;i<=255;i++){
//analogWrite(transistor, i);
//delay(10);
 // }
 // for(int i=255;i>=0;i--){
//analogWrite(transistor, i);
//delay(10);
//  }
//}

void setDateTime(int hour, int minute, int second)
{


  // The following codes transmits the data to the RTC
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(byte(0));
  Wire.write(decToBcd(second));
  Wire.write(decToBcd(minute));
  Wire.write(decToBcd(hour));
  Wire.write(decToBcd(1));
  Wire.write(decToBcd(1));
  Wire.write(decToBcd(1));
  Wire.write(decToBcd(1));
  Wire.write(byte(0));
  Wire.endTransmission();
}

byte readByte()
{
  while (!Serial.available()) {
    delay(10);
  }
  byte reading = 0;
  byte incomingByte = Serial.read();
  while (incomingByte != '\n') {
    if (incomingByte >= '0' && incomingByte <= '9') {
      reading = reading * 10 + (incomingByte - '0');
  }
    incomingByte = Serial.read();
  }
  Serial.flush();
  return reading;
}

/**
 * Prints the current date/time set in the RTC module to the serial monitor
 */
void refreshTime()
{
  Wire.beginTransmission(DS1307_ADDRESS);
  Wire.write(0x00);
  Wire.endTransmission();
  Wire.requestFrom(DS1307_ADDRESS, 7);

  byte nowSeconds = bcdToDec(Wire.read());
  byte nowMinute = bcdToDec(Wire.read());
  byte nowHour = bcdToDec(Wire.read() & 0b111111);
  byte nowWeekDay = bcdToDec(Wire.read());
  byte nowMonthDay = bcdToDec(Wire.read());
  byte nowMonth = bcdToDec(Wire.read());
  byte nowYear = bcdToDec(Wire.read());

  char data[] = "";
  sprintf(data, "%02d:%02d:%02d",nowHour, nowMinute, nowSeconds);
  currentTime=data;
}

/**
 * Converts a decimal (Base-10) integer to BCD (Binary-coded decimal)
 */
int decToBcd(int value)
{
  return ((value/10*16) + (value%10));
}

/**
 * Converts a BCD (Binary-coded decimal) to decimal (Base-10) integer
 */
int bcdToDec(int value)
{
  return ((value/16*10) + (value%16));
}
