
import csv
import sqlite3
import os

"""
    我这里说的情况，都是多行 字符串/注释的时候(即使用3个引号的情况)
    在使用引号做注释的时候，偶尔和字符串混乱，
    以后使用字符串的时候，都是用单引号，
    注释都是用双引号怎么样？
    
    2018.11.13 by jianfeng
"""

def Saleae_Logic_I2C_csv_SaveDB(csv_fname,dbfile):
    """
        逻辑分析仪，I2C导出的数据csv格式。
        可以通过该脚本直接查看收发内容
    """
    conn = sqlite3.connect(dbfile)
    c = conn.cursor()
    c.execute('''CREATE TABLE i2c_table
		(Time text, PacketID text, Address text, Data text, RorW text,ACK text)''' )
    with open(csv_fname, newline='') as csvfile:
        reader = csv.reader(csvfile)
        cnt = 0
        for row in reader:
            if cnt == 0:
                cnt += 1
                continue
            cnt += 1
            """
            # 调试的时候先存放3组数据
            if cnt > 10:
                break
            """
            data = tuple(row)
            c.execute("INSERT INTO i2c_table VALUES(?,?,?,?,?,?)",data)

    # 保存到数据库
    conn.commit()
    conn.close()
    print("SQLite创建成功")

def Saleae_Logic_I2C_dispalyDB(dbfile):
    conn = sqlite3.connect(dbfile)
    c = conn.cursor()
    for row in c.execute('SELECT * FROM i2c_table ORDER BY Time'):
        print(row)
    conn.close()
    
def Saleae_Logic_I2C_selectDB(dbfile,tuple_data):
    conn = sqlite3.connect(dbfile)
    c = conn.cursor()
    # SQLite3命令组织一下
    item = tuple_data[0]
    value = tuple_data[1],
    sql_cmd = 'SELECT * FROM i2c_table WHERE '+item+'=?'
    # 将该命令打印出来，用来调试
    print(sql_cmd+','+str(value))
    # 执行命令
    c.execute(sql_cmd,value)
    for row in c.fetchall():
        print(row)
    conn.close()
    
if __name__ == "__main__":
    import sys
    if len(sys.argv) != 2:
        print('命令行参数：argv[1]=数据文本文件(*.csv)')
        sys.exit(-1)
    fname = sys.argv[1]
    # db文件名称
    dbfile = fname.rsplit('.',maxsplit=1)[0] + '.db'
    if not os.path.exists(dbfile):
        Saleae_Logic_I2C_csv_SaveDB(fname,dbfile)
    else:
        # Saleae_Logic_I2C_dispalyDB(dbfile)
        Saleae_Logic_I2C_selectDB(dbfile,('PacketID','1'))
        Saleae_Logic_I2C_selectDB(dbfile,('Data','0xFD'))

        # 为了方便代码管理，不保留生成的文件，因此调用完毕，立刻删除
        os.remove(dbfile)
        print("SQLite已删除")
