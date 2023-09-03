# uuid_init_esp32
Initializes and saves 2 UUID values into ESP32's EEPROM

# Dependency
## arduino-cli
- Upon installation, please run:
```
arduino-cli config init
arduino-cli core update-index
```
  - Then, modify arduino-cli's configuration file (typically at ~/.arduino15/arduino-cli.yaml) under the **board_manager** heading as follows:
```
board_manager:
  additional_urls:
    - https://espressif.github.io/arduino-esp32/package_esp32_index.json
```
  - After that, run:
```
arduino-cli core update-index
arduino-cli core search esp32
```
  - If you see ```esp32:esp32```, then you're good to go!

# Set Up
```
git clone https://github.com/VirtuousCrane/uuid_init_esp32.git
cd uuid_init_esp32
chmod +x flash.sh
```

# Running the Program
```
./flash.sh --port /dev/<PORT> --file-location <LOCATION OF REPOSITORY>
```

- Example:
```
./flash.sh --port /dev/ttyUSB0 --file-location ~/uuid_init_esp32
```

# How the program stores UUIDs
```
| UUID LEN (1 byte) | UUID (36 bytes) | UUID LEN (1 byte) | UUID (36 bytes) |
```

# Acknowledgement
The code to read and write strings to EEPROM was modified from [here](https://roboticsbackend.com/arduino-write-string-in-eeprom/)
