# Big Plane Radar

Firmware for the Waveshare ESP32-S3-Touch-LCD-7 display. It shows a live ADS-B
radar centered on a configurable location, with aircraft symbols, labels,
altitude, vertical speed, range rings, and a compact aircraft list.

The firmware does not use LVGL. It draws directly into an RGB565 framebuffer and
uses Waveshare's official `ESP32_Display_Panel` stack for the 800x480 RGB LCD and
GT911 touch panel.

![Big Plane Radar running on Waveshare ESP32-S3-Touch-LCD-7](docs/plane-radar.png)

## 3D-Printed Stand

A matching desktop stand for this display and firmware is available on
MakerWorld:

https://makerworld.com/ru/models/3034679-stand-for-esp32-s3-touch-lcd-7-for-plane-radar

## Hardware

- Waveshare ESP32-S3-Touch-LCD-7 (800x480) or ESP32-S3-Touch-LCD-7B (1024x600) RGB LCD
- USB data cable connected to the board's `UART1` USB port
- Board switch set to `UART1`

The two boards share the same RGB/touch pinout but differ in panel resolution/timing and use
different (incompatible) IO expander chips; see `BOARD` under Build.

On macOS, install the USB serial driver if the board does not appear as
`/dev/cu.usbmodem*` or `/dev/cu.wchusbserial*`. On Linux, the device usually
appears as `/dev/ttyACM*` or `/dev/ttyUSB*`; the user may need access to the
`dialout` group.

## Features

- first-boot setup portal: `PlaneRadar-Setup`;
- saved Wi-Fi, radar center, units, runway overlay, and range settings in NVS;
- ADS-B data from `https://opendata.adsb.fi/api/v3/`;
- local dead-reckoning between ADS-B updates, redrawn at about `4 FPS`;
- optional route city line in the aircraft list via cached callsign lookups from
  `https://api.adsbdb.com/`;
- background Wi-Fi reconnect after router/power outages;
- touch controls: short tap cycles range, long press starts the setup portal;
- boot setup window: hold the screen during startup to force the setup portal;
- screenshot endpoint: `/screenshot` and `/screenshot.bmp`;
- conservative RGB LCD settings per panel: `14 MHz` PCLK on both the LCD-7 and LCD-7B.
  Waveshare's own reference firmware runs the 7B at `30 MHz`, but that assumes 120MHz
  PSRAM/flash; this Arduino core only supports 80MHz on the S3, and 30MHz (and even 20MHz)
  caused visible screen drift/tearing on real hardware at that speed, so the 7B matches the
  LCD-7's proven-stable `14 MHz`. The 7B also uses a larger bounce buffer
  (`panel_width * 20` vs `panel_width * 10`) for extra DMA cushion.

## Symbol Legend

Aircraft symbols use ADS-B `category` when it is available.

![Aircraft symbol legend](docs/aircraft-symbol-legend.svg)

## Repository Layout

```text
.
├── big_plane_radar.ino
├── build_arduino_cli.sh
├── esp_panel_board_custom_conf.h
├── lib/
│   └── ArduinoJson/
├── releases/
├── scripts/
│   └── build_iata_airports.py
├── src/
│   ├── airports.h
│   ├── airports_iata.h
│   ├── main.cpp
│   ├── panel_display.cpp
│   └── panel_display.h
└── vendor/
    └── waveshare-libraries/
```

`vendor/waveshare-libraries` contains only the Arduino libraries required by this
firmware: `ESP32_Display_Panel`, `ESP32_IO_Expander`, and `esp-lib-utils`.

## Install Tools

Install:

- `arduino-cli`
- Espressif Arduino core for ESP32
- `esptool` for manual flashing or diagnostics

Install the ESP32 core:

```sh
arduino-cli core update-index
arduino-cli core install esp32:esp32
```

## Build

```sh
bash build_arduino_cli.sh
```

This builds for the original ESP32-S3-Touch-LCD-7 (800x480) by default. To build for the
ESP32-S3-Touch-LCD-7B (1024x600) instead:

```sh
BOARD=7B bash build_arduino_cli.sh
```

`BOARD` selects the resolution, RGB timing, and IO expander driver in
`esp_panel_board_custom_conf.h`. Each board builds to its own path under `build/` so switching
`BOARD` never reuses stale objects from the other board.

By default, no Wi-Fi credentials are compiled into the firmware. The default
radar center is London:

```text
Latitude:  51.507400
Longitude: -0.127800
```

You can override first-boot defaults at build time:

```sh
DEFAULT_LAT=51.507400 \
DEFAULT_LON=-0.127800 \
bash build_arduino_cli.sh
```

Optional Wi-Fi defaults:

```sh
DEFAULT_WIFI_SSID="YourNetwork" \
DEFAULT_WIFI_PASSWORD="YourPassword" \
bash build_arduino_cli.sh
```

## Upload

Put the board switch into `UART1`, plug USB into the `UART1` port, then run:

```sh
UPLOAD=1 CLEAN=1 PORT=/dev/cu.usbmodem5AE71132621 bash build_arduino_cli.sh
```

Adjust `PORT` for your machine:

```sh
# macOS examples
PORT=/dev/cu.usbmodemXXXX
PORT=/dev/cu.wchusbserialXXXX

# Linux examples
PORT=/dev/ttyACM0
PORT=/dev/ttyUSB0
```

## Browser Flashing

You can also flash the board directly from a browser with Web Serial support.
Use Chrome, Edge, or another Chromium-based desktop browser. iOS browsers do not
support this workflow.

### Option A: Adafruit WebSerial ESPTool

This is the quickest no-hosting option because it lets you choose a local binary
file manually:

1. Open [Adafruit WebSerial ESPTool](https://adafruit.github.io/Adafruit_WebSerial_ESPTool/).
2. Set the board switch to `UART1` and plug USB into the `UART1` port.
3. Click `Connect` and select the ESP32-S3 serial port.
4. Use one file row:
   - offset: `0x0`
   - file: `releases/big_plane_radar.ino.merged.bin` (LCD-7) or
     `releases/big_plane_radar-7b.ino.merged.bin` (LCD-7B)
5. Click `Erase`, then `Program`.

Use the merged binary matching your board for browser flashing.

### Option B: ESP Web Tools Page

This repository includes a ready static installer in `web-installer/`. It uses
[ESP Web Tools](https://esphome.github.io/esp-web-tools/), which installs
firmware from a manifest and release binary.

To use it:

1. Publish this repository with GitHub Pages or another HTTPS static host.
2. Open:

```text
https://<your-github-user>.github.io/big_plane_radar/web-installer/
```

3. Select your board (LCD-7 or LCD-7B), then press the install button and
   select the ESP32-S3 serial port.

ESP Web Tools requires HTTPS and the firmware file must be fetchable by the
browser. The board selector switches between two manifests:

```text
web-installer/manifest-7.json  -> ../releases/big_plane_radar.ino.merged.bin
web-installer/manifest-7b.json -> ../releases/big_plane_radar-7b.ino.merged.bin
```

## First Boot

If no configuration is saved, the board starts a Wi-Fi access point:

```text
PlaneRadar-Setup
```

Connect to it and open:

```text
http://192.168.4.1
```

After the board joins your Wi-Fi, the setup page is also available at:

```text
http://plane-radar.local
```

Set Wi-Fi, radar center coordinates, units, and runway overlay there. The board
reboots after saving.

## Screenshot

When the board is connected to Wi-Fi, capture the current screen:

```sh
curl -o docs/screenshot.bmp http://plane-radar.local/screenshot.bmp
```

Direct URLs:

```text
http://plane-radar.local/screenshot
http://plane-radar.local/screenshot.bmp
```

If mDNS is unavailable, use the IP shown in the setup page:

```sh
curl -o docs/screenshot.bmp http://<device-ip>/screenshot.bmp
```

## Release Binaries

Prebuilt files are placed in `releases/`:

- `big_plane_radar.ino.merged.bin`

Manual flashing can use the same merged binary:

```sh
esptool.py --chip esp32s3 --port /dev/cu.usbmodemXXXX --baud 921600 \
  write_flash 0x0 releases/big_plane_radar.ino.merged.bin
```

The easiest development path is still `UPLOAD=1 ... bash build_arduino_cli.sh`.
