// Libraries
#if __has_include(<Arduino.h>)
#include <Arduino.h>
#else
// Fallback declarations allow editor parsing when the Arduino SDK is not
// configured; an Arduino build will use the real header above.
class SerialPort {
public:
    void begin(unsigned long);
    void print(const char*);
};
extern SerialPort Serial;
#endif

#if __has_include(<Wire.h>)
#include <Wire.h>
#else
class I2CBus {
public:
    void begin();
};
extern I2CBus Wire;
#endif

void initMultiplexer();
void initEncoders();
void initGripper();
void initCAN();

// Number of joints on the robot
constexpr int NUM_JOINTS = 6;

// Joint angle storage
float jointAngles[NUM_JOINTS];

void setup() {
    Serial.begin(115200);
    
    // Initialize the I2C 
    Wire.begin();
    // Initialize with the Multiplexer (TCA9548A)
    initMultiplexer();
    
    // Initialize magnetic encoders (AS5600)
    initEncoders();

    // Initialize potentiometer
    initGripper();

    // Initialize CAN
    initCAN();

    Serial.print("Controller Initialized");
}

void loop() {
    
}