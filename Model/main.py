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

def detect_command(text):
    text = text.lower()

    # xác định hành động
    if any(word in text for word in ["bật", "mở", "sáng"]):
        action = "ON"
    elif any(word in text for word in ["tắt", "đóng"]):
        action = "OFF"
    else:
        return None

    # xác định phòng
    if any(word in text for word in ["cả nhà", "toàn bộ", "tất cả", "hết", "cả"]):
        room = "ALL"
    elif "khách" in text:
        room = "LIVINGROOM"
    elif "ăn" in text:
        room = "DININGROOM"
    elif "ngủ" in text:
        room = "BEDROOM"
    elif "sân" in text:
        room = "YARD"
    else:
        return None

    return f"{room}_{action}"

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

            cmd = detect_command(text)
            if cmd:
                ser.write((cmd + "\n").encode())
                print(f"✅ Gửi: {cmd}\n")
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
