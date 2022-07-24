**Bootloader for Open source video transmitter firmware**

OpenVTx firmware can be found from https://github.com/JyeSmith/OpenVTx

# Setup

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#setup)

# Flashing the VTx

See [OpenVTx flashing documentation](https://github.com/JyeSmith/OpenVTx#flashing-the-vtx) how to
connect ST-Link.

See [EWRF E7082VM bootloader flash helper](https://github.com/JyeSmith/STL/EWRF_E7082VM_bootloader_flash_helper/) for a 3D print to help with inital bootloader flash.

Select `EWRF_E7082VM_bootloader` env and hit upload to flash a bootloader.

*Note:* This automatically removes protections so no need to use ST-Link Utility anymore.

*Note: Make sure the red led starts blinking after flashing! If not you might need open ST-Link utility and just apply option bytes. This seems to be a problem with some GD32 MCUs*

Next you need to flash OpenVTx firmware:
* Connect VTX to FC
* Select `VTX (TBS SmartAudio)`
* Use `EWRF_E7082VM_serialpassthrough` target to upload actual OpenVTx firmware.

Happy flying :)
