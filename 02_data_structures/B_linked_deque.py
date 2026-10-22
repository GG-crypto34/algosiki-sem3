import sys


class DequeNode:
    __slots__ = ('value', 'previous', 'next')

    def __init__(self, value):
        self.value = value
        self.previous = None
        self.next = None


class LinkedDeque:
    def __init__(self):
        self._first = None
        self._last = None
        self._length = 0

    def __len__(self):
        return self._length

    def append(self, value, front=False):
        node = DequeNode(value)
        if self._first is None:
            self._first = self._last = node
        elif front:
            node.next = self._first
            self._first.previous = node
            self._first = node
        else:
            node.previous = self._last
            self._last.next = node
            self._last = node
        self._length += 1

    def peek(self, front=False):
        node = self._first if front else self._last
        return 'Error' if node is None else node.value

    def remove(self, front=False):
        node = self._first if front else self._last
        if node is None:
            return 'Error'
        if node.previous is None:
            self._first = node.next
        else:
            node.previous.next = node.next
        if node.next is None:
            self._last = node.previous
        else:
            node.next.previous = node.previous
        self._length -= 1
        value = node.value
        node.previous = node.next = None
        return value


def main():
    read = sys.stdin.buffer.readline
    queue = LinkedDeque()
    for _ in range(int(read())):
        command, *arguments = read().decode().split()
        if command == 'size':
            print(len(queue))
            continue
        front = arguments[0] == 'front'
        if command == 'push':
            queue.append(arguments[1], front)
        elif command == 'pop':
            print(queue.remove(front))
        elif command == 'get':
            print(queue.peek(front))


if __name__ == '__main__':
    main()
