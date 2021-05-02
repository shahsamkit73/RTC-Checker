# RTC-Checker

Industrial prototypes typically contain legion electronics components. The failure mode of these components often happens in the circuits. However, in some case, these failure switching causes safely hazard. So, it is very essential to understand the behaviour of component to design the mechanism safe, reliant and durable. The prime idea of this project is to focus on the debacle detection of DS1307 RTC, a memory based IC, before placing /soldering in the PCB circuit.

### Dependencies & Libraries ###
* #### ESP32 IoT Development Board
* #### Arduino Environment - [ArduinoIDE](https://www.arduino.cc/en/software)
* #### DS 1307 RTC
* #### 0.96 inch I2C 128x64 OLED display module
* #### [RTClib](https://github.com/adafruit/RTClib) 
* #### [Adafruit_SSD1306](https://github.com/adafruit/Adafruit_SSD1306)
* #### [Adafruit_GFX](https://github.com/adafruit/Adafruit-GFX-Library)

### How to install libraries in Arduino IDE :
* **Method 1**
1. Go to **Tools > Board > Boards Manager** and open Boards Manager
2. Search for library name and press install

* **Method 2**
1. Go to **My Computer > Documents > Arduino > Libraries** and paste the unzipped folder

### Circuit Connection ###

<p align="center">
  <img width="1000" height="575" src="https://user-images.githubusercontent.com/43854300/116803966-c1085880-ab38-11eb-9499-056471d8a73c.JPG"
</p>

### How to convert image to Bitmap HEX code :
1. Click on the [image2cpp](https://diyusthad.com/image2cpp) button and open the application in a new tab.
2. Choose image file
3. Set image setting (**_Canvas Size, Brightness Threshold, Scaling_**)
4. Generate output and paste the HEX code in your code

**IMPORTANT: If more than one I2C suppoted modules are used then `I2C protocol address` should not be same.**
