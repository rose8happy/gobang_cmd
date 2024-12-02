//
// Created by i1i on 11/10/24.
//

#include "GobangAI.h"


GobangAI::GobangAI(std::vector<std::vector<int>>& board, int chess)
    : board(board), chess(chess), ruleChecker(board, aiChess)
{
    std::srand(static_cast<unsigned>(std::time(nullptr)));  // ��ʼ�����������
}

// ��ȡ�������λ��
std::pair<int, int> GobangAI::getBestMove(int depth) {
    ruleChecker.chess = aiChess;
    long long bestScore = -100000;
    std::vector<std::pair<int, int>> bestMoves;

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == 0 && !ruleChecker.isForbiddenMove(row, col)) {
                // ��ʱ����
                board[row][col] = aiChess;

                long long score = minimax(depth - 1, -100000, 100000, false);

                // �ָ�����״̬
                board[row][col] = 0;

                if (score > bestScore) {
                    bestScore = score;
                    bestMoves.clear();
                    bestMoves.emplace_back(row, col);
                } else if (score == bestScore) {
                    bestMoves.emplace_back(row, col);
                }
            }
        }
    }

    if (bestMoves.empty()) {
        // ����һ��Ĭ��λ�ã����ߴ���û�п������ӵ�����
        return {-1, -1};  // ʾ��������Чλ��
    }
    // ���ѡ��һ����������λ��
    return bestMoves[std::rand() % bestMoves.size()];
}

long long GobangAI::evaluateBoard() {
    long long score = 0;

    // �������̣����ÿ��λ�õ����Ͳ��ӷ�
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] != 0) {
                // ��ǰ���ӵ���ɫ
                int chess = board[row][col];
                long long currentScore = 0;

                // ��鵱ǰ�������ĸ������ϵ�����
                currentScore += evaluateLine(row, col, 1, 0, chess);  // ˮƽ����
                currentScore += evaluateLine(row, col, 0, 1, chess);  // ��ֱ����
                currentScore += evaluateLine(row, col, 1, 1, chess);  // ���Խ���
                currentScore += evaluateLine(row, col, 1, -1, chess); // ���Խ���

                // AI���÷����ӣ����ֵ÷ּ���
                if (chess == aiChess) {
                    score += currentScore;
                } else {
                    score -= currentScore;
                }
            }
        }
    }
    return score;
}

// ������������������ĳһ�����ϵ�����
long long GobangAI::evaluateLine(int row, int col, int dx, int dy, int chess) {
    int count = 1;       // ����ͬɫ������
    int openEnds = 0;    // ���˵Ŀ�λ��
    long long score = 0;

    // ��һ���������
    int x = row + dx;
    int y = col + dy;
    while (isInBounds(x, y) && board[x][y] == chess) {
        count++;
        x += dx;
        y += dy;
    }
    if (isInBounds(x, y) && board[x][y] == 0) openEnds++;

    // ���෴�������
    x = row - dx;
    y = col - dy;
    while (isInBounds(x, y) && board[x][y] == chess) {
        count++;
        x -= dx;
        y -= dy;
    }
    if (isInBounds(x, y) && board[x][y] == 0) openEnds++;

    // �������ͺͿ�λ������
    if (count >= 5) {
        score = WIN;
    } else if (count == 4) {
        score = openEnds == 2 ? LIVE_FOUR : RUSHED_FOUR;
    } else if (count == 3) {
        score = openEnds == 2 ? LIVE_THREE : SLEEP_THREE;
    } else if (count == 2) {
        score = openEnds == 2 ? LIVE_TWO : 0;
    }

    // �Խ���λ�ý������⴦��
    if (chess == 1 && ruleChecker.isForbiddenMove(row, col)) {
        score = -10000;  // ����λ�ķ���
    }

    return score;
}

// �����������ж������Ƿ������̷�Χ��
bool GobangAI::isInBounds(int x, int y) const{
    return x >= 0 && x < board.size() && y >= 0 && y < board[0].size();
}

long long GobangAI::minimax(int depth, long long alpha, long long beta, bool isMaximizingPlayer) {
    if (depth == 0 || ruleChecker.judge()) {
        return evaluateBoard();
    }

    long long bestScore = isMaximizingPlayer ? -100000 : 100000;

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] == 0 && !ruleChecker.isForbiddenMove(row, col)) {
                // ��ʱ����
                board[row][col] = isMaximizingPlayer ? aiChess : chess;

                long long score = minimax(depth - 1, alpha, beta, !isMaximizingPlayer);

                // �ָ�����״̬
                board[row][col] = 0;

                // ������ѵ÷�
                if (isMaximizingPlayer) {
                    bestScore = std::max(bestScore, score);
                    alpha = std::max(alpha, score);
                } else {
                    bestScore = std::min(bestScore, score);
                    beta = std::min(beta, score);
                }

                if (beta <= alpha) {
                    return bestScore;
                }
            }
        }
    }

    return bestScore;
}
