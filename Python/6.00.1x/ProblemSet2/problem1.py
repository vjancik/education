totalPaid=0

for i in range(1,13):
    print('Month: '+str(i))
    print('Minimum monthly payment: '+str(round(balance*monthlyPaymentRate,2)))
    totalPaid+=balance*monthlyPaymentRate
    balance=balance-balance*monthlyPaymentRate
    balance=balance+balance*annualInterestRate/12
    print('Remaining balance: '+str(round(balance,2)))
print('Total paid: '+str(round(totalPaid,2)))
print('Remaining balance: '+str(round(balance,2)))
