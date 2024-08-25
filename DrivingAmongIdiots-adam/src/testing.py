def isPalindrome(x):
        list = str(x).split()
        if x<0:
            return False
        for i in range(len(list)):
            j = -1*(i+1)
            print(list[i],list[j])
            if list[i] != list[j]:
                return False
        return True
    
print(isPalindrome(121))
print(isPalindrome(-121))
print(isPalindrome(10))