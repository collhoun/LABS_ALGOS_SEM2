import random


def create_samples(n: int) -> list:
    """
    создает n пар ключ-значение  

    Args:
        n (int): количество пар

    Returns:
        list: список пар
    """
    possible_keys = ['key_' + str(i) for i in range(n)]
    possible_values = ['value_' + str(i) for i in range(n)]
    return list(zip(possible_keys, possible_values))


def write_samples(samples: list, file_name: str) -> bool:
    """
    записывает примеры в файл

    Args:
        samples (list): входные данные
        file_name (str): имя файля для записи

    Returns:
        bool: True если запись прошла, False в противном случае
    """
    try:
        with open(file_name, 'w') as f:
            f.write(str(len(samples)) + '\n')
            for key, value in samples:
                f.write(key + ' ' + value + '\n')
        return True
    except Exception as e:
        print(e)
        return False


def create_sorted_samples(n: int) -> list:
    """
    создает n пар ключ-значение и сортирует их

    Args:
        n (int): количетсво пар

    Returns:
        list: список отсортированных пар
    """
    samples = create_samples(n)
    samples.sort()
    return samples


def create_reversed_samples(n: int) -> list:
    """
    создает n пар ключ-значение и переворачивает их

    Args:
        n (int): количетсво пар

    Returns:
        list: список перевернутых пар
    """
    samples = create_samples(n)
    samples.reverse()
    return samples


def create_random_samples(n: int, seed: int | None = None) -> list:
    """
    создает n пар ключ-значение и перемешивает их

    Args:
        n (int): количетсво пар

    Returns:
        list: перемешанный список
    """
    if seed is None:
        seed = 42
    rnd = random.Random(seed)
    samples = create_samples(n)
    rnd.shuffle(samples)
    return samples


if __name__ == '__main__':
    sorted_samples = create_sorted_samples(30)
    random_samples = create_random_samples(30)
    reversed_samples = create_reversed_samples(30)
    write_samples(sorted_samples, 'tests/tests_data/sorted_samples.txt')
    write_samples(random_samples, 'tests/tests_data/random_samples.txt')
    write_samples(reversed_samples, 'tests/tests_data/reversed_samples.txt')
