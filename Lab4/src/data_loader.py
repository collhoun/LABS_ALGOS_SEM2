import random


def load_random_data(filename: str, cnt_lines: int = 20):
    rnd = random.Random()
    with open(filename, "w", encoding='utf-8') as file:
        for _ in range(cnt_lines):
            operation_number = rnd.choices(
                [1, 2, 3, 4], weights=[5, 2, 2, 3], k=1)[0]
            key = ''.join(rnd.choices(
                'abcdefghijklmnopqrstuvwxyz', k=rnd.randint(1, 6)))
            value = rnd.randint(-100, 100)
            line = f"{operation_number} {key} {value}\n"
            file.write(line)


def load_sorted_data(filename: str, data: list):
    data.sort(key=lambda x: x.split()[1])
    data = [i.split() for i in data]
    with open(filename, "w", encoding='utf-8') as file:
        for operation_number, key, value in data:
            line = f"{operation_number} {key} {value}\n"
            file.write(line)


def read_data(filename: str):
    with open(filename, "r", encoding='utf-8') as file:
        return file.readlines()


if __name__ == '__main__':
    load_random_data("./data/samples.txt")
    data = read_data("./data/samples.txt")
    load_sorted_data("./data/sorted_samples.txt", data)
