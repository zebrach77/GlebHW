class Sudoku:
    def __init__(self, matr):
        self.matr = matr
        self.bean = []
        # print(self.Compute(0, 1))
        # print(self.Compute(1, 0))
        t = self.Control()
        if not t:
            print("Can't Solve")
            exit(0)
        # if not t:
        #     print("CAN'T SOLVE")
        #     exit(0)

    def Check(self, dig_map, line_arr):
        for i in line_arr:
            if i:
                dig_map[i-1] += 1
        return dig_map

    def Line(self, dig_map, line_num):
        return self.Check(dig_map, self.matr[line_num])

    def Column(self, dig_map, column_num):
        column = [self.matr[i][column_num] for i in range(9)]
        return self.Check(dig_map, column)

    def Square(self, dig_map, m, n):
        square = []
        for i in range(m*3, (m+1)*3):
            for j in range(n*3, (n+1)*3):
                square.append(self.matr[i][j])
        return self.Check(dig_map, square)

    def ZeroCount(self, arr):
        c = 0
        for i in arr:
            if not i:
                c += 1
        if c != 1:
            return False
        return True

    def Compute(self, i, j):
        map = [0 for i in range(9)]
        map = self.Line(map, i)
        map = self.Column(map, j)
        map = self.Square(map, i // 3, j // 3)
        if not 0 in map:
            return True
        if self.ZeroCount(map):
            for t in range(9):
                if map[t] == 0:
                    if not self.matr[i][j]:
                        self.matr[i][j] = t+1
                    return True
        return False

    def Control(self, i = 0, j = 0):
        b = True
        for arr in self.matr:
            if 0 in arr:
                b = False
                break
        if b:
            return True
        # if len(self.bean) > 70:
        #     self.bean = []
        for q in range(9):
            if not self.matr[i][q]:
                if not [i, q] in self.bean:
                    self.bean.append([i, q])
                    if self.Compute(i, q):
                        if self.Control(i, q):
                            return True
        for q in range(9):
            if not self.matr[q][i]:
                if not [q, j] in self.bean:
                    self.bean.append([q, j])
                    if self.Compute(q, j):
                        if self.Control(i, q):
                            return True
        for t in range((i//3)*3, (i//3)*3+3):
            for u in range((j//3)*3, (j//3)*3+3):
                if not self.matr[t][u]:
                    if not [t, u] in self.bean:
                        self.bean.append([t, u])
                        if self.Compute(t, u):
                            if self.Control(t, u):
                                return True
        for q in range(9):
            for w in range(9):
                if not self.matr[q][w]:
                    if [q, w] in self.bean:
                        self.bean.append([q, w])
                        if self.Compute(q, w):
                            if self.Control(q, w):
                                return True
        for arr in self.matr:
            if 0 in arr:
                b = False
                break
        if b:
            return True
        return False


# matr = []
# for i in range(9):
#     matr.append([int(j) for j in input().split()])
# sud = Sudoku(matr)
# for i in sud.matr:
#     for j in i:
#         print(j, end=" ")
#     print()


class Solution:
    def solveSudoku(self, board: List[List[str]]) -> None:
        M = [[int(i) if i != "." else 0 for i in j] for j in board]
        sud = Sudoku(M)
        M = sud.matr
        board = [[str(i) if i != 0 else "." for i in j] for j in M]
