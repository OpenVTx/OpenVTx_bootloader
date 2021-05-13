**Bootloader for Open source video transmitter firmware**

OpenVTx firmware can be found from https://github.com/JyeSmith/OpenVTx

# Setup

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#setup)

# Flashing the VTx

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#flashing-the-vtx) how to
connect ST-Link.

Then hit upload to flash a bootloader.

Next you need to flash OpenVTx firmware:
* Connect VTX to FC
* Select `VTX (TBS SmartAudio)`
* Use `EWRF_E7082VM_BOOTLOADER` target to upload actual OpenVTx firmware.

Happy flying :)
