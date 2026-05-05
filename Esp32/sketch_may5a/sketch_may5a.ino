String command = "";

// Khai báo chân
const int livingRoom = 14;
const int diningRoom = 27;
const int bedRoom = 26;
const int yard = 25;

void setup() {
  Serial.begin(115200);

  pinMode(livingRoom, OUTPUT);
  pinMode(diningRoom, OUTPUT);
  pinMode(bedRoom, OUTPUT);
  pinMode(yard, OUTPUT);

  // Tắt hết ban đầu (tuỳ wiring, có thể đổi HIGH/LOW)
  digitalWrite(livingRoom, LOW);
  digitalWrite(diningRoom, LOW);
  digitalWrite(bedRoom, LOW);
  digitalWrite(yard, LOW);

  Serial.println("ESP32 Ready");
}

void loop() {
  if (Serial.available()) {
    command = Serial.readStringUntil('\n');
    command.trim();

    Serial.print("Received: ");
    Serial.println(command);

    handleCommand(command);
  }
}

void handleCommand(String cmd) {
  // ===== ALL =====
  if (cmd == "ALL_ON") {
    setAll(LOW);
  } 
  else if (cmd == "ALL_OFF") {
    setAll(HIGH);
  }

  // ===== LIVING ROOM =====
  else if (cmd == "LIVINGROOM_ON") {
    digitalWrite(livingRoom, LOW);
  } 
  else if (cmd == "LIVINGROOM_OFF") {
    digitalWrite(livingRoom, HIGH);
  }

  // ===== DINING ROOM =====
  else if (cmd == "DININGROOM_ON") {
    digitalWrite(diningRoom, LOW);
  } 
  else if (cmd == "DININGROOM_OFF") {
    digitalWrite(diningRoom, HIGH);
  }

  // ===== BEDROOM =====
  else if (cmd == "BEDROOM_ON") {
    digitalWrite(bedRoom, LOW);
  } 
  else if (cmd == "BEDROOM_OFF") {
    digitalWrite(bedRoom, HIGH);
  }

  // ===== YARD =====
  else if (cmd == "YARD_ON") {
    digitalWrite(yard, LOW);
  } 
  else if (cmd == "YARD_OFF") {
    digitalWrite(yard, HIGH);
  }

  else {
    Serial.println("Unknown command");
  }
}

// Hàm bật/tắt toàn bộ
void setAll(int state) {
  digitalWrite(livingRoom, state);
  digitalWrite(diningRoom, state);
  digitalWrite(bedRoom, state);
  digitalWrite(yard, state);
}