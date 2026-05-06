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

    Serial.print("Received: [");
    Serial.print(command);
    Serial.print("] len=");
    Serial.print(command.length());
    Serial.print(" bytes:");
    for (int i = 0; i < command.length(); i++) {
      Serial.print(" 0x");
      Serial.print((int)command[i], HEX);
    }
    Serial.println();

    handleCommand(command);
  }
}

void handleCommand(String cmd) {
  // ===== ALL =====
  if (cmd == "ALL_ON") {
    Serial.println("-> ALL_ON matched");
    setAll(HIGH);
  }
  else if (cmd == "ALL_OFF") {
    Serial.println("-> ALL_OFF matched");
    setAll(LOW);
  }

  // ===== LIVING ROOM =====
  else if (cmd == "LIVINGROOM_ON") {
    Serial.println("-> LIVINGROOM_ON matched");
    digitalWrite(livingRoom, HIGH);
  }
  else if (cmd == "LIVINGROOM_OFF") {
    Serial.println("-> LIVINGROOM_OFF matched");
    digitalWrite(livingRoom, LOW);
  }

  // ===== DINING ROOM =====
  else if (cmd == "DININGROOM_ON") {
    Serial.println("-> DININGROOM_ON matched");
    digitalWrite(diningRoom, HIGH);
  }
  else if (cmd == "DININGROOM_OFF") {
    Serial.println("-> DININGROOM_OFF matched");
    digitalWrite(diningRoom, LOW);
  }

  // ===== BEDROOM =====
  else if (cmd == "BEDROOM_ON") {
    Serial.println("-> BEDROOM_ON matched");
    digitalWrite(bedRoom, HIGH);
  }
  else if (cmd == "BEDROOM_OFF") {
    Serial.println("-> BEDROOM_OFF matched");
    digitalWrite(bedRoom, LOW);
  }

  // ===== YARD =====
  else if (cmd == "YARD_ON") {
    Serial.println("-> YARD_ON matched");
    digitalWrite(yard, HIGH);
  }
  else if (cmd == "YARD_OFF") {
    Serial.println("-> YARD_OFF matched");
    digitalWrite(yard, LOW);
  }

  else {
    Serial.println("-> NO MATCH!");
  }
}

// Hàm bật/tắt toàn bộ
void setAll(int state) {
  digitalWrite(livingRoom, state);
  digitalWrite(diningRoom, state);
  digitalWrite(bedRoom, state);
  digitalWrite(yard, state);
}
