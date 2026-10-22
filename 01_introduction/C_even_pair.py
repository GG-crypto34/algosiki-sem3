import sys


def maximum_even_pair(values):
    largest = [None, None]
    answer = -1
    for value in values:
        parity = value % 2
        previous = largest[parity]
        if previous is not None:
            answer = max(answer, previous + value)
        if previous is None or value > previous:
            largest[parity] = value
    return answer


def main():
    print(maximum_even_pair(map(int, sys.stdin.buffer.read().split())))


if __name__ == '__main__':
    main()
