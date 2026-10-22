import sys


def maximum_divisible_sum(values):
    best = [0, None, None]
    for value in values:
        updated = best.copy()
        for remainder, total in enumerate(best):
            if total is None:
                continue
            candidate = total + value
            slot = (remainder + value) % 3
            if updated[slot] is None or candidate > updated[slot]:
                updated[slot] = candidate
        best = updated
    return best[0]


def main():
    values = map(int, sys.stdin.buffer.read().split())
    print(maximum_divisible_sum(values))


if __name__ == '__main__':
    main()
