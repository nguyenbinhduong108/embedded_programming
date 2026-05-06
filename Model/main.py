import re
import speech_recognition as sr
import serial
import os

ser = serial.Serial('/dev/tty.usbserial-0001', 115200)

r = sr.Recognizer()
r.pause_threshold = 0.5
r.phrase_threshold = 0.15
r.non_speaking_duration = 0.3
r.energy_threshold = 400
r.dynamic_energy_threshold = False

def clear_screen():
    os.system('cls' if os.name == 'nt' else 'clear')

def detect_action(text):
    if any(word in text for word in ["bật", "mở", "sáng"]):
        return "ON"
    elif any(word in text for word in ["tắt", "đóng"]):
        return "OFF"
    return None

def detect_room(text):
    if any(word in text for word in ["cả nhà", "toàn bộ", "tất cả", "hết"]):
        return "ALL"
    elif "khách" in text:
        return "LIVINGROOM"
    elif "ăn" in text:
        return "DININGROOM"
    elif "ngủ" in text:
        return "BEDROOM"
    elif "sân" in text:
        return "YARD"
    return None

def detect_commands(text):
    text = text.lower()

    # tách câu thành các phần bằng dấu phẩy, "và", "với", "rồi"
    parts = re.split(r'[,]+|\s+và\s+|\s+với\s+|\s+rồi\s+', text)
    parts = [p.strip() for p in parts if p.strip()]

    commands = []
    last_action = None

    for part in parts:
        action = detect_action(part)
        room = detect_room(part)

        # nếu phần này không có hành động, dùng hành động trước đó
        if action is None and last_action is not None:
            action = last_action

        if action and room:
            commands.append(f"{room}_{action}")
            last_action = action

    return commands

print("=== Điều khiển bằng giọng nói (Ctrl+C để thoát) ===")

with sr.Microphone() as source:
    r.adjust_for_ambient_noise(source, duration=1)
    r.energy_threshold = max(r.energy_threshold, 400)
    print(f"Đã sẵn sàng! (energy_threshold={r.energy_threshold})\n")

    while True:
        try:
            print("🎤 Đang nghe...")
            audio = r.listen(source)
            print("⏳ Đang nhận diện...")

            text = r.recognize_google(audio, language="vi-VN")
            clear_screen()
            print("=== Điều khiển bằng giọng nói (Ctrl+C để thoát) ===\n")
            print(f"🗣️  Bạn nói: {text}")

            cmds = detect_commands(text)
            if cmds:
                for cmd in cmds:
                    ser.write((cmd + "\n").encode())
                    print(f"✅ Gửi: {cmd}")
                print()
            else:
                print("❌ Không hiểu lệnh\n")

        except sr.UnknownValueError:
            pass
        except sr.RequestError as e:
            print(f"⚠️  Lỗi kết nối Google: {e}\n")
        except KeyboardInterrupt:
            print("\n👋 Tạm biệt!")
            ser.close()
            break
