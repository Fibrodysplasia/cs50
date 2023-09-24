import re

def getCardNumber():
    while True:
        cardNumber= input("Card Number: ")
        
        pattern = pattern = r'[^0-9-]'
        if re.search(pattern, cardNumber):
            print("Invalid card number")
        else:   
            return removeNonNumerics(cardNumber)  

def removeNonNumerics(cardNumber):
    return re.sub(r'[^0-9]', '', cardNumber)

def checkLuhn(cardNumber):
    cardNumber = cardNumber[::-1]
    sum = 0
    for i in range(len(cardNumber)):
        digit = int(cardNumber[i])
        if i % 2 == 1:
            digit *= 2
            if digit > 9:
                digit -= 9
        sum += digit
    return sum % 10 == 0

def getCardType(cardNumber):
    if re.match(r'^3[47]', cardNumber) and len(cardNumber) == 15:
        return 'AMEX'
    elif re.match(r'^5[1-5]', cardNumber) and (len(cardNumber) == 16 or len(cardNumber) == 13):
        return 'MASTERCARD'
    elif re.match(r'^4', cardNumber) and (len(cardNumber) == 16 or len(cardNumber) == 13):
        return 'VISA'
    else:
        return 'INVALID'

def main():
    cardNumber = getCardNumber()
    if checkLuhn(cardNumber):
        print(getCardType(cardNumber))
    else:
        print('INVALID')
        
if __name__ == "__main__":
    main()
    
        
    
