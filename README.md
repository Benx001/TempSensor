# TempSensor
c project to display the temperature from the TC74 temperature sensor

1. Clone https://github.com/Benx001/RaspberryPiPico.git in the "TempSensor" folder
2. Update the PICO_SDK_PATH path in CMakeLists.txt
3. Build the project

Update TC74 in TempSensor.c according to the sensor model, default value belongs to sensor TC74A0-3.3VCT

Raspberry Pi Pico and TC74A0-3.3VCT connection
Raspberry Pi Pico       TC74A0-3.3VCT
GP0 - i2c0 SDA          pin 2 - SDA
GP1 - i2c0 SCL          pin 4 - SCLK
                        pin 3 - GND
                        pin 5 - Vdd
                        pin 1 - NC

To display the temperature in a computer monitor:
1. Clone https://github.com/Benx001/temp-app.git
2. npm install
2. npm start
3. Connect the raspberry pi pico to the computer with an usb micro B cable
4. In the browser click Open Port button, then select the serial port and connect

Works only on chrome, edge and opera browsers (any browser that supports the Web Serial API)