def McNuggets(n):
    """
    n is an int

    Returns True if some integer combination of 6, 9 and 20 equals n
    Otherwise returns False.
    """
    # Your Code Here
    if n%6==0 or n%9==0 or n%20==0:
        return True
    for i in range((n/6)+1):
        for j in range ((n/9)+1):
            for k in range ((n/20)+1):
                if i*6+j*9+k*20==n:
                    return True
    return False
    
print(McNuggets(239))