//
// Created by i1i on 11/10/24.
//

#ifndef GOBANGAI_H
#define GOBANGAI_H

#include <vector>
#include <utility>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include "GobangRuleChecker.h"

// 定义不同棋型的分数
const int WIN = 10000;
const int LIVE_FOUR = 1000;
const int RUSHED_FOUR = 500;
const int LIVE_THREE = 100;
const int SLEEP_THREE = 50;
const int LIVE_TWO = 10;

#define aiChess (3 - chess)

class GobangAI
{
public:
    GobangAI(std::vector<std::vector<int>>& board, int chess);
    std::vector<std::vector<int>>& board; // 棋盘状态
    int chess;                           // 当前执棋，1=黑棋，2=白棋

    // 计算最佳下棋位置
    std::pair<int, int> getBestMove(int depth = 2);

private:
    GobangRuleChecker ruleChecker; // 禁手规则检查类

    long long evaluateBoard();
    long long minimax(int depth, long long alpha, long long beta, bool isMaximizingPlayer);
    long long evaluateLine(int row, int col, int dx, int dy, int chess);
    bool isInBounds(int x, int y) const;
};

#endif // GOBANGAI_H
