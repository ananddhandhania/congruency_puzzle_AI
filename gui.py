## This code is written by Anand Dhandhania ##
## 26th August, 2012

import _tkinter 
import  Tkinter as tk
from ttk import *
import subprocess
#top = gui.Tk()
matrix = []
out = []
n = 6
for i in range(n*n):
	matrix.append(0);

def callback(i,obj):
	print i
	if matrix[i] == 1:
		matrix[i] = 0
		obj["text"] = "0"
	else:
		matrix[i] = 1
		obj["text"] = "1"

	
def exe(obj):
	#print matrix
	str_args = []
	str_args.append('./structure')
	str_args.append(str(n))
	for i in range(len(matrix)):
		str_args.append(str(matrix[i]))
	#print str_args
	process = subprocess.Popen(str_args,stdout = subprocess.PIPE)
	out,err = process.communicate()
	out = out.strip()
	out = out.split(' ')
	print out
	print type(obj.Button[0])
	#obj.Button[0]["text"] = 'alpha'
	print type(out[1])
	for i in range(len(out)):
		obj.Button[i]["text"] = str(out[i])
		if(out[i] == '1'): 	
			obj.Button[i].configure(bg="red")
		if(out[i] == '2'):      
                        obj.Button[i].configure(bg="yellow")
		if(out[i] == '3'):      
                        obj.Button[i].configure(bg="green")
		if(out[i] == '4'):      
                        obj.Button[i].configure(bg="blue")
		if(out[i] == '5'):      
                        obj.Button[i].configure(bg="pink")
		if(out[i] == '6'):      
                        obj.Button[i].configure(bg="orange")
		if(out[i] == 'X'):      
                        obj.Button[i].configure(bg="black")
def flush(obj):
	for i in  range(len(matrix)):
		obj.Button[i]["text"] = "0"
		obj.Button[i]["bg"] = "grey"
		matrix[i] = 0

def assign(text):
	if text != '':
		n = int(text)

class Example(tk.Frame):
  
    def __init__(self,parent):
        tk.Frame.__init__(self,parent)   
         
        self.parent = parent
        self.Button = []
        self.initUI()
	
    
    def initUI(self):
      
        self.parent.title("Six Congruent Parts")
        self.pack(fill=tk.BOTH, expand=1)
	quitButton = tk.Button(self,text="Quit",command=self.quit)
	quitButton.place(x=100,y=50)        
	
	execute = tk.Button(self,text="Execute",command=lambda:exe(self))
        execute.place(x=350,y=50)

	clear = Button(self,text="Clear",command=lambda:flush(self))
        clear.place(x=600,y=50)

	#e = Entry(self,width=5)
	#e.place(x=500,y=300)
	#e.focus_set()
	#text = e.get()
	
	#b = Button(self, text="get", width=10, command=)
	#b.place(x=500,y=320)
	#print e.get()


     	for i in range(n):
		for j in range(n):
			self.Button.append(tk.Button(self,text=str(matrix[n*i+j]),command=lambda X = n*i+j:callback(X,self.Button[X])))
        		self.Button[n*i+j].place(x=230 + (j+1)*40,y=190+30*i)		
def main():
    print matrix
    root = tk.Tk()
    root.geometry("750x450+300+300")
    app = Example(root)
    root.mainloop()  
    print matrix	
       

if __name__ == '__main__':
    main()  
#top.mainloop()
