# Factory Method
# オブジェクト作成時に、作成するオブジェクトのクラスをサブクラスに選ばせる

import abc


def main():
    cow = CowFactory()
    cow.check_animal()

    chiken = ChickenFactory()
    chiken.check_animal()


# Creator
class Factory:
    def __init__(self):
        self.animal = self.factory_method()
        # self.animal に対し、self.factory_method() 関数で作成したものを代入しているが、
        # self.factory_method() 自体は抽象メソッドであり、子クラスにオブジェクトの生成☆を選択させる

# こう書くと、クラス追加時にifの修正が必要（増えない、簡単な構成ならこっちでもよい）
# class Factory:
#     def __init__(self, animal_name):
#         if animal_name == "cow":
#             self.animal = Cow()
#         elif animal_name == "chicken":
#             self.animal = Chicken()


    # template_method
    def check_animal(self):
        self.animal.eat()
        self.animal.speak()

    @abc.abstractmethod
    def factory_method(self):
        pass


# Product
class Animal:
    @abc.abstractmethod
    def eat(self):
        pass

    @abc.abstractmethod
    def speak(self):
        pass


# ConcreteCreator
class CowFactory(Factory):
    # オブジェクトの生成☆
    def factory_method(self):
        return Cow()


# ConcreteCreator
class ChickenFactory(Factory):
    # オブジェクトの生成☆
    def factory_method(self):
        return Chicken()


# ConcreteProduct
class Cow(Animal):
    def eat(self):
        print("Cow:eat")

    def speak(self):
        print("Cow:speak")


# ConcreteProduct
class Chicken(Animal):
    def eat(self):
        print("Chiken:eat")

    def speak(self):
        print("Chiken:speak")


if __name__ == "__main__":
    main()