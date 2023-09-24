# This should have been named Morio

def get_height():
    while True:
        height = input("What's the height of the pyramid? ")
        if height is None:
            print("Please enter a number between 1 and 8")
        else:
            if not height.isdigit():
                print("Please enter a number between 1 and 8")
            else:
                height = int(height)
                if height < 1 or height > 8:
                    print("Please enter a number between 1 and 8")
                else:
                    return height

def print_pyramid(height):
    for i in range(height):
        print(" " * (height - i - 1), end="")
        print("#" * (i + 1), end="")
        print("  ", end="")
        print("#" * (i + 1))

def main ():
    height = get_height()
    print_pyramid(height)
    
if __name__ == "__main__":
    main()
    