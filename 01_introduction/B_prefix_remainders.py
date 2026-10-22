import sys


def prefix_remainders(digits, modulus):
    remainder = 0
    for digit in digits:
        remainder = (remainder * 10 + digit - ord('0')) % modulus
        yield remainder


def main():
    read = sys.stdin.buffer.readline
    length, modulus = map(int, read().split())
    digits = read().strip()
    sys.stdout.write(' '.join(map(str, prefix_remainders(digits[:length], modulus))) + '\n')


if __name__ == '__main__':
    main()
