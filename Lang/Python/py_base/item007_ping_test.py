import subprocess
import sys
import time

def ping_target(target_ip, source_ip, packet_size=32, timeout_ms=1000):
    """
    单次执行Ping，返回：(是否成功, 结果文本行)
    """
    cmd = [
        "ping",
        target_ip,
        "-S", source_ip,
        "-l", str(packet_size),
        "-n", "1",
        "-w", str(timeout_ms)
    ]
    
    try:
        result = subprocess.run(
            cmd, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE, 
            text=True,
            creationflags=subprocess.CREATE_NO_WINDOW if sys.platform == "win32" else 0
        )
        output = result.stdout
        
        # 优先匹配成功的回复行
        for line in output.splitlines():
            stripped_line = line.strip()
            if stripped_line.startswith("来自 "):
                return True, stripped_line
        
        # 匹配失败场景
        if "请求超时" in output:
            return False, "请求超时。"
        elif "无法访问目标主机" in output:
            return False, "无法访问目标主机。"
        elif "一般性故障" in output:
            return False, "一般性故障。"
        else:
            return False, "未知错误。"
            
    except Exception as e:
        return False, f"执行异常: {str(e)}"


def ping_test(target_ip, source_ip, packet_size=32, timeout_ms=1000, count=1518):
    """
    执行多次Ping测试，循环调用单次ping，输出结果并统计
    """
    if sys.platform != "win32":
        raise EnvironmentError("此脚本仅支持 Windows 平台。")

    success_count = 0
    fail_count = 0

    # 输出和原生ping一致的头部
    print(f"正在 Ping {target_ip} 从 {source_ip} 具有 {packet_size} 字节的数据:")
    print("")

    for cnt in range(count):
        packet_size = cnt

        is_success, result_line = ping_target(
            target_ip, source_ip, packet_size, timeout_ms
        )
        print(result_line)
        
        if is_success:
            success_count += 1
        else:
            fail_count += 1
        
        # 可选：添加间隔避免占用过高
        # time.sleep(0.1)

    # 输出最终统计，格式也和原生ping对齐
    print("")
    print(f"{target_ip} 的 Ping 统计信息:")
    print(f"    数据包: 已发送 = {count}, 已接收 = {success_count}, 丢失 = {fail_count} ({int(fail_count/count*100)}% 丢失)")
    print(f"    成功率: {(success_count/count)*100:.2f}%")


if __name__ == "__main__":
    TARGET_IP = "192.168.1.100"
    SOURCE_IP = "192.168.1.102"
    # 在这里修改你要测试的包大小即可
    PACKET_SIZE = 32
    
    # 管理员权限提醒
    if sys.platform == "win32":
        import ctypes
        if not ctypes.windll.shell32.IsUserAnAdmin():
            print("⚠️ 警告: 使用 -S 指定源IP需要【管理员权限】。")
            print("如果出现'一般性故障'，请右键脚本选择'以管理员身份运行'。\n")

    try:
        # count为总发送次数，可按需修改
        ping_test(TARGET_IP, SOURCE_IP, packet_size=PACKET_SIZE, count=1518)
    except Exception as e:
        print(f"脚本执行出错: {e}")
        print("请确保：")
        print("1. 以管理员身份运行此脚本。")
        print("2. 源IP已正确配置在本地网卡上。")
