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
    // 检查一个位置是否有一个禁手
    bool checkForbidden(int x, int y) const;
    // 检查活三和四子禁手
    bool checkThreeAndFour(int x, int y, int color) const;
    // 检查长连的禁手
    bool checkOverline(int x, int y, int color) const;
    // 判断某个位置的棋子是否为黑棋
    bool isBlack(int x, int y) const {
        return board[x][y] == 1;
    }
    // 判断某个位置的棋子是否为空
    bool isEmpty(int x, int y) const {
        return board[x][y] == 0;
    }
    bool checkFiveInLine(int x, int y, int dx, int dy, int color) const;
};

#endif // GOBANGRULECHECKER_H
