'''
Create a BankAccount class. The bank account class should have the following attributes: balance and account_owner. The bank account class should also have deposit and withdraw methods. You should also be able to print the bank account, to display the account owners name and balance. When implemented correctly, you should be able to use the Bank account class as follows:
'''

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