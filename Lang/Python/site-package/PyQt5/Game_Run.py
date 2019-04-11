
import time
import random


class Person():
    def __init__(self, name, attack=10, defense=0):
        self.blood = 100
        self.name = name

        self.value_attack = attack
        self.value_defense = defense

    def __str__(self):
        return self.name

    def get_blood(self):
        # print(self.name + '\'s blood is ' + '{:.0f}'.format(self.blood))
        return int(self.blood)

    def isalive(self):
        if self.blood == 0:
            # print(self.name + '\' is dead')
            return False
        return True

    def attack(self, person):
        if self.value_attack > person.value_defense:
            variation = self.value_attack - person.value_defense
        else:
            variation = 5

        person.blood -= variation * random.randint(5, 10)/10
        if person.blood < 0:
            person.blood = 0

        person.get_blood()


class Game():
    def __init__(self):
        self.Tom = Person('Tom', 35, 5)
        self.Tony = Person('Tony', 30, 10)

        self.first = random.randint(0, 1)

    def isgame_over(self):
        if self.Tom.isalive() and self.Tony.isalive():
            return False
        return True

    def who_win(self):
        if self.Tom.isalive():
            return str(self.Tom)
        else:
            return str(self.Tony)

    def get_blood(self, name):
        if name == str(self.Tom):
            return self.Tom.get_blood()
        if name == str(self.Tony):
            return self.Tony.get_blood()

    def run(self):
        if self.first == 0:
            self.Tony.attack(self.Tom)
            self.first = 1
        else:
            self.Tom.attack(self.Tony)
            self.first = 0

        # time.sleep(0.1)
        return self.first


"""
game = Game()
while not game.isgame_over():
    game.run()

print('--- End ---')`
"""
