import sys


def spiral_values(matrix):
    top, bottom = 0, len(matrix) - 1
    left, right = 0, len(matrix[0]) - 1
    while top <= bottom and left <= right:
        for column in range(left, right + 1):
            yield matrix[top][column]
        top += 1
        for row in range(top, bottom + 1):
            yield matrix[row][right]
        right -= 1
        if top <= bottom:
            for column in range(right, left - 1, -1):
                yield matrix[bottom][column]
            bottom -= 1
        if left <= right:
            for row in range(bottom, top - 1, -1):
                yield matrix[row][left]
            left += 1


def main():
    read = sys.stdin.buffer.readline
    rows, columns = map(int, read().split())
    matrix = [list(map(int, read().split())) for _ in range(rows)]
    if rows and columns:
        sys.stdout.write(' '.join(map(str, spiral_values(matrix))) + '\n')


if __name__ == '__main__':
    main()
