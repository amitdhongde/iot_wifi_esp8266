#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.h" //Custom HTML webpage contents

#define PIN_D1 16 //Near power LED light
#define PIN_D2 4
#define PIN_D3 0
#define PIN_D4 2 //Near antenna LED light
#define PIN_D5 16 //Near power LED light
#define PIN_D6 4
#define PIN_D7 0
#define PIN_D8 2 //Near antenna LED light
#define PIN_D9 16 //Near power LED light
#define PIN_D10 4

/**
 * Custom Structure
 **/
typedef struct {
  int* pin;
  int pin_code;
  char* pin_mapper;
} DigitalPinData;

//ESP8266 NodeMCU Pin Confuguration
/*
const DigitalPinData PIN_DATA[] = {
  { PIN_D0, 16, STATUS_BTN1 },
  { PIN_D1,  5, STATUS_BTN2 },
  { PIN_D2,  4, STATUS_BTN3 },
  { PIN_D3,  0, STATUS_BTN4 },
  { PIN_D4,  2, STATUS_BTN5 },
  { PIN_D5, 16, STATUS_BTN6 },
  { PIN_D6, 16, STATUS_BTN7 },
  { PIN_D7, 16, STATUS_BTN8 },
  { PIN_D8, 16, STATUS_BTN9 },
  { PIN_D9, 16, STATUS_BTN10 }
};
*/

const char* _CONST_WIFI_SSID = "<ENTER_WIFI_SID>";
const char* _CONST_WIFI_PWD = "<ENTER_WIFI_PASSWORD>";

const char* _CONST_WIFI_IOT_ON  = "btn-iot-on";
const char* _CONST_WIFI_IOT_OFF = "btn-iot-off";

String STATUS_BTN1,STATUS_BTN2,STATUS_BTN3,STATUS_BTN4,STATUS_BTN5,
       STATUS_BTN6,STATUS_BTN7,STATUS_BTN8,STATUS_BTN9,STATUS_BTN10;

/**
 * Create an instance of the server
 * specify the port to listen on as an argument
 **/
//WiFiServer server(80);
ESP8266WebServer server(80);


/**
 * This routine is executed on opening the browser with IP address
 **/
void handleRoot() {
  String html_custom = CUSTOM_HTML_PAGE_CONNECTED; //Read HTML contents

  //Update field data
  html_custom.replace("[BTN_IOT_1]",  STATUS_BTN1);
  html_custom.replace("[BTN_IOT_2]",  STATUS_BTN2);
  html_custom.replace("[BTN_IOT_3]",  STATUS_BTN3);
  html_custom.replace("[BTN_IOT_4]",  STATUS_BTN4);
  html_custom.replace("[BTN_IOT_5]",  STATUS_BTN5);
  html_custom.replace("[BTN_IOT_6]",  STATUS_BTN6);
  html_custom.replace("[BTN_IOT_7]",  STATUS_BTN7);
  html_custom.replace("[BTN_IOT_8]",  STATUS_BTN8);
  html_custom.replace("[BTN_IOT_9]",  STATUS_BTN9);
  html_custom.replace("[BTN_IOT_10]", STATUS_BTN10);

  server.send(200, "text/html", html_custom); //Send web page
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

  int intIotButtonId = iot_button.toInt();
  bool isIotButtonOff = true;

  switch(intIotButtonId) {
    case 1:
      //Code here
      pinMode(PIN_D1, OUTPUT);
      isIotButtonOff=!(digitalRead(PIN_D1)>0);
      STATUS_BTN1=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      digitalWrite(PIN_D1, (isIotButtonOff)?HIGH:LOW);
      break;

    case 2:
      //Code here
      pinMode(PIN_D2, OUTPUT);
      isIotButtonOff=!(digitalRead(PIN_D2)>0);
      STATUS_BTN2=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      digitalWrite(PIN_D2, (isIotButtonOff)?HIGH:LOW);
      break;

    case 3:
      //Code here
      pinMode(PIN_D3, OUTPUT);
      isIotButtonOff=!(digitalRead(PIN_D3)>0);
      STATUS_BTN3=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      digitalWrite(PIN_D3, (isIotButtonOff)?HIGH:LOW);
      break;

    case 4:
      //Code here
      pinMode(PIN_D4, OUTPUT);
      isIotButtonOff=!(digitalRead(PIN_D4)>0);
      STATUS_BTN4=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      digitalWrite(PIN_D4, (isIotButtonOff)?HIGH:LOW);
      break;

    case 5:
      //Code here
      pinMode(PIN_D5, OUTPUT);
      isIotButtonOff=!(digitalRead(PIN_D5)>0);
      STATUS_BTN5=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      digitalWrite(PIN_D5, (isIotButtonOff)?HIGH:LOW);
      break;

    case 6:
      //Code here
      STATUS_BTN6=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      break;

    case 7:
      //Code here
      STATUS_BTN7=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      break;

    case 8:
      //Code here
      STATUS_BTN8=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      break;

    case 9:
      //Code here
      STATUS_BTN9=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      break;

    case 10:
      //Code here
      STATUS_BTN10=isIotButtonOff?_CONST_WIFI_IOT_ON:_CONST_WIFI_IOT_OFF;
      break;

    default:
      //Do nothing
      break;
  } //End switch

  server.sendHeader("Location", "/");
  server.send(302, "text/plain", "Updated-- Press Back Button");  //This Line Keeps It on Same Page
   
  delay(500);
} //Function ends


/**
 * Sketch Setup
 **/
void setup(void) {
  Serial.begin(115200);
  delay(10);

  //Preset values
  STATUS_BTN1=STATUS_BTN2=STATUS_BTN3=STATUS_BTN4=STATUS_BTN5=_CONST_WIFI_IOT_OFF;
  STATUS_BTN6=STATUS_BTN7=STATUS_BTN8=STATUS_BTN9=STATUS_BTN10=_CONST_WIFI_IOT_OFF;

  // prepare GPIO2
  pinMode(PIN_D4, OUTPUT);
  digitalWrite(PIN_D4, LOW);

  //Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(_CONST_WIFI_SSID);

  //WiFi Settings
  WiFi.mode(WIFI_STA);
  WiFi.begin(_CONST_WIFI_SSID, _CONST_WIFI_PWD);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  //Server configurations
  server.on("/", handleRoot);
  server.on("/esp8266", handleForm);
  server.onNotFound(handleNotFound); //Not found event

  //Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
} //Function ends


void loop(void) {
  server.handleClient();
} //Function ends
