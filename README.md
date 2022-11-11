**Bootloader for Open source video transmitter firmware**

OpenVTx firmware can be found from https://github.com/OpenVTx/OpenVTx

# Flashing the VTx bootloader

See [OpenVTx flashing documentation](https://github.com/OpenVTx/OpenVTx#diy-setup-and-flashing-the-ewrf-e7082vm) how to
connect ST-Link.

See [EWRF E7082VM bootloader flash helper](https://github.com/OpenVTx/OpenVTx_bootloader/tree/master/STL/EWRF_E7082VM_bootloader_flash_helper) for a 3D print to help with initial bootloader flash.

Select `Generic_GD32F130_bootloader` env and hit upload to flash a bootloader.

*Note: This automatically removes protections so no need to use ST-Link Utility anymore. Make sure the red led starts blinking after flashing! If not you might need open ST-Link utility and just apply option bytes. This seems to be a problem with some GD32 MCUs*

Next you need to flash OpenVTx firmware:
* Connect VTX to FC.
* Select protocol `VTX (TBS SmartAudio)`.  After the first flash any protocol can be used for future flashing.
* Go to https://openvtx.org/, select a Target, then Flash.

Happy flying :)
