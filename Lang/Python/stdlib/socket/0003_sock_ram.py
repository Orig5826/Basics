import socket
import struct

sock = socket.socket(socket.AF_PACKET, socket.SOCK_RAW, socket.htons(0x0003))
 
# 绑定到所有网络接口上
sock.bind(('', 0))
 
# 设置套接字选项，允许捕获所有接收到的数据包
sock.setsockopt(socket.SOL_SOCKET, socket.SO_RCVBUF, 1024 * 1024)
 
print("Listening on network interface. Press Ctrl+C to stop...")
 
try:
    while True:
        # 无限循环，等待接收数据包
        data = sock.recvfrom(65565)
        packet_data = data[0]
        header = packet_data[0:14]
        dst_mac, src_mac, eth_proto = struct.unpack('! 6s 6s H', header)
 
        print(f"Destination MAC: {dst_mac.hex().upper()}")
        print(f"Source MAC: {src_mac.hex().upper()}")
        print(f"Ether Type: {eth_proto}")
        # 输出剩余的数据包内容，如果需要进一步分析，可以根据以太网类型(eth_proto)来解析
        print(packet_data[14:])
finally:
    sock.close()