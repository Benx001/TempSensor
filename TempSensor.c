/*
c project to display the temperature from the TC74 temperature sensor
    Copyright (C) 2022  Benjamín Morales

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "RaspberryPiPico/libraries/c/PCD8544/PCD8544.h"
#include "RaspberryPiPico/libraries/c/PCD8544/PCD8544.c"

const uint I2C_SDA = 0;
const uint I2C_SCL = 1;
i2c_inst_t *I2C_PORT = i2c0;

// I2C address
static const uint8_t TC74 = 72; //TC74A0-3.3VCT
// Commands
static const uint8_t *TC74_ReadTemp = 0x00;

int8_t din = 11;
int8_t sclk = 10;
int8_t dc = 12;
int8_t rst = 14;
int8_t cs = 13;

int contrast = 45;

int main()
{
    stdio_init_all();

    i2c_init(I2C_PORT, 50 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
    i2c_set_slave_mode(i2c0, false, TC74);

    LCDInit(sclk, din, dc, cs, rst, contrast);
    LCDclear();

    uint8_t data[1];
    data[0] = 0x00;

    int8_t pretemp = -128;

    sleep_ms(2000);
    for (;;)
    {
        sleep_ms(1000);
        uint8_t temp[1] = {0};
        int ret = 0;

        i2c_write_blocking(i2c0, TC74, TC74_ReadTemp, 1, true);
        ret = i2c_read_blocking(i2c0, TC74, temp, 1, false);

        printf("%c",temp[0]);
        
        char c[50];
        int8_t thetemp = temp[0];
        if(temp[0]>127){
            thetemp = (257+~(temp[0]))*(-1);
        }
        if(pretemp!=-128){
            sprintf(c, "Pre. Temp:%d\n", pretemp);
        }else{
            sprintf(c, "Pre. Temp: NA");
        }
        if((thetemp < pretemp+3) && (thetemp > pretemp-3)){
            continue;
        }
        LCDclear();
        LCDdrawstring(0, 0, c);
        LCDdrawline(0, 10, 83, 10, BLACK);
        sprintf(c, "Temp: %d\n", thetemp);
        LCDdrawstring(0, 12, c);
        LCDdrawline(0, 20, 83, 20, BLACK);
        LCDdisplay();
        pretemp = thetemp;
    }

    return 0;
}
