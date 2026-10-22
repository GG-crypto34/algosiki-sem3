import sys


def maximum_divisible_pair(values):
    largest = [None, None, None]
    answer = -1
    for value in values:
        remainder = value % 3
        previous = largest[-remainder % 3]
        if previous is not None:
            answer = max(answer, value + previous)
        if largest[remainder] is None or value > largest[remainder]:
            largest[remainder] = value
    return answer


def main():
    print(maximum_divisible_pair(map(int, sys.stdin.buffer.read().split())))


if __name__ == '__main__':
    main()
