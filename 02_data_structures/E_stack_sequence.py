import sys


def is_stack_sequence(pushed, popped):
    pending = []
    next_removed = 0
    for value in pushed:
        pending.append(value)
        while pending and next_removed < len(popped) and pending[-1] == popped[next_removed]:
            pending.pop()
            next_removed += 1
    return next_removed == len(popped)


def main():
    read = sys.stdin.buffer.readline
    pushed = list(map(int, read().split()))
    popped = list(map(int, read().split()))
    print(is_stack_sequence(pushed, popped))


if __name__ == '__main__':
    main()
