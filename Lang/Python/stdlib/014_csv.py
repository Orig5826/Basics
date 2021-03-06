
import csv


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


if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print('命令行参数：argv[1]=数据文本文件(*.csv)')
        sys.exit(-1)
    fname = sys.argv[1]
    Saleae_Logic_I2C_csv_parse(fname)
