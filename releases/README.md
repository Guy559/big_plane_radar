# Release Artifacts

This directory is populated by local builds. Use `bash build_arduino_cli.sh` for
normal builds (add `BOARD=7B` for the LCD-7B) or `UPLOAD=1 bash
build_arduino_cli.sh` for direct flashing.

The expected release files are:

- `big_plane_radar.ino.merged.bin` &mdash; ESP32-S3-Touch-LCD-7
- `big_plane_radar-7b.ino.merged.bin` &mdash; ESP32-S3-Touch-LCD-7B

Use the merged binary matching your board for browser-based flashing tools at
offset `0x0`.

Manual flashing example:

```sh
# LCD-7
esptool.py --chip esp32s3 --port /dev/cu.usbmodemXXXX --baud 921600 \
  write_flash 0x0 releases/big_plane_radar.ino.merged.bin

# LCD-7B
esptool.py --chip esp32s3 --port /dev/cu.usbmodemXXXX --baud 921600 \
  write_flash 0x0 releases/big_plane_radar-7b.ino.merged.bin
```
