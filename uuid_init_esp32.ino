#include <EEPROM.h>
#include "uuid.h"

// UUID len = 36, len = 1, therefore 37

int write_str_to_eeprom(int offset, const String &s);
int read_str_from_eeprom(int offset, String *s);

String device_uuid_1;
String device_uuid_2;

void setup() {
  // Initializes Serial
  Serial.begin(115200);
  while (!Serial) {}

  // Initializes EEPROM
  EEPROM.begin(EEPROM_SIZE);

  // Checks if UUID has been set
  int uuid1_len = EEPROM.read(0);
  if (uuid1_len < 1) {
    // Initializes the UUID into EEPROM
    Serial.println("EEPROM not set. Initializing UUID from Preset values...");
    int uuid_1_offset = write_str_to_eeprom(0, uuid_1);
    int _uuid_2_offset = write_str_to_eeprom(uuid_1_offset, uuid_2);

    if (EEPROM.commit()) {
      Serial.println("Successfully written to EEPROM");
    } else {
      Serial.println("Failed to write to EEPROM");
      while (true) {
        Serial.print(".");
      }
    }
  }

  // Reads UUID values from EEPROM
  int device_uuid_1_offset = read_str_from_eeprom(0, &device_uuid_1);
  read_str_from_eeprom(device_uuid_1_offset, &device_uuid_2);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("UUID 1 = ");
  Serial.print(device_uuid_1);
  Serial.println();

  Serial.print("UUID 2 = ");
  Serial.print(device_uuid_2);
  Serial.println();
  
  delay(5000);
}

int write_str_to_eeprom(int offset, const String &s) {
  int current_offset = offset;

  // Getting and Writing Length of String to EEPROM
  byte len = s.length();
  EEPROM.write(current_offset, len);
  current_offset++;

  // Writing String to EEPROM
  for (int i = 0; i < len; i++) {
    EEPROM.write(current_offset, s[i]);
    current_offset++;
  }

  return current_offset;
}

int read_str_from_eeprom(int offset, String *s) {
  int current_offset = offset;
  int str_len = EEPROM.read(offset);
  char str[str_len + 1];
  current_offset++;

  for (int i = 0; i < str_len; i++) {
    str[i] = EEPROM.read(current_offset);
    current_offset++;
  }
  str[str_len] = '\0';

  *s = String(str);
  return current_offset;
}
