
from tkinter import *
from tkinter.filedialog import askopenfilename
import csv

# ----- 全局变量 ------
# 文件名称
global cmd
# 命令的核心操作


def Saleae_Logic_I2C_csv_parse(csv_fname):
    '''
        逻辑分析仪，I2C导出的数据csv格式。
        可以通过该脚本直接查看收发内容
    '''
    with open(csv_fname, newline='') as csvfile:
        reader = csv.reader(csvfile)
        Packet_ID = -1
        for row in reader:
            if not row[1].isdigit():
                continue

            if row[1] != str(Packet_ID):
                print('')
                Packet_ID += 1
                if row[4] == 'Write':
                    print('-> ', end='')
                elif row[4] == 'Read':
                    print('<- ', end='')
                else:
                    pass
            data = row[3]
            print(data[2:], end=' ')


def open_file():
    file_path = askopenfilename(filetypes=[("文本文件", ".csv"), ("全部", ".*")])
    path.set(file_path)


def translate():
    file_name = path.get()
    Saleae_Logic_I2C_csv_parse(file_name)


root = Tk()
path = StringVar()
cmd = StringVar()

Entry(root, textvariable=path).grid(row=0, column=0, columnspan=3, ipadx=30)
Button(root, text="选择文件", command=open_file).grid(row=0, column=4)

Label(root, text='').grid(row=1, column=0, columnspan=3, ipadx=30)
Button(root, text="开始转换", command=translate).grid(row=1, column=4)


root.mainloop()
