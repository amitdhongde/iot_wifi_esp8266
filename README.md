# 4CH Relay Automation with ESP8266 over WiFi and RF

This is a simple Home Automation project using the DIY micro-controller (ESP8266) with firmware developed over arduino. This setup can be used to control any relay from any web browser using the wireless network. 

Alternately, the RF uses the 433MHz Receiver in case the WiFi is not available.

## Gather Materials

1. ESP8266 NodeMCU (https://www.amazon.in/Lolin-NodeMCU-ESP8266-CP2102-Wireless/dp/B010O1G1ES)
2. 4-Channel 5V Relay Module (https://www.techtonics.in/5v-10a-4-channel-opto-coupler-relay-board-module)
3. F2F JUMPER WIRES (20CM) 20PCS (https://www.olelectronics.com/F2F-Jumper-Wires--20-PCs)

All the components are avalable in the local electronics market or over Amazon online store. Please make necessary changes in the code based on the board you use.

# Configuration

1. The application uses Auduino (v1.8.13) for development or rebuilds.
2. Update [wifi_config.h](https://github.com/ellaisys/iot_wifi_esp8266/blob/master/sketch_esp8266_wifi_relay/wifi_config.h) with wifi configuration (SSID and PASSWORD).
3. Modify the arduino sketch file [sketch_esp8266_wifi_relay.ino](https://github.com/ellaisys/iot_wifi_esp8266/blob/master/sketch_esp8266_wifi_relay/sketch_esp8266_wifi_relay.ino) for the **DigitalPinData PIN_DATA** array attribute.
```c
    DigitalPinData PIN_DATA[] = {
    { "[BTN_IOT_0]", 16, CONST_WIFI_IOT_OFF, FALSE },
    { "[BTN_IOT_1]",  5, CONST_WIFI_IOT_OFF, TRUE },
    { "[BTN_IOT_2]",  4, CONST_WIFI_IOT_OFF, TRUE },
    { "[BTN_IOT_3]",  0, CONST_WIFI_IOT_OFF, TRUE },
    { "[BTN_IOT_4]",  2, CONST_WIFI_IOT_OFF, TRUE },
    { "[BTN_IOT_5]", 14, CONST_WIFI_IOT_OFF, FALSE },
    { "[BTN_IOT_6]", 12, CONST_WIFI_IOT_OFF, FALSE },
    { "[BTN_IOT_7]", 13, CONST_WIFI_IOT_OFF, FALSE },
    { "[BTN_IOT_8]", 15, CONST_WIFI_IOT_OFF, FALSE },
    { "[BTN_IOT_9]",  3, CONST_WIFI_IOT_OFF, FALSE }
    };
```

## Circuit Diagram


## Node MCU ESP-8266 Pinout Diagram

<img src="https://github.com/ellaisys/iot_wifi_esp8266/blob/master/sketch_esp8266_wifi_relay/node-mcu-esp8266-pinout.jpg" width="100%" alt="Node MCU ESP-8266 Pinout Diagram"/>