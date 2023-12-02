import serial
import json
import winsound
import datetime
from serial.tools import list_ports


def list_available_ports():
    ports = list(list_ports.comports())
    if not ports:
        print("没有找到可用的串口。")
    else:
        print("可用串口：")
        for port, desc, _ in ports:
            print(f"{port}: {desc}")


def send_current_time(ser):
    current_time = datetime.datetime.now().strftime("%H:%M:%S")
    ser.write(current_time.encode('utf-8'))


def receive_serial_data(port, baud_rate):
    ser = serial.Serial(port, baud_rate, timeout=1)

    try:
        while True:
            data = ser.readline().decode('utf-8').strip()

            if data:
                try:
                    if data == "success!":
                        current_time = datetime.datetime.now().strftime("%H:%M:%S")
                        print(current_time, "ok!")
                        continue
                    sensor_data = json.loads(data)

                    if not (20 <= sensor_data["temperature"] <= 30 and 0.2 <= sensor_data["humidity"] <= 0.8):
                        print("异常数据！触发报警。")
                        print(f"异常数据内容：{sensor_data}")  # 输出异常数据到控制台
                        winsound.Beep(1000, 2000)
                        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        with open('sensor_log.txt', 'a', encoding='utf-8') as log_file:
                            log_file.write(
                                f"{timestamp}: {sensor_data} (异常数据)\n")
                    else:
                        timestamp = datetime.datetime.now().strftime("%Y-%m-%d %H:%M:%S")
                        print(f"正常数据：{sensor_data}，时间戳：{timestamp}")

                        with open('sensor_log.txt', 'a', encoding='utf-8') as log_file:
                            log_file.write(f"{timestamp}: {sensor_data}\n")

                except json.JSONDecodeError as e:
                    log_file.write(f"{timestamp}: {data}\n")
                except Exception:
                    log_file.write(f"{timestamp}: {Exception}\n")
            else:
                # 没有接收到信息，向串口发送当前时间
                send_current_time(ser)

    except KeyboardInterrupt:
        print("程序被用户中断。")

    finally:
        ser.close()


if __name__ == "__main__":
    list_available_ports()  # 显示可用的串口
    serial_port = input("请输入串口端口（例如，COM1或/dev/ttyUSB0）：")
    baud_rate = 115200
    receive_serial_data(serial_port, baud_rate)
