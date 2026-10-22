import sys


def merge_sorted(left, right):
    first = second = 0
    while first < len(left) and second < len(right):
        if left[first] <= right[second]:
            yield left[first]
            first += 1
        else:
            yield right[second]
            second += 1
    while first < len(left):
        yield left[first]
        first += 1
    while second < len(right):
        yield right[second]
        second += 1


def main():
    data = list(map(int, sys.stdin.buffer.read().split()))
    first_size, second_size = data[:2]
    split = 2 + first_size
    result = merge_sorted(data[2:split], data[split:split + second_size])
    sys.stdout.write(' '.join(map(str, result)) + '\n')


if __name__ == '__main__':
    main()
