#testing how classes work

class cattle():
	def __init__(self, type):
		if type == "cow":
			self.name = "Mootbing"
			self.milkable = True
		elif type == "bull":
			self.name = "Moolius"
			self.milkable = False
		self.age = 0
	def milkCow(self):
		if self.milkable:
			print("cow has been milked")
		else:
			print("bulls can't be milked silly!")
		self.age += 1
		
a = cattle("cow")
b = cattle("bull")
for i in range (10):
	print(a.name+"\n"+str(a.milkable))
	print(b.name+"\n"+str(b.milkable))
	a.milkCow()
	b.milkCow()
	print(str(a.age))
	print(str(b.age))

