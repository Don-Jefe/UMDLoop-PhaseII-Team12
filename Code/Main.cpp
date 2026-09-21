// Libraries
// Number of joints on the roobot
#define NUM_JOINTS 6

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
    for (int joint = 0; joint < NUM_JOINTS; joint++) {
        // Select the multiplexer channel for the current joint
        selectMultiplexerChannel(joint);
        
        // Read the angle from the encoder
        jointAngles[joint] = readEncoderAngle();
    }

    // Read the gripper position
    float rawGripperPosition = readGripperPosition();
    float gripperPosition = mapGripperPosition(rawGripperPosition);

    // Telemetry output
    for (int joint = 0; joint < NUM_JOINTS; joint++) {
        Serial.print("Joint ");
        Serial.print(joint);
        Serial.print(": ");
        Serial.print(jointAngles[joint]);
        Serial.println(" degrees");
    }
    serial.print("Gripper Position: ");
    Serial.println(gripperPosition);

    sendCAN(jointAngles, gripperPosition);

    delay(100); // Delay


    
}