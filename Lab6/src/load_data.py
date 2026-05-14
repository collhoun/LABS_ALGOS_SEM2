import os


def create_file_with_size(path, size):
    with open(path, 'wb') as f:
        f.write(os.urandom(size))


def create_test_data():
    base_dir = './test_data'
    os.makedirs(base_dir, exist_ok=True)
    os.makedirs(os.path.join(base_dir, 'sub1'), exist_ok=True)
    os.makedirs(os.path.join(base_dir, 'sub2'), exist_ok=True)

    # Files in root
    create_file_with_size(os.path.join(base_dir, 'tmp_small.txt'), 512)
    create_file_with_size(os.path.join(base_dir, 'tmp_medium.txt'), 2048)
    create_file_with_size(os.path.join(base_dir, 'tmp_large.txt'), 100000)
    create_file_with_size(os.path.join(base_dir, 'log_small.log'), 100)
    create_file_with_size(os.path.join(base_dir, 'log_medium.log'), 5000)
    create_file_with_size(os.path.join(
        base_dir, 'log_large.log'), 15000)  # larger than 5000
    create_file_with_size(os.path.join(
        base_dir, 'other_file.txt'), 1000)  # no prefix

    # Files in sub1
    create_file_with_size(os.path.join(base_dir, 'sub1', 'tmp_sub1.txt'), 1024)
    create_file_with_size(os.path.join(base_dir, 'sub1', 'log_sub1.log'), 3000)

    # Files in sub2
    create_file_with_size(os.path.join(
        base_dir, 'sub2', 'tmp_sub2.txt'), 50000)
    create_file_with_size(os.path.join(base_dir, 'sub2', 'log_sub2.log'), 2000)


if __name__ == '__main__':
    create_test_data()
    print("Test data created in ./test_data")
