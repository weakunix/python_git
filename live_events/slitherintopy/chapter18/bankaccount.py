class bankAccount:
    def __init__(self, name, bal):
        self.name = name
        self.bal = bal
    def deposit(self, money):
        self.bal += money
    def withdraw(self, money):
        self.bal -= money
    def __str__(self):
        return "Owner: "+str(self.name)+"\nBalance: $"+str(self.bal)
    
bingbingbank = bankAccount("Bing", 1000)
bingbingbank.withdraw(10)
print(bingbingbank)
bingbingbank.deposit(10000)
print(bingbingbank)