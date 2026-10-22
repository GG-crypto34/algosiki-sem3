import sys


def evaluate_postfix(tokens):
    operands = []
    for token in tokens:
        if token not in ('+', '-', '*'):
            operands.append(int(token))
            continue
        right = operands.pop()
        left = operands.pop()
        if token == '+':
            result = left + right
        elif token == '-':
            result = left - right
        else:
            result = left * right
        operands.append(result)
    return operands[-1]


def main():
    print(evaluate_postfix(sys.stdin.read().split()))


if __name__ == '__main__':
    main()
