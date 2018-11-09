import tkinter as tk

wind = tk.Tk()
wind.title("tk 小程序")
wind.geometry('300x200+500+300')

# list
ll = ["C", "C++", "Java", "Python", "Lua", "R"]
lbox1 = tk.Listbox(wind)
for item in ll:
    lbox1.insert(0, item)


lbox1.pack()
wind.mainloop()
