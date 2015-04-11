testBalance=balance

lowerBound=balance/12
upperBound=(balance*(1+annualInterestRate)**12)/12
lowestPayment=(upperBound+lowerBound)/2

while True:
    testBalance=balance
    for i in range(1,13):
        testBalance-=lowestPayment
        testBalance+=testBalance*annualInterestRate/12
    if testBalance>0 or testBalance<-0.01:
        if testBalance>0:
            lowerBound=lowestPayment
        elif testBalance<0:
            upperBound=lowestPayment
        lowestPayment=(upperBound+lowerBound)/2
    else:
        break
print('Lowest Payment: '+str(round(lowestPayment,2)))
