import socket  

def main():  
    try:  
        server_socket = socket.socket()  
        server_socket.bind(('0.0.0.0', 5201))  
        server_socket.listen(5)  
        print("TCP服务器启动，等待客户端连接...")  

        while True:  
            client_socket, addr = server_socket.accept()  
            print(f"连接来自：{addr}")  

            while True:  
                try:  
                    data = client_socket.recv(1024)  
                    if not data:  
                        break  
                    print(f"收到数据：{data.hex()}") 
                    client_socket.sendall(data) 
                except socket.error as e:  
                    print(f"错误：{e}，客户端连接可能已断开")  
                    break  

            client_socket.close()  

    except socket.error as e:  
        print(f"服务器启动失败：{e}")  

if __name__ == '__main__':  
    main()
