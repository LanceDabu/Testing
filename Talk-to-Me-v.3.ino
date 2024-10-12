#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);  // 0x27 Address of LCD on i2c | Tinkercad 0x20 -> PCF8574

const int FlexSensorPin1 = A0;
const int FlexSensorPin2 = A1;
const int FlexSensorPin3 = A2;
const int FlexSensorPin4 = A3;
const int FlexSensorPin5 = A6;
const int ButtonPin = 2; // Pin connected to the button

int mode = 0; // 0 for phrases, 1 for numbers, 2 for letters
bool lastButtonState = HIGH; // Initialize with HIGH for pull-up resistor
bool currentButtonState = HIGH;

void setup() {
    pinMode(FlexSensorPin1, INPUT);
    pinMode(FlexSensorPin2, INPUT);
    pinMode(FlexSensorPin3, INPUT);
    pinMode(FlexSensorPin4, INPUT);
    pinMode(FlexSensorPin5, INPUT);
    pinMode(ButtonPin, INPUT_PULLUP); // Button with internal pull-up resistor

    Serial.begin(9600);
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0, 0);
    lcd.print("Talk-To-Me");
}

void loop() {
    currentButtonState = digitalRead(ButtonPin);
    
    // Switch mode if button is pressed
    if (lastButtonState == HIGH && currentButtonState == LOW) {
        switchMode();
        delay(200); // Debounce delay
    }
    lastButtonState = currentButtonState;

    int flexValues[5];
    readFlexSensors(flexValues);

    lcd.clear();

    switch (mode) {
        case 0:
            handlePhrasesMode(flexValues);
            break;
        case 1:
            handleNumbersMode(flexValues);
            break;
        case 2:
            handleLettersMode(flexValues);
            break;
    }

    delay(500); // Adjust delay as needed
}

// Function to read flex sensor values
void readFlexSensors(int *flexValues) {
    flexValues[0] = analogRead(FlexSensorPin1);
    flexValues[1] = analogRead(FlexSensorPin2);
    flexValues[2] = analogRead(FlexSensorPin3);
    flexValues[3] = analogRead(FlexSensorPin4);
    flexValues[4] = analogRead(FlexSensorPin5);

    Serial.print("Flex Sensor 1: ");
    Serial.print(flexValues[0]);
    Serial.print(" | Flex Sensor 2: ");
    Serial.print(flexValues[1]);
    Serial.print(" | Flex Sensor 3: ");
    Serial.print(flexValues[2]);
    Serial.print(" | Flex Sensor 4: ");
    Serial.print(flexValues[3]);
    Serial.print(" | Flex Sensor 5: ");
    Serial.println(flexValues[4]);
}

// Function to handle mode switching
void switchMode() {
    mode++;
    if (mode > 2) {
        mode = 0; // Reset to phrases mode after letters mode
    }
}

// Function to handle phrases mode
void handlePhrasesMode(int *flexValues) {
    lcd.setCursor(0, 0);
    
    if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_2_3_4_5 ");
        Serial.println("Order 1_2_3_4_5");

    } else if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_2_3_4   ");
        Serial.println("Order 1_2_3_4");

    } else if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Pakyu Par   ");
        Serial.println("Fuck You");

    } else if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_2_3     ");
        Serial.println("Order 1_2_3");

    } else if ((flexValues[0] < 150) && (flexValues[1] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_2       ");
        Serial.println("Order 1_2");

    } else if ((flexValues[0] < 150) && (flexValues[2] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_3       ");
        Serial.println("Order 1_3");

    } else if ((flexValues[0] < 150) && (flexValues[3] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1_4       ");
        Serial.println("Order 1_4");

    } else if ((flexValues[2] < 200) && (flexValues[3] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("Order 3_4       ");
        Serial.println("Order 3_4");

    } else if (flexValues[0] < 150) {
        lcd.setCursor(0, 1);
        lcd.print("Order 1         ");
        Serial.println("Order 1");

    } else if (flexValues[1] < 200) {
        lcd.setCursor(0, 1);
        lcd.print("Order 2         ");
        
        Serial.println("Order 2");
    } else if (flexValues[2] < 200) {
        lcd.setCursor(0, 1);
        lcd.print("Order 3         ");
        Serial.println("Order 3");

    } else if (flexValues[3] < 200) {
        lcd.setCursor(0, 1);
        lcd.print("Order 4         ");
        Serial.println("Order 4");

    } else if (flexValues[4] < 200 & flexValues[3] < 170) {
        lcd.setCursor(0, 1);
        lcd.print("Order 5         ");
        Serial.println("Order 5");
        
    } else {
        lcd.setCursor(0, 1);
        lcd.print("Phrases mode    ");
        Serial.println("Phrases mode ");
    }
}

// Function to handle numbers mode
void handleNumbersMode(int *flexValues) {
  lcd.setCursor(0, 0);
  
    if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("5 ");
        Serial.println("5");

   } else if ((flexValues[1] < 150) && (flexValues[2] < 160) && (flexValues[3] < 140) && (flexValues[4] < 150)) {
        lcd.setCursor(0, 1);
        lcd.print("10");
        Serial.println("10");

    } else if ((flexValues[0] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("1");
        Serial.println("1");

    } else if ((flexValues[0] < 150) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("2");
        Serial.println("2");

    } else if ((flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("3");
        Serial.println("3");

    } else if ((flexValues[0] < 120)) {
        lcd.print("4");
        Serial.println("4");

    } else if ((flexValues[0] < 200) && (flexValues[4] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("6 ");
        Serial.println("6");

    } else if ((flexValues[0] < 150) && (flexValues[3] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("7");
        Serial.println("7");

    } else if ((flexValues[0] < 150) && (flexValues[2] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("8");
        Serial.println("8");

    } else if ((flexValues[0] < 150) && (flexValues[1] < 200)) {
        lcd.setCursor(0, 1);
        lcd.print("9");
        Serial.println("9");

    } else {
        lcd.print("Numbers mode");
        Serial.println("Numbers mode");
    }
}

// Function to handle letters mode using ASL
void handleLettersMode(int *flexValues) {
    lcd.setCursor(0, 0);
    
    if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 150) && (flexValues[4] < 150)) {
        lcd.print("A");
        Serial.println("A"); // A: Fist with thumb extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("B");
        Serial.println("B"); // B: Palm open, fingers extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200)) {
        lcd.print("C");
        Serial.println("C"); // C: Fingers bent in a C shape
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 200)) {
        lcd.print("D");
        Serial.println("D"); // D: Fingers spread with index finger extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 150)) {
        lcd.print("E");
        Serial.println("E"); // E: Fingers curved with thumb extended
    } else if ((flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("F");
        Serial.println("F"); // F: Thumb and index finger touching
    } else if ((flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 150)) {
        lcd.print("G");
        Serial.println("G"); // G: Thumb and index finger extended
    } else if ((flexValues[2] < 150) && (flexValues[3] < 150) && (flexValues[4] < 200)) {
        lcd.print("H");
        Serial.println("H"); // H: Index and middle fingers extended
    } else if ((flexValues[2] < 150) && (flexValues[3] < 150)) {
        lcd.print("I");
        Serial.println("I"); // I: Pinky extended
    } else if ((flexValues[3] < 150) && (flexValues[4] < 200)) {
        lcd.print("J");
        Serial.println("J"); // J: Index finger curved in a J shape
    } else if ((flexValues[0] < 150) && (flexValues[2] < 150) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("K");
        Serial.println("K"); // K: Thumb and index finger extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[4] < 200)) {
        lcd.print("L");
        Serial.println("L"); // L: Thumb and index finger extended
    } else if ((flexValues[0] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200)) {
        lcd.print("M");
        Serial.println("M"); // M: Thumb and three fingers bent
    } else if ((flexValues[0] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("N");
        Serial.println("N"); // N: Thumb and two fingers bent
    } else if ((flexValues[0] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200) && (flexValues[1] < 200)) {
        lcd.print("O");
        Serial.println("O"); // O: Fingers curved into a ball
    } else if ((flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("P");
        Serial.println("P"); // P: Thumb and index finger extended with other fingers folded
    } else if ((flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 150)) {
        lcd.print("Q");
        Serial.println("Q"); // Q: Index and pinky fingers extended, others folded
    } else if ((flexValues[2] < 150) && (flexValues[3] < 150)) {
        lcd.print("R");
        Serial.println("R"); // R: Index and middle fingers crossed
    } else if ((flexValues[3] < 150)) {
        lcd.print("S");
        Serial.println("S"); // S: Fist with thumb around fingers
    } else if ((flexValues[4] < 150)) {
        lcd.print("T");
        Serial.println("T"); // T: Thumb and fingers extended in a T shape
    } else if ((flexValues[0] < 200) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("U");
        Serial.println("U"); // U: Index and middle fingers extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 200) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("V");
        Serial.println("V"); // V: Index and middle fingers extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 200)) {
        lcd.print("W");
        Serial.println("W"); // W: Thumb, index, and middle fingers extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200)) {
        lcd.print("X");
        Serial.println("X"); // X: Index finger extended and curved
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 200) && (flexValues[3] < 200) && (flexValues[4] < 150)) {
        lcd.print("Y");
        Serial.println("Y"); // Y: Thumb and pinky extended
    } else if ((flexValues[0] < 150) && (flexValues[1] < 150) && (flexValues[2] < 150) && (flexValues[3] < 200) && (flexValues[4] < 200)) {
        lcd.print("Z");
        Serial.println("Z"); // Z: Index finger tracing a Z
    } else {
        lcd.print("Letters mode");
        Serial.println("Letters mode");
    }
}



   

