#include "serialread.h"
#include <cstring>
#include <iostream>
#include <math.h>
#include <stdio.h>

SerialRead::SerialRead() {
  flightDataFile.open("data/flightData.txt", std::ios::out);
  serialDataFile.open("/dev/cu.usbmodem11101", std::ios::in | std::ios::binary);
}

SerialRead::~SerialRead() {
  serialDataFile.close();
  flightDataFile.close();
}

float SerialRead::getValue(std::string name) { return serialValues[name]; }

template <typename T> T converter(char *packet) {
  T temp;
  memcpy(&temp, packet, sizeof(temp));
  return temp;
}

void printByte(uint8_t byte) {
  for (int i = 7; i >= 0; i--) {
    if (byte & (0b1 << i)) {
      std::cout << "1";
    } else {
      std::cout << "0";
    }
  }
  std::cout << std::endl;
}

void SerialRead::readPacket() {
  char packet[86];

  if (serialDataFile.is_open()) {
    serialDataFile.read(packet, sizeof(packet)); // read 86 bytes to our buffer

    // If we did not read 86 bytes, then discard the bytes and try again next
    // time this function is called
    std::streamsize bytes = serialDataFile.gcount();
    if (bytes != sizeof(packet)) {
      return;
    }

    /*Process MetaData*/
    int i = 0;
    while (i < 8) {
      switch (i) {
      case 0:
        if (packet[0] & 0x01) {
          altimeterState = VALID;
        }
        break;
      case 1:
        if (packet[0] & 0x01) {
          gpsState = VALID;
        }
        break;
      case 2:
        break;
      case 3:
        if (packet[0] & 0x01) {
          temperatureState = VALID;
        } else {
          if ((packet[0] >> 1) & 0x01) {
            temperatureState = INVALID;
          } else {
            temperatureState = OFF;
          }
        }
        i += 1;
        packet[0] >>= 1;
        break;
      case 4:
        break;
      case 5:
        if (packet[0] & 0x01) {
          accelerometerState = VALID;
        } else {
          if ((packet[0] >> 1) & 0x01) {
            accelerometerState = INVALID;
          } else {
            accelerometerState = OFF;
          }
        }
        i += 1;
        packet[0] >>= 1;
        break;
      case 6:
        break;
      case 7:
        // Process IMU State
        if (packet[0] & 0x01) {
          imuState = VALID;
        }
        break;
      }
      packet[0] >>= 1;
      i += 1;
    }

    i = 8;
    while (i < 16) {
      switch (i) {
      case 8:
        if (packet[1] & 0x01) {
          imuState = INVALID;
        }
        break;
      case 9:
        if (packet[1] & 0x01) {
          gpsState = VALID;
        } else {
          if ((packet[1] >> 1) & 0x01) {
            gpsState = INVALID;
          } else {
            gpsState = OFF;
          }
        }
        i += 1;
        packet[1] >>= 1;
        break;
      case 10:
        break;
      case 11:
        if (packet[1] & 0x01) {
          altimeterState = VALID;
        } else {
          if ((packet[1] >> 1) & 0x01) {
            altimeterState = INVALID;
          } else {
            altimeterState = OFF;
          }
        }
        i += 1;
        packet[1] >>= 1;
        break;
      case 12:
        break;
      case 13: {
        // Process the Flight Mode
        u_int8_t sum = 0;
        for (int j = 0; j < 3; j++) {
          if (packet[1] & 0x01) {
            sum += pow(2, j);
          }
          packet[1] >>= 1;
        }
        switch (sum) {
        case 0:
          flightMode = STARTUP;
          break;
        case 1:
          flightMode = STANDBY;
          break;
        case 2:
          flightMode = ASCENT;
          break;
        case 3:
          flightMode = DROGUEDEPLOYED;
          break;
        case 4:
          flightMode = MAINDEPLOYED;
          break;
        case 5:
          flightMode = FAULT;
          break;
        default:
          break;
        }
      }
        i += 3;
        break;
      case 14:
        break;
      case 15:
        break;
      }
      packet[1] >>= 1;
      i += 1;
    }

    uint32_t timestamp = converter<uint32_t>((char *)&packet[2]);
    printf("%s%i%s", "Time Stamp: ", timestamp, "\n");

    printf("Events Byte 1: ");
    printByte(packet[6]);

    printf("Events Byte 2: ");
    printByte(packet[7]);

    printf("Events Byte 3: ");
    printByte(packet[8]);

    float alt = converter<float>((char *)&packet[9]);

    float lat = converter<float>((char *)&packet[13]);

    float longi = converter<float>((char *)&packet[17]);

    uint8_t satInView = converter<uint8_t>((char *)&packet[21]);

    float accelX = converter<float>((char *)&packet[22]);

    float accelY = converter<float>((char *)&packet[26]);

    float accelZ = converter<float>((char *)&packet[30]);

    float gyroX = converter<float>((char *)&packet[34]);

    float gyroY = converter<float>((char *)&packet[38]);

    float gyroZ = converter<float>((char *)&packet[42]);

    float accelXIMU = converter<float>((char *)&packet[46]);

    float accelYIMU = converter<float>((char *)&packet[50]);

    float accelZIMU = converter<float>((char *)&packet[54]);

    float oriX = converter<float>((char *)&packet[58]);

    float oriY = converter<float>((char *)&packet[62]);

    float oriZ = converter<float>((char *)&packet[66]);

    float gravityX = converter<float>((char *)&packet[70]);

    float gravityY = converter<float>((char *)&packet[74]);

    float gravityZ = converter<float>((char *)&packet[78]);

    float temp = converter<float>((char *)&packet[82]);

    serialValues["timestamp"] = float(timestamp);

    serialValues["Altitude"] = alt;

    serialValues["Latitude"] = float(lat);
    serialValues["Longitude"] = float(longi);

    serialValues["Accel X"] = accelX;
    serialValues["Accel Y"] = accelY;
    serialValues["Accel Z"] = accelZ;

    serialValues["Gyro X"] = gyroX;
    serialValues["Gyro Y"] = gyroY;
    serialValues["Gyro Z"] = gyroZ;

    serialValues["Accel X IMU"] = accelXIMU;
    serialValues["Accel Y IMU"] = accelYIMU;
    serialValues["Accel Z IMU"] = accelZIMU;

    serialValues["Orientation X"] = oriX;
    serialValues["Orientation Y"] = oriY;
    serialValues["Orientation Z"] = oriZ;

    serialValues["Gravity X"] = gravityX;
    serialValues["Gravity Y"] = gravityY;
    serialValues["Gravity Z"] = gravityZ;

    /*TODO: Update the elevation Queue with the new value*/

    if (flightDataFile.is_open()) { /*Write the packet to the text file */
      std::cout << "flightData.txt is open, beginning to write data ..."
                << std::endl;

      for (auto it = serialValues.begin(); it != serialValues.end(); it++) {
        flightDataFile << it->first.c_str() << ": " << it->second << ",";
      }
      flightDataFile << "\n";
    } else {
      std::cout << "flightData.txt is not open" << std::endl;
      ;
    }
  }
}
