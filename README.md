**Bootloader for Open source video transmitter firmware**

OpenVTx firmware can be found from https://github.com/JyeSmith/OpenVTx

# Setup

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#setup)

# Flashing the VTx

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#flashing-the-vtx) how to
connect ST-Link.

Select `EWRF_E7082VM_bootloader` env and hit upload to flash a bootloader.

Note: This automatically removes protections so no need to use ST-Link Utility anymore.

Next you need to flash OpenVTx firmware:
* Connect VTX to FC
* Select `VTX (TBS SmartAudio)`
* Use `EWRF_E7082VM_serialpassthrough` target to upload actual OpenVTx firmware.

Happy flying :)
