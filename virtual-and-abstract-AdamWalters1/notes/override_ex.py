class Animal:
    def speak(self):
        print("This animal does not have a sound")

class Dog(Animal):
    def speak(self):
        print("Woof!")

class Cat(Animal):
    def speak(self):
        print("Meow!")

def animal_sound(animal):
    animal.speak()

if __name__ == "__main__":
    myAnimal = Animal()
    myDog = Dog()
    myCat = Cat()

    animal_sound(myAnimal)  # Outputs: This animal does not have a sound
    animal_sound(myDog)     # Outputs: Woof!
    animal_sound(myCat)     # Outputs: Meow!
