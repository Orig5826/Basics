
from tkinter import *
import time

class window(Tk):
    def __init__(self):
        super().__init__()
        
        # 分辨率
        self.width = 64 # >=64
        self.height = 64 # >= 64
        # 点大小
        self.point_width = 10
        
        width = self.width * self.point_width
        height = self.height * self.point_width
        self.canvas = Canvas(self, width=width, height=height, background = "white")
        self.canvas.grid(row=0, column=0)
        
    def draw_point(self, x, y, color="#000000"):
        x0 = int(x) * self.point_width
        y0 = int(y) * self.point_width
        x1 = int(x + 1) * self.point_width
        y1 = int(y + 1) * self.point_width
        # print(x0,y0,x1,y1)
        # self.canvas.create_rectangle(x0, y0, x1, y1, fill="black")
        self.canvas.create_rectangle(x0, y0, x1, y1, fill=color)
        
    def draw_point_test(self):
        app.draw_point(0, 0)
        app.draw_point(0, app.height - 1)
        app.draw_point(app.width - 1, 0)
        app.draw_point(app.width - 1, app.height - 1)
        
    def draw_line(self, x0, y0, x1, y1, color="#ffffff"):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        sx = -1 if x0 > x1 else 1
        sy = -1 if y0 > y1 else 1
        
        k = dy/dx
        b = y0 - k*x0
        
        x = x0
        y = y0
        if dx > dy:
            cnt = dx + 1
            for i in range(cnt):
                self.draw_point(x, y, color)
                x += sx
                y = k*x + b
        else:
            cnt = dy + 1
            for i in range(cnt):
                self.draw_point(x, y, color)
                y += sy
                x = (y - b)/k
                
    def draw_line2(self, x0, y0, x1, y1, color="#ffffff"):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        sx = -1 if x0 > x1 else 1
        sy = -1 if y0 > y1 else 1
        
        if dy < dx:
            # 斜率小于1
            
        else:
            # 斜率大于1
            
        
    def draw_line_test(self):
        draw_line = self.draw_line
    
        start = time.perf_counter()
        draw_line(32, 32, 64, 64, "#0000ff")
        draw_line(32, 32, 48, 64, "#00ff00")
        draw_line(32, 32, 64, 48, "#00ffff")
        
        draw_line(0, 0, 32, 32, "#ff0000")
        draw_line(0, 16, 32, 32, "#ff00ff")
        draw_line(16, 0, 32, 32, "#ffff00")
        
        end = time.perf_counter()
        
        execution_time = end - start
        print(f"执行时间：{execution_time * 1000 * 1000} us")
        

if __name__ == '__main__':
    app = window()
    # app.draw_point_test()
    app.draw_line_test()
    
    app.mainloop()
