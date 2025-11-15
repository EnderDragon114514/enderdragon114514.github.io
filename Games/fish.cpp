#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <vector>
#include <string>
#include <algorithm>

class FishGame {
private:
    int score;
    std::vector<int> fishPos;
    const int totalTime = 20; // 游戏时间
    int mode; // 模式：0 表示无尽模式，1 表示20秒模式

public:
    FishGame(int gameMode) : score(0), mode(gameMode) {}

    void startGame() {
        std::cout << "开始游戏！" << std::endl;
        if (mode == 1) {
            std::cout << "你现在处于20秒模式，倒计时将会在你吃掉第一只小鱼后开始。" << std::endl;
        } else {
            std::cout << "你现在处于无尽模式。" << std::endl;
        }
        std::cout << "游戏开源地址：https://gitee.com/sf-yuzifu/eat-fish-together" << std::endl;

        fishPos.resize(10);
        for (int i = 0; i < 10; ++i) {
            fishPos[i] = std::rand() % 6 + 1;
        }

        auto startTime = std::chrono::system_clock::now(); // 记录游戏开始时间

        while (true) {
            if (mode == 1 && score == 0) {
                while (std::chrono::duration<double>(std::chrono::system_clock::now() - startTime).count() < totalTime) {
                    updateGame();
                    displayFish(); // 在每次更新游戏状态后刷新屏幕
                    std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms 刷新一次屏幕
                }
                std::cout << "时间到！游戏结束。" << std::endl;
                break;
            }
            updateGame();
            displayFish(); // 在每次更新游戏状态后刷新屏幕
            std::this_thread::sleep_for(std::chrono::milliseconds(200)); // 200ms 刷新一次屏幕
        }
    }

    // 其他函数的定义保持不变...
};

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    int chosenMode;
    std::cout << "请选择模式（0: 无尽模式, 1: 20秒模式）：";
    std::cin >> chosenMode;
    FishGame game(chosenMode);
    game.startGame();
    return 0;
}
