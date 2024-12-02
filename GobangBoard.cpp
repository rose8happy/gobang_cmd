//
// Created by i1i on 11/8/24.
//
#include "GobangBoard.h"

GobangBoard::GobangBoard() : ruleChecker(board, chess), ai(board,chess)
{
    // 初始化棋盘数组为 0（空）
    board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
}

[[noreturn]] void GobangBoard::run() {
    while (true) {
        // 开始游戏

        // 一局游戏中，画棋盘，接受指令
        while (true) {
            drawBoard();
            mousePressEvent();
        }
    }
}

void GobangBoard::start()
{
    boardReset();
    // 使用随机设备获取随机种子
    std::random_device rd;
    std::mt19937 gen(rd());  // 使用 Mersenne Twister 引擎
    std::uniform_int_distribution<> dis(1, 2);  // 设置 1 或 2 的分布
    // 生成 1 或 2 的随机数
    chess = dis(gen);
    ai.chess = chess;
    if (chess == 1) {
        isMyTurn = true;
        printf("提示 You play black and go first\n");
    } else if (chess==2)
    {
        isMyTurn = false;
        printf("提示 You play white and go second\n");
        aiPlay();
    } else
    {
        printf("提示Error");
    }
}

// void GobangBoard::onSurrenderButtonClicked()
// {
//     if (gameStarted) winOrLose(false);
// }

void GobangBoard::boardReset()
{
    for (int i=0;i<boardSize;i++)
    {
        std::fill(board[i].begin(), board[i].end(), 0);
    }
    drawBoard();
}

void GobangBoard::winOrLose(bool win)
{
    if (win)
    {
        printf("提示You win!");
    } else
    {
        printf("提示You lose!");
    }
    gameStarted = false;
    isMyTurn = false;
}

void GobangBoard::drawBoard() {
    system("cls");   //清屏
    for (int i=0;i<boardSize;i++) {
        printf("%d ", i+1);
    }
    for (int i=0;i<boardSize;i++) {
        printf("%c ", 'A'+i);
        for (int j=0;j<boardSize;j++) {
            if (i==pre_white.first && j==pre_white.second) {
                printf("▲");
            } else if (i==pre_black.first && j==pre_black.second) {
                printf("△");
            }else if (board[i][j] == 1) {
                printf("●");
            } else if (board[i][j] == 2) {
                printf("○");
            } else if (board[i][j] == 0) {
                if (i==0 && j==0) printf("┏");
                else if (i==boardSize-1 && j==boardSize-1) printf("┛");
                else if (i==0 && j==boardSize-1) printf("┓");
                else if (i==boardSize-1 && j==0) printf("┗");
                else if (i==0) printf("┃");
                else if (j==0) printf("┣");
                else if (i==boardSize-1) printf("┻");
                else if (j==boardSize-1) printf("┫");
                else printf("╋");
            }
        }
        printf("\n");
    }
}

void GobangBoard::mousePressEvent() {
    char row_c = 0; int col_i = 0;
    scanf("%c %d", &row_c, &col_i);
    getchar();

    int col = col_i;
    int row = row_c - 'A';

    if (!isMyTurn) return;

    // 在自己的回合才能下棋
    if (col >= 0 && col < boardSize && row >= 0 && row < boardSize && board[row][col] == 0) {
        // 检查禁手，禁止落子
        //ruleChecker.board = board;
        ruleChecker.chess = chess;
        if (ruleChecker.isForbiddenMove(row, col))
        {
            printf( "提示You can not put a piece here!");
            return;
        }
        isMyTurn = false; // 在AI下完棋后置回true
        board[row][col] = chess;  // 示例：黑棋放置
        drawBoard();  // 更新界面显示
        int res = ruleChecker.judge();
        if (res)
        {
            winOrLose(res==chess);
            return;
        }

        aiPlay();
    }
}

void GobangBoard::aiPlay()
{
    // 使用C++11随机数库生成一个1到2秒之间的随机延迟
    std::random_device rd;
    std::mt19937 gen(rd()); // 使用随机种子生成器
    std::uniform_int_distribution<> dis(0, 1000); // 生成1000到2000毫秒的随机数
    int delay = dis(gen); // 获取随机延迟
    // 使用QTimer单次延迟调用

    ai.chess=chess;
    auto bestMove = ai.getBestMove();
    int ai_chess = 3-chess;
    board[bestMove.first()][bestMove.second()] = ai_chess;
    drawBoard();
    int res = ruleChecker.judge();
    if (res)
    {
        winOrLose(res==chess);
        return;
    }
    isMyTurn = true;


}

