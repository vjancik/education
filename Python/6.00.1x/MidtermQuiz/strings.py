def laceStrings(s1, s2):
    """
    s1 and s2 are strings.

    Returns a new str with elements of s1 and s2 interlaced,
    beginning with s1. If strings are not of same length, 
    then the extra elements should appear at the end.
    """
    s3=''
    i=0
    minLength = min(len(s1),len(s2))
    for i in range(minLength):
        s3+=s1[i]+s2[i]
    if len(s1)>len(s2):
        s3+=s1[i+1:]
    else:
        s3+=s2[i+1:]
    return s3