
import tkinter as tk
from tkinter.filedialog import askopenfilename, asksaveasfilename
import csv
import time
import os

def Saleae_Logic_I2C_csv_parse(csv_fname):
    '''
        逻辑分析仪，I2C导出的数据csv格式。
        可以通过该脚本直接查看收发内容
    '''
    ss = ''
    with open(csv_fname, newline='') as csvfile:
        reader = csv.reader(csvfile)
        Packet_ID = -1
        for row in reader:
            print('<{},{}>'.format(Packet_ID,row[1]))
            if not row[1].isdigit():
                if row[1] == '':
                    Packet_ID += 1
                continue
            if row[1] != str(Packet_ID):
                # print('')
                ss += "\n"
                Packet_ID += 1
                if row[4] == 'Write':
                    # print('-> ', end='')
                    ss += "-> "
                elif row[4] == 'Read':
                    # print('<- ', end='')
                    ss += "<- "
                else:
                    pass
            data = row[3]
            # print(data[2:], end=' ')
            ss += data[2:] + ' '
    return ss


def open_file():
    file_path = askopenfilename(filetypes=[("文本文件", ".csv"), ("全部", ".*")])
    path.set(file_path)
    cmd.set('请点击"开始转换"')


def translate(save_mode=0):
    # 将输出文件放在和源文件同一个目录下
    file_name = path.get()
    # 开始转换
    ss = Saleae_Logic_I2C_csv_parse(file_name)
    if save_mode == 0:
        file_output = file_name.rsplit('.', maxsplit=1)
        # 获取当前时间
        now = time.strftime("_%Y%m%d_%H%M%S")
        file_output = file_output[0] + now + '.txt'
    elif save_mode == 1:
        # 通过对话框打开文件
        file_output = asksaveasfilename(
            defaultextension='.txt', filetypes=[("文本文件", ".txt")],
            initialfile='saleae_logic_i2c.txt')
    else:
        return False
    with open(file_output, 'w') as ff:
        ff.write(ss)
    ff.close()
    cmd.set('转换完成')


# tk实例化
root = tk.Tk()
path = tk.StringVar()
cmd = tk.StringVar()

# 添加控件
root.title('Saleae辅助工具 v1.0')
# 如果打包程序，这个不太方便
ico = "./res/apaki.ico"
if os.path.exists(ico):
    root.iconbitmap(default=ico)
root.resizable(False, False)  # 大小不可变
cmd.set('请选择文件...')

# 第一行
tk.Entry(root, textvariable=path).grid(row=0, column=0, columnspan=2, ipadx=50)
tk.Button(root, text="选择文件", command=open_file).grid(row=0, column=2)
# 第二行
tk.Label(root, textvariable=cmd).grid(row=1, column=0, columnspan=2, ipadx=50)
tk.Button(root, text="开始转换", command=lambda: translate(1)).grid(row=1, column=2)

# tk运行
root.mainloop()
