# Iterator パターン
# 各要素に順番にアクセス

# pythonではビルトインの形でIteratorをサポートしている。

def main():
    my_iterator = Hoge(10, 20, 30)
    for num in my_iterator:
        print(num)


class Hoge:

    def __init__(self, *numbers):
        self._numbers = numbers
        self._i = 0

    def __iter__(self):
        print("__iter__ is called")
        return self
        # return "hoge" # => TypeError: iter() returned non-iterator of type 'str'

    def __next__(self):
        print("__next__ is called")
        if self._i == len(self._numbers):
            raise StopIteration()
        value = self._numbers[self._i]
        self._i += 1
        return value


if __name__ == "__main__":
    main()


#  あるオブジェクトがイテレータを期待するコンテクストに置かれると、
# （例：for i in object: となると）

# __iter__ メソッドが呼ばれる
# イテレート（繰り返し）するたびに__next__メソッドが呼ばれる
# StopIteration()をraiseすると繰り返しが止まる