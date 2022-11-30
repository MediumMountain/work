# クラス内クラス

## 専属のクラスをクラスの中に作ることができる
## Javaではそのまま使用できるが、Pythonでは「self」を渡す必要がある

```
class Outer:

    def sample(self, value):
        self.value = value

        # selfを渡す必要がある
        self.Inner(self).print()

    class Inner:

        def __init__(self, outer):
            self.outer = outer

        def print(self):
            print(self.outer.value)

Outer().sample(123)
```