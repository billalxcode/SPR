from string import digits

def isDigit(values: str = ""):
    for value in values:
        if value in digits: continue
        else: return False
    return True

class Text:
    def __init__(self) -> None:
        self.text = {}
        self.key = ""

    def create_new(self, key: str = ""):
        self.key = key
        self.text[key] = list()

    def set_key(self, key: str = ""):
        self.key = key

    def append(self, text: str = ""):
        self.text[self.key].append(text)

    def get(self, key: str = ""):
        output = "\n".join(self.text[key])
        return output[1:]

class Data:
    def __init__(self) -> None:
        self.data = {}
        self.key = ""

    def create_new(self, key: str = ""):
        self.key = key
        self.data[key] = dict()

    def insert(self, key: str, value: str):
        self.data[self.key][key][value]
        return True

    def get(self, key: str):
        return self.data[self.key][key]

    def delete(self, key: str):
        del self.data[self.key][key]
        return True