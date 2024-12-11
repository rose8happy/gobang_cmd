#include "GobangBoard.h"

GobangBoard::GobangBoard() : ruleChecker(board, chess), ai(board, chess) {
    board = std::vector<std::vector<int>>(boardSize, std::vector<int>(boardSize, 0));
    pre_white = {-1, -1};
    pre_black = {-1, -1};
}

void GobangBoard::run() {
    while (true) {
        start();
        while (gameStarted) {
            mousePressEvent();
        }
        printf("是否开始下一把游戏? (y/n): ");
        char choice;
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') break;
    }
}

void GobangBoard::start() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 2);
    chess = dis(gen);
    ai.chess = 3 - chess;
    if (chess == 1) {
        isMyTurn = true;
        printf("提示: 你执黑棋并先行\n");
    } else if (chess == 2) {
        isMyTurn = false;
        printf("提示: 你执白棋并后行\n");
        //aiPlay();
    }
    printf("黑棋禁手三三、四四、长连。白棋第一手需要下在上半区。\n");
    printf("按下任意键开始游戏\n");
    //clearInputBuffer();  // 清空输入缓冲区
    getchar();  // 等待用户按键
    gameStarted = true;
    boardReset();
    if (chess == 2) {
        aiPlay();
    }
}

void GobangBoard::boardReset() {
    for (int i = 0; i < boardSize; i++) {
        std::fill(board[i].begin(), board[i].end(), 0);
    }
    drawBoard();
}

void GobangBoard::winOrLose(bool win) {
    if (win) {
        printf("你赢了！\n");
    } else {
        printf("很遗憾你输了。\n");
    }
    gameStarted = false;
    isMyTurn = false;
}

void GobangBoard::drawBoard() {
    clearScreen();   //清屏
    printf("  ");
    for (int i=0;i<boardSize;i++) {
        printf("%-2d ", i+1);
    }
    printf("\n");
    for (int i=0;i<boardSize;i++) {
        printf("%c ", 'A'+i);
        for (int j=0;j<boardSize;j++) {
            if (i==pre_black.first && j==pre_black.second) {
                printf("▲");
            } else if (i==pre_white.first && j==pre_white.second) {
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
                else if (i==0) printf("┯");
                else if (j==0) printf("┣");
                else if (i==boardSize-1) printf("┻");
                else if (j==boardSize-1) printf("┫");
                else printf("╋");
            }
            printf("  ");
        }
        printf("\n");
    }
    printf("黑棋●白棋○黑棋上一步▲白棋上一步△\n");
    int pre_x, pre_y;
    if (chess == 1) {
        pre_x = pre_white.first;
        pre_y = pre_white.second;
    } else {
        pre_x = pre_black.first;
        pre_y = pre_black.second;
    }
    printf("对方上一步棋%c %d\n", pre_x + 'A', pre_y + 1);
    // 提示执棋
    if (chess == 1) printf("你执黑棋 ");
    else printf("你执白棋 ");
    printf("输入要下的位置坐标如 A 1\n");
}

void GobangBoard::mousePressEvent() {
    std::string input;
    std::getline(std::cin, input);

    if (input.size() < 3 || input[0] < 'A' || input[0] >= 'A' + boardSize || input[2] < '1' || input[2] > '9') {
        printf("无效输入。请按照这个格式输入 A 1。\n");
        return;
    }

    int row = input[0] - 'A';
    int col = input[2] - '1';

    if (!isMyTurn) return;

    if (col >= 0 && col < boardSize && row >= 0 && row < boardSize && board[row][col] == 0) {
        ruleChecker.chess = chess;
        if (ruleChecker.isForbiddenMove(row, col)) {
            printf("禁手！ 你不能在这个点落子！\n");
            return;
        }
        isMyTurn = false;
        board[row][col] = chess;
        if (chess == 1)
            pre_black = {row, col};
        else
            pre_white = {row, col};
        //drawBoard();
        int res = ruleChecker.judge();
        if (res) {
            winOrLose(res == chess);
            return;
        }
        aiPlay();
    } else {
        printf("无效输入1。请按照这个格式输入 A 1。\n");
    }
}

void GobangBoard::aiPlay() {
    ai.chess = chess;
    auto bestMove = ai.getBestMove();
    if (chess == 1)
        pre_white = bestMove;
    else
        pre_black = bestMove;
    int ai_chess = 3 - chess;
    board[bestMove.first][bestMove.second] = ai_chess;
    drawBoard();
    int res = ruleChecker.judge();
    if (res) {
        winOrLose(res == chess);
        return;
    }
    isMyTurn = true;
}

void GobangBoard::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void GobangBoard::clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
