import sys


class QueueNode:
    __slots__ = ('value', 'next')

    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedQueue:
    def __init__(self):
        self._first = None
        self._last = None
        self._length = 0

    def __len__(self):
        return self._length

    def append(self, value):
        node = QueueNode(value)
        if self._last is None:
            self._first = node
        else:
            self._last.next = node
        self._last = node
        self._length += 1

    def front(self):
        return 'Error' if self._first is None else self._first.value

    def remove(self):
        if self._first is None:
            return 'Error'
        value = self._first.value
        self._first = self._first.next
        self._length -= 1
        if self._first is None:
            self._last = None
        return value


def main():
    read = sys.stdin.buffer.readline
    queue = LinkedQueue()
    for _ in range(int(read())):
        command, *arguments = read().decode().split()
        if command == 'push':
            queue.append(arguments[0])
        elif command == 'pop':
            print(queue.remove())
        elif command == 'get':
            print(queue.front())
        elif command == 'size':
            print(len(queue))


if __name__ == '__main__':
    main()
