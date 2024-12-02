//
// Created by i1i on 11/10/24.
//
#include "GobangRuleChecker.h"


GobangRuleChecker::GobangRuleChecker(std::vector<std::vector<int>>& board, int chess)
    : board(board), chess(chess) {}

// �ж�ĳ��λ���Ƿ�Ϊ����
bool GobangRuleChecker::isForbiddenMove(int x, int y) const {
    if (isEmpty(x, y)) {
        return checkForbidden(x, y);
    }
    return false;
}

// �����ֵ���ع���
bool GobangRuleChecker::checkForbidden(int x, int y) const {
    if (chess == 2)
    {
        // ������֣������һ�֣�ֻ�������°���
        for (auto & i : board)
        {
            for (int j : i)
            {
                if (j == 2)
                {
                    return false;
                }
            }
        }
        return x >= board.size() / 2;
    }
    if (chess == 1)
    {
        // �������������Լ���������Ľ���
        if (checkThreeAndFour(x, y, 1)) {
            return true; // �������
        }

        if (checkOverline(x, y, 1)) {
            return true; // �������
        }
    }

    return false;
}

// ������������ĵĽ���
bool GobangRuleChecker::checkThreeAndFour(int x, int y, int color) const {
    int jd = judge();
    if (jd == 1)
    {
        return false;
    }
    // ����ĸ�����
    int directions[4][2] = {
        {1, 0}, // ˮƽ��
        {0, 1}, // ��ֱ��
        {1, 1}, // ���Խ��ߣ����£�
        {1, -1} // ���Խ��ߣ����ϣ�
    };

    int countThree = 0; // ��¼�ҵ��Ļ�������
    int countFour = 0;  // ��¼�ҵ��Ļ��ĸ���

    for (auto & direction : directions) {
        int dx = direction[0];
        int dy = direction[1];

        // ��鵱ǰ�����ϵĻ����ͻ���
        int count = 1; // ��ǰ����������

        // ��һ����������
        int nx = x + dx;
        int ny = y + dy;
        while (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            count++;
            nx += dx;
            ny += dy;
        }

        // ���෴��������
        nx = x - dx;
        ny = y - dy;
        while (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            count++;
            nx -= dx;
            ny -= dy;
        }

        // �жϻ����ͻ���
        if (count == 3) {
            // ����ڵ�ǰ�������γɻ�������������Ƿ��п�λ
            if ((x + dx * 3 >= 0 && x + dx * 3 < board.size() && y + dy * 3 >= 0 && y + dy * 3 < board[0].size() && board[x + dx * 3][y + dy * 3] == 0) &&
                (x - dx >= 0 && x - dx < board.size() && y - dy >= 0 && y - dy < board[0].size() && board[x - dx][y - dy] == 0)) {
                countThree++;
            }
        }

        if (count == 4) {
            // ����ڵ�ǰ�������γɻ��ģ���������Ƿ��п�λ
            if ((x + dx * 4 >= 0 && x + dx * 4 < board.size() && y + dy * 4 >= 0 && y + dy * 4 < board[0].size() && board[x + dx * 4][y + dy * 4] == 0) &&
                (x - dx >= 0 && x - dx < board.size() && y - dy >= 0 && y - dy < board[0].size() && board[x - dx][y - dy] == 0)) {
                countFour++;
            }
        }
    }

    // ����ҵ������������������ģ�����true����ʾ����
    return (countThree >= 2 || countFour >= 2);
}


// ��鳤���Ľ���
bool GobangRuleChecker::checkOverline(int x, int y, int color) const {
    // ����ĸ�����
    int directions[4][2] = {
        {1, 0}, // ˮƽ��
        {0, 1}, // ��ֱ��
        {1, 1}, // ���Խ��ߣ����£�
        {1, -1} // ���Խ��ߣ����ϣ�
    };

    for (auto & direction : directions) {
        int dx = direction[0];
        int dy = direction[1];

        int count = 1; // ��ǰ����������

        // ��һ����������
        int nx = x + dx;
        int ny = y + dy;
        while (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            count++;
            nx += dx;
            ny += dy;
        }

        // ���෴��������
        nx = x - dx;
        ny = y - dy;
        while (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            count++;
            nx -= dx;
            ny -= dy;
        }

        // ����Ƿ񳬹��������
        if (count > 5) {
            return true; // ������������ڳ���
        }
    }

    return false; // û�г���
}

int GobangRuleChecker::judge() const {
    // �����������̣����ÿ��λ�õ������Ƿ��γ�������
    for (int x = 0; x < board.size(); ++x) {
        for (int y = 0; y < board[0].size(); ++y) {
            int color = board[x][y];
            if (color != 0) { // ������λ��������
                // ����ĸ������Ƿ��γ�������
                if (checkFiveInLine(x, y, 1, 0, color) || // ˮƽ
                    checkFiveInLine(x, y, 0, 1, color) || // ��ֱ
                    checkFiveInLine(x, y, 1, 1, color) || // ���¶Խ���
                    checkFiveInLine(x, y, 1, -1, color))  // ���¶Խ���
                {
                    return color; // ����ҵ������飬���ػ�ʤ������ɫ��1=���壬2=���壩
                }
            }
        }
    }
    return 0; // ���û���ҵ������飬����0��ʾ���˻�ʤ
}

// �������������ĳ���������Ƿ��γ�������
bool GobangRuleChecker::checkFiveInLine(int x, int y, int dx, int dy, int color) const {
    int count = 1;
    // ��������
    for (int i = 1; i < 5; ++i) {
        int nx = x + i * dx, ny = y + i * dy;
        if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            ++count;
        } else {
            break;
        }
    }
    // ��������
    for (int i = 1; i < 5; ++i) {
        int nx = x - i * dx, ny = y - i * dy;
        if (nx >= 0 && nx < board.size() && ny >= 0 && ny < board[0].size() && board[nx][ny] == color) {
            ++count;
        } else {
            break;
        }
    }
    return count >= 5; // ����������飬����true
}


