import os

for i in range(0, 10):
    print("i = %d" % i)
    # 需要调用的程序
    # 相对路径和绝对路径都可以，和cmd没什么区别
    # 因为我们用的就是cmd程序呀
    # exe = r"C:\Users\Administrator\Desktop\aardvark-api-windows-i686-v5.30\c\_output\aalights.exe "
    exe = r".\aalights.exe "
    # 程序需要执行的次数
    arg = "0"
    os.system("cmd /c" + exe + arg)
