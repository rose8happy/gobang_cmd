//
// Created by i1i on 11/10/24.
//

#ifndef GOBANGRULECHECKER_H
#define GOBANGRULECHECKER_H

#include <vector>

class GobangRuleChecker
{
public:
    GobangRuleChecker(std::vector<std::vector<int>>& board, int chess);

    bool isForbiddenMove(int x, int y) const;
    std::vector<std::vector<int>>& board;
    int chess;
    int judge() const;

private:
    // ���һ��λ���Ƿ���һ������
    bool checkForbidden(int x, int y) const;
    // �����������ӽ���
    bool checkThreeAndFour(int x, int y, int color) const;
    // ��鳤���Ľ���
    bool checkOverline(int x, int y, int color) const;
    // �ж�ĳ��λ�õ������Ƿ�Ϊ����
    bool isBlack(int x, int y) const {
        return board[x][y] == 1;
    }
    // �ж�ĳ��λ�õ������Ƿ�Ϊ��
    bool isEmpty(int x, int y) const {
        return board[x][y] == 0;
    }
    bool checkFiveInLine(int x, int y, int dx, int dy, int color) const;
};

#endif // GOBANGRULECHECKER_H
