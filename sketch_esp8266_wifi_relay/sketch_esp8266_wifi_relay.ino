#include <stdio.h>
#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "wifi_config.h" //Custom WIFI Configuration
#include "index.h" //Custom HTML webpage contents


/**
 * Basic Declarations and Macros
 */
#define ARR_LEN(x) (sizeof(x) / sizeof((x)[0]))

#define TRUE  1
#define FALSE 0
#define CONST_WIFI_IOT_ON "btn-iot-on"
#define CONST_WIFI_IOT_OFF "btn-iot-off"
#define CONST_WIFI_IOT_DISABLED "btn-iot-disabled"


/**
 * Constant variables
 */
const int CONST_DEFAULT_LED = 13; //Near antenna LED light
const char* CONST_WIFI_SSID = WIFI_SSID;
const char* CONST_WIFI_PWD = WIFI_PWD;


/**
 * Custom Data Structure
 */
typedef struct {
  String pin_name;
  int pin_code;
  String pin_mapper;
  int is_active;
} DigitalPinData;


DigitalPinData PIN_DATA[] = {
  { "[BTN_IOT_0]", 16, CONST_WIFI_IOT_OFF, TRUE },
  { "[BTN_IOT_1]",  5, CONST_WIFI_IOT_OFF, TRUE },
  { "[BTN_IOT_2]",  4, CONST_WIFI_IOT_OFF, TRUE },
  { "[BTN_IOT_3]",  0, CONST_WIFI_IOT_OFF, TRUE },
  { "[BTN_IOT_4]",  2, CONST_WIFI_IOT_OFF, FALSE },
  { "[BTN_IOT_5]", 14, CONST_WIFI_IOT_OFF, FALSE },
  { "[BTN_IOT_6]", 12, CONST_WIFI_IOT_OFF, FALSE },
  { "[BTN_IOT_7]", 13, CONST_WIFI_IOT_OFF, FALSE },
  { "[BTN_IOT_8]", 15, CONST_WIFI_IOT_OFF, FALSE },
  { "[BTN_IOT_9]",  3, CONST_WIFI_IOT_OFF, FALSE }
};


/**
 * Create an instance of the server
 * specify the port to listen on as an argument
 */
ESP8266WebServer server(80);


/**
 * Sketch Start
 */
void setup() {
  //Preset the default led, before connecting
  pinMode(CONST_DEFAULT_LED, OUTPUT);
  digitalWrite(CONST_DEFAULT_LED, 0);
  
  //Set Baud rate
  Serial.begin(115200);
  delay(10);

  //Connect with WiFi
  WiFi.mode(WIFI_STA);
  WiFi.begin(CONST_WIFI_SSID, CONST_WIFI_PWD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  } //Loop ends

  //Connection successful
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(CONST_WIFI_SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
  } //End if

  //Route configurations
  server.on("/", handleRoot);
  server.on("/esp8266", handleForm);
  server.onNotFound(handleNotFound); //Not found event

  //Start the server
  server.begin();
  Serial.println("HTTP server started");
} //Function ends


void loop() {
  server.handleClient();
  MDNS.update();
} //Function ends


/**
 * This routine is executed on opening the browser with IP address
 **/
void handleRoot() {
  //Read HTML contents
  String html_custom = FPSTR(CUSTOM_HTML_PAGE_CONNECTED);
  
  //Get the length of the array
  size_t arrlen = ARR_LEN(PIN_DATA);

  //Loop the array and update field data
  for(int i=0;i<arrlen;i++) {
    //Check if the button is enabled
    if (PIN_DATA[i].is_active==TRUE) {
      html_custom.replace(PIN_DATA[i].pin_name, PIN_DATA[i].pin_mapper);

      //Set the pin value
      pinMode(PIN_DATA[i].pin_code, OUTPUT);
      digitalWrite(PIN_DATA[i].pin_code, ((PIN_DATA[i].pin_mapper==CONST_WIFI_IOT_ON))?HIGH:LOW);
    } else { 
      html_custom.replace(PIN_DATA[i].pin_name, CONST_WIFI_IOT_DISABLED);

      //Set the pin value to LOW
      pinMode(PIN_DATA[i].pin_code, OUTPUT);
      digitalWrite(PIN_DATA[i].pin_code, LOW);
    } //End if
  } //Loop ends

  //Send web page
  server.send(200, "text/html", html_custom); 
} //Function ends


/**
 * This routine is executed on browser address
 **/
void handleNotFound() {

} //Function ends


/**
 * This routine is executed on webform submit
 **/
void handleForm() {
  //IOT button form value
  String iot_button = server.arg("iot_button");

  //Selected Pin Data
  int intIotButtonId = iot_button.toInt();
  DigitalPinData selPinData = PIN_DATA[intIotButtonId];

  //Check of the pin is active
  if (selPinData.is_active == TRUE) {
    //Read Pin value
    pinMode(selPinData.pin_code, OUTPUT);
    int isIotButtonOff=(digitalRead(selPinData.pin_code)>0)?1:0;

    //Toggle the pin status
    int btnToggleState = (isIotButtonOff==0)?1:0;
    String btnState=btnToggleState?CONST_WIFI_IOT_ON:CONST_WIFI_IOT_OFF;
    digitalWrite(selPinData.pin_code, (btnToggleState)?HIGH:LOW);

    //Set pint status
    selPinData.pin_mapper=btnState;
  } //End if

  //Update Array
  PIN_DATA[intIotButtonId]=selPinData;

  //Redirect the page back
  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //This Line Keeps It on Same Page
   
  delay(500);
} //Function ends