
from tkinter import *

class window(Tk):
    def __init__(self):
        super().__init__()
        
        # 分辨率
        self.width = 64
        self.height = 64
        # 点大小
        self.point_width = 5
        
        width = self.width * self.point_width
        height = self.height * self.point_width
        self.canvas = Canvas(self, width=width, height=height, background = "white")
        self.canvas.grid(row = 100, column = 100)
        
    def draw_point(self, x, y):
        x0 = (x+1) * self.point_width
        y0 = (y+1) * self.point_width
        x1 = (x+2) * self.point_width
        y1 = (y+2) * self.point_width
        self.canvas.create_rectangle(x0, y0, x1, y1, fill="black")
    
    def draw_line(self, x0, y0, x1, y1):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        
        
app = window()
app.draw_point(10,10)
app.draw_line(10,10,20,20)
app.mainloop()
