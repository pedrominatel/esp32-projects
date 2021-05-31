| Supported Targets | ESP32 | ESP32-S2 | ESP32-C3 |
| ----------------- | ----- | -------- | -------- |

# I2S Digital Microphone Spectrum Example

(See the README.md file in the upper level 'examples' directory for more information about examples.)

In this example, the audio is captured from a PDM MEMS microphone connected on the I2S peripheral to generate and display a spectrum using FFT from esp-dsp library.

## How to Use Example

### Hardware Required

* A development board with ESP32 SoC (e.g., ESP32-DevKitC, ESP-WROVER-KIT, etc.)
* A USB cable for power supply and programming
* A digital microphone (SPK0838HT4H PDM output was used in this example)

The digital PDM microphone is connected on the I2S interface `I2S_NUM_0`.

|Mic|GPIO|
|:---:|:---:|
|PDM Clock|GPIO22|
|PDM Data|GPIO23|

### Configure the Project

```
idf.py menuconfig
```

### Build and Flash

Build the project and flash it to the board, then run monitor tool to view serial output:

```
idf.py -p PORT flash monitor
```

(To exit the serial monitor, type ``Ctrl-]``.)

See the Getting Started Guide for full steps to configure and use ESP-IDF to build projects.

[ESP-IDF Getting Started Guide on ESP32](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html)

[ESP-IDF Getting Started Guide on ESP32-S2](https://docs.espressif.com/projects/esp-idf/en/latest/esp32s2/get-started/index.html)

[ESP-IDF Getting Started Guide on ESP32-C3](https://docs.espressif.com/projects/esp-idf/en/latest/esp32c3/get-started/index.html)

## Example Output

Running this example, you will see the Bits per Sample changes every 5 seconds after you have run this example. You can use `i2s_set_clk` to change the Bits per Sample and the Sample Rate. The output log can be seen below:

```
I (31) boot: ESP-IDF qa-test-v4.3-20210128-117-gb02b 2nd stage bootloader
I (31) boot: compile time 12:01:19
I (32) boot: chip revision: 1
I (36) boot_comm: chip revision: 1, min. bootloader chip revision: 0
I (43) boot.esp32: SPI Speed      : 40MHz
I (48) boot.esp32: SPI Mode       : DIO
I (52) boot.esp32: SPI Flash Size : 2MB
I (57) boot: Enabling RNG early entropy source...
I (62) boot: Partition Table:
I (66) boot: ## Label            Usage          Type ST Offset   Length
I (73) boot:  0 nvs              WiFi data        01 02 00009000 00006000
I (80) boot:  1 phy_init         RF data          01 01 0000f000 00001000
I (88) boot:  2 factory          factory app      00 00 00010000 00100000
I (95) boot: End of partition table
I (100) boot_comm: chip revision: 1, min. application chip revision: 0
I (107) esp_image: segment 0: paddr=00010020 vaddr=3f400020 size=0bb80h ( 48000) map
I (132) esp_image: segment 1: paddr=0001bba8 vaddr=3ffb0000 size=028e8h ( 10472) load
I (137) esp_image: segment 2: paddr=0001e498 vaddr=40080000 size=00404h (  1028) load
I (139) esp_image: segment 3: paddr=0001e8a4 vaddr=40080404 size=01774h (  6004) load
I (149) esp_image: segment 4: paddr=00020020 vaddr=400d0020 size=1a400h (107520) map
I (193) esp_image: segment 5: paddr=0003a428 vaddr=40081b78 size=0964ch ( 38476) load
I (215) boot: Loaded app from partition at offset 0x10000
I (215) boot: Disabling RNG early entropy source...
 ________________________________________________________________
0|                                                               |
1|                                                               |
2|                                                               |
3|                                                               |
4|                                                               |
5|   |||                                                         |
6||  ||||                                                 ||     |
7|||||||||     |   |                          ||| |       |||    |
8|||||| ||||||||||||| |               |   ||||||||||||| |||||    |
9                    | ||||||||||||||| |||             |     |||||
 0123456789012345678901234567890123456789012345678901234567890123
 ________________________________________________________________
0|                                                               |
1|                                                               |
2|                                                               |
3|                                                               |
4|                                                               |
5|   |||                                                         |
6||||||||                                                 |      |
7||||| |||  ||| | ||                         |||   |||  |||||    |
8|||   | ||||||||||||| |             |||  ||||||||||||| |||||||| |
9                     | |||||||||||||   ||             |        ||
 0123456789012345678901234567890123456789012345678901234567890123
 ________________________________________________________________
0|                                                               |
1|                                                               |
2|                                                               |
3|                                                               |
4|                                                               |
5|   | ||                                                        |
6||| |||||                                     |         |       |
7|||| ||||   |||  ||                  |       ||        |||||    |
8 ||     | |||||| |||                |||| || |||||||||  |||||||| |
9         |      |   ||||||||||||||||    |  |         ||        ||
 0123456789012345678901234567890123456789012345678901234567890123
```


## Troubleshooting

* Program upload failure

    * Hardware connection is not correct: run `idf.py -p PORT monitor`, and reboot your board to see if there are any output logs.
    * The baud rate for downloading is too high: lower your baud rate in the `menuconfig` menu, and try again.

For any technical queries, please open an [issue](https://github.com/espressif/esp-idf/issues) on GitHub. We will get back to you soon.
