lowestPayment=0
step=10

testBalance=balance

while testBalance>0:
    testBalance=balance
    lowestPayment+=step
    for i in range(1,13):
        testBalance-=lowestPayment
        testBalance+=testBalance*annualInterestRate/12
print('Lowest Payment: '+str(lowestPayment))
