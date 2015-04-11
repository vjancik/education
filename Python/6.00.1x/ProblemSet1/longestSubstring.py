beginLongest=0
endLongest=1
begin=0
end=1
length=1
longestLength=1
i=0
j=0
while i!=len(s)-1:
    begin=i
    j=i
    length=1
    while j!=len(s)-1 and ord(s[j])<=ord(s[j+1]):
        j+=1
        length+=1
        end=j+1
    if length>longestLength:
        longestLength=length
        beginLongest=begin
        endLongest=end
    i+=1
print('Longest substring in alphabetical order is: '+s[beginLongest:endLongest])
