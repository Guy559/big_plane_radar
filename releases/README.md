# Release Artifacts

This directory is populated by local builds. Use `bash build_arduino_cli.sh` for
normal builds or `UPLOAD=1 bash build_arduino_cli.sh` for direct flashing.

The expected release files are:

- `big_plane_radar.ino.bin`
- `big_plane_radar.ino.bootloader.bin`
- `big_plane_radar.ino.partitions.bin`
- `big_plane_radar.ino.merged.bin`
- `boot_app0.bin`
- `flash_args`

Use `big_plane_radar.ino.merged.bin` for browser-based flashing tools at offset
`0x0`.
