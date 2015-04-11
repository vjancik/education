def myLog(x, b):
    '''
    x: a positive integer
    b: a positive integer; b >= 2

    returns: log_b(x), or, the logarithm of x relative to a base b.
    '''
    # Your Code Here
    result = 0
    power = 1
    while result < x:
        result = b**power
        power+=1
    if result > x:
        return power-2
    return power-1
    
print(myLog(16,2))
print(myLog(1,2))