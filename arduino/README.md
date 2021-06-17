# FTM Initiator Example


### Log Output

```
ESP-ROM:esp32s2-rc4-20191025
Build:Oct 25 2019
rst:0x1 (POWERON),boot:0x8 (SPI_FAST_FLASH_BOOT)
SPIWP:0xee
mode:DIO, clock div:1
load:0x3ffe6100,len:0x4b0
load:0x4004c000,len:0xa6c
load:0x40050000,len:0x25c0
entry 0x4004c198
[   762][I][ftm_initiator.ino:206] wifi_cmd_sta_join(): sta connecting to 'WiFi_FTM_Responder'
[  1356][I][ftm_initiator.ino:219] app_get_ftm(): Requesting FTM session with Frm Count - 32, Burst Period - 200mSec (0: No Preference)
W (904) wifi:Starting FTM session in 0.200 Sec
W (2508) wifi:FTM session ends with 25 valid readings out of 31, Avg raw RTT: 27.750 nSec, Avg RSSI: -31
[  2964][I][ftm_initiator.ino:235] app_get_ftm(): Estimated RTT - 14 nSec, Estimated Distance - 2.21 meters
```

