import sys


def maximum_even_subset(values):
    total = 0
    smallest_odd = None
    for value in values:
        total += value
        if value % 2 and (smallest_odd is None or value < smallest_odd):
            smallest_odd = value
    return total if total % 2 == 0 else total - smallest_odd


def main():
    print(maximum_even_subset(map(int, sys.stdin.buffer.read().split())))


if __name__ == '__main__':
    main()
