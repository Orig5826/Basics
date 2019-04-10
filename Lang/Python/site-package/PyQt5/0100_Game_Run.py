
import time
import random


class Person():
    def __init__(self, name, attack=10, defense=0):
        self.blood = 100
        self.name = name

        self.value_attack = attack
        self.value_defense = defense

    def get_blood(self):
        print(self.name + '\'s blood is ' + '{:.0f}'.format(self.blood))
        return self.blood

    def isalive(self):
        if self.blood == 0:
            print(self.name + '\' is dead')
            return False
        return True

    def attack(self, person):
        if self.value_attack > person.value_defense:
            variation = self.value_attack - person.value_defense
        else:
            variation = 1

        person.blood -= variation * random.random()
        if person.blood < 0:
            person.blood = 0

        person.get_blood()


class Game():
    def __init__(self):
        self.Tom = Person('Tom', 100, 20)
        self.Tony = Person('Tony', 60, 60)

        self.first = random.randint(0, 1)

    def isgame_over(self):
        if self.Tom.isalive() and self.Tony.isalive():
            return False
        return True

    def run(self):
        if self.first == 0:
            self.Tony.attack(self.Tom)
            self.first = 1
        else:
            self.Tom.attack(self.Tony)
            self.first = 0

        time.sleep(0.1)


game = Game()
while not game.isgame_over():
    game.run()

print('--- End ---')
