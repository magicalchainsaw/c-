#pragma once
#include "scenemanager.h"
#include "region.h"
#include <graphics.h>
#include <tchar.h>
#include <vector>
#include <iostream>
extern scenemanager scene_manager;
extern int board_data[5][5];
extern int temp_board[5][5];
extern std::vector<std::vector<int>> vec;
extern std::vector<std::vector<int>> vec1;
class give_scene : public scene
{
public:
    give_scene() = default;
    ~give_scene() {}

    void on_enter() {
        setbkcolor(RGB(173, 216, 230));
        settextcolor(WHITE);
        vec.clear();
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                board_data[i][j] = 0;
                temp_board[i][j] = 0;
                usedCells[i][j] = false;
            }

        }
        
        clickSequence.clear();
      
        _tcscpy_s(statusText, 64, _T("开始点击: 0/5"));
    }

    void on_update(int delta) {
        if(counter>=5)
        for (int i = 0; i < 5; i++)
        {
            list[i].on_update(delta);
        }
    }

    void on_draw() {
        
        cleardevice();

        setlinecolor(BLACK);
        setlinestyle(PS_SOLID, 1);
        for (int i = 0; i < 6; i++) {
            line(340, 20 + 120 * i, 940, 20 + 120 * i);
            line(340 + 120 * i, 20, 340 + 120 * i, 620);
        }

     
        settextstyle(24, 0, _T("Arial"));
        setbkmode(TRANSPARENT);
        settextcolor(BLACK); 

     
        if(counter<5)
        outtextxy(10, 20, statusText);
        else
        {
            outtextxy(10, 20, statusText);
        }
        for (int i=0;i<counter;i++)
        {
            list[i].on_draw();
        }
        settextstyle(60, 0, _T("Arial"));
        settextcolor(BLACK);
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (!(board_data[i][j] == 0))
                {
                    TCHAR str[32];
                    _stprintf_s(str, _T("%d"), board_data[i][j]);
                    outtextxy(340 + 120 * j + (120 - textwidth(str)) / 2, 20 + 120 * i + (120 - textheight(str)) / 2, str);
                }
            }
        }
     
    }

    void on_input(const ExMessage msg) {
        if (msg.message == WM_LBUTTONDOWN&&counter<5) {
            int lie = ((msg.x - 340) / 120)+1;
            int han = ((msg.y - 20) / 120)+1;

            
            if (han >= 1 && han < 6 && lie >= 1 && lie < 6) {
                handleClick(han, lie);
            }
            else {
            
                _stprintf_s(statusText, 64, _T("点击在棋盘外!"));
            }
        }
        if (counter >= 5)
        {
            for (int i = 0; i < 5; ++i)
            {
                list[i].on_input(msg);
            }
            if (msg.message == WM_KEYDOWN)
            {
                switch (msg.vkcode)
                {
                case 0x45:
                    for (int i = 0; i < 5; ++i)
                    {
                        list[i].on_update(0);
                    }
                    if (!hasCompleteCoverage())
                    {
                        _tcscpy_s(statusText, 64, _T("区域必须覆盖全部25格"));
                        break;
                    }
                    {
                        int solutionCount = countSolutions(2);
                        if (solutionCount == 0)
                        {
                            _tcscpy_s(statusText, 64, _T("当前题目无解"));
                            break;
                        }
                        if (solutionCount > 1)
                        {
                            _tcscpy_s(statusText, 64, _T("当前题目不是唯一解"));
                            break;
                        }
                    }
                    for (int i = 0; i < 5; ++i)
                    {
                        for (int j = 0; j < 5; ++j)
                            if (!(board_data[i][j] == 0))
                            {
                                temp_board[i][j] = board_data[i][j];
                            }
                    }
                    scene_manager.switchto(scenemanager::scenetype::walk);
                    break;
                }
                
            }
        }
    }

    void on_exit() {
        counter = 0;

    }

private:
    struct ClickPos {
        int han;
        int lie;


        bool operator==(const ClickPos& other) const {
            return han == other.han && lie == other.lie;
        }
    };

    std::vector<ClickPos> clickSequence;
    TCHAR statusText[64]; 
    bool usedCells[5][5] = {};

    bool isAdjacent(int han1, int lie1, int han2, int lie2) {
        int rowDiff = abs(han1 - han2);
        int colDiff = abs(lie1 - lie2);

       
        return (rowDiff + colDiff == 1);
    }

    bool isAdjacentToAny(int han, int lie) {
        for (const auto& pos : clickSequence) {
            if (isAdjacent(pos.han, pos.lie, han, lie)) {
                return true;
            }
        }
        return false;
    }

    void handleClick(int han, int lie) {
        ClickPos newPos = { han, lie };
        if (usedCells[han - 1][lie - 1]) {
            _stprintf_s(statusText, 64, _T("该格已在其他区域 当前: %d/5"), static_cast<int>(clickSequence.size()));
            return;
        }

        if (clickSequence.empty()) {
            clickSequence.push_back(newPos);
            _stprintf_s(statusText, 64, _T("连续点击: %d/5"), static_cast<int>(clickSequence.size()));
            return;
        }

        for (const auto& pos : clickSequence) {
            if (pos == newPos) {
                _stprintf_s(statusText, 64, _T("位置重复! 当前: %d/5"), static_cast<int>(clickSequence.size()));
                return;
            }
        }

 
        if (!isAdjacentToAny(han, lie)) {
          
            clickSequence.clear();
            clickSequence.push_back(newPos);
            _stprintf_s(statusText, 64, _T("不相邻! 重新开始: 1/5"));
            return;
        }

      
        clickSequence.push_back(newPos);

       
        _stprintf_s(statusText, 64, _T("连续点击: %d/5"), static_cast<int>(clickSequence.size()));

  
        if (clickSequence.size() == 5) {
            processFiveClicks();
            
            clickSequence.clear();
            if (counter < 5)
            {
                _tcscpy_s(statusText, 64, _T("区域已保存，继续选择"));
            }
            else
            {
                _tcscpy_s(statusText, 64, _T("填写提示数，按E保存"));
            }
        }
    }

    void processFiveClicks() {
        std::vector<int> temp;
        std::cout << "检测到5次连续相邻点击:" << std::endl;
        for (size_t i = 0; i < clickSequence.size(); i++) {
            auto& pos = clickSequence[i];
            std::cout << "(" << pos.han << ", " << pos.lie << ")";
            temp.push_back(5 * pos.han - 5 + pos.lie);
        }
        vec.push_back(temp);

        list[counter].setregion(temp[0],temp[1],temp[2],temp[3],temp[4]);
        for (const auto& pos : clickSequence)
        {
            usedCells[pos.han - 1][pos.lie - 1] = true;
        }
        counter++;
      
    }
    bool hasCompleteCoverage()
    {
        int usedCount = 0;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (usedCells[i][j])
                {
                    usedCount++;
                }
            }
        }
        return counter == 5 && vec.size() == 5 && usedCount == 25;
    }
    bool buildRegionMap(int regionMap[5][5])
    {
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                regionMap[i][j] = -1;
            }
        }
        if (vec.size() != 5)
        {
            return false;
        }
        for (int regionIndex = 0; regionIndex < 5; ++regionIndex)
        {
            if (vec[regionIndex].size() != 5)
            {
                return false;
            }
            for (int cellNumber : vec[regionIndex])
            {
                if (cellNumber < 1 || cellNumber > 25)
                {
                    return false;
                }
                int row = (cellNumber - 1) / 5;
                int col = (cellNumber - 1) % 5;
                if (regionMap[row][col] != -1)
                {
                    return false;
                }
                regionMap[row][col] = regionIndex;
            }
        }
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (regionMap[i][j] == -1)
                {
                    return false;
                }
            }
        }
        return true;
    }
    int solveGrid(int grid[5][5], int regionMap[5][5], bool rowUsed[5][6], bool colUsed[5][6], bool regionUsed[5][6], int limit)
    {
        int bestRow = -1;
        int bestCol = -1;
        int bestCount = 6;
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                if (grid[i][j] != 0)
                {
                    continue;
                }
                int candidateCount = 0;
                for (int num = 1; num <= 5; ++num)
                {
                    int regionIndex = regionMap[i][j];
                    if (!rowUsed[i][num] && !colUsed[j][num] && !regionUsed[regionIndex][num])
                    {
                        candidateCount++;
                    }
                }
                if (candidateCount == 0)
                {
                    return 0;
                }
                if (candidateCount < bestCount)
                {
                    bestCount = candidateCount;
                    bestRow = i;
                    bestCol = j;
                }
            }
        }
        if (bestRow == -1)
        {
            return 1;
        }
        int solutions = 0;
        int regionIndex = regionMap[bestRow][bestCol];
        for (int num = 1; num <= 5; ++num)
        {
            if (rowUsed[bestRow][num] || colUsed[bestCol][num] || regionUsed[regionIndex][num])
            {
                continue;
            }
            grid[bestRow][bestCol] = num;
            rowUsed[bestRow][num] = true;
            colUsed[bestCol][num] = true;
            regionUsed[regionIndex][num] = true;
            solutions += solveGrid(grid, regionMap, rowUsed, colUsed, regionUsed, limit - solutions);
            grid[bestRow][bestCol] = 0;
            rowUsed[bestRow][num] = false;
            colUsed[bestCol][num] = false;
            regionUsed[regionIndex][num] = false;
            if (solutions >= limit)
            {
                return solutions;
            }
        }
        return solutions;
    }
    int countSolutions(int limit)
    {
        int regionMap[5][5];
        if (!buildRegionMap(regionMap))
        {
            return 0;
        }
        int grid[5][5] = {};
        bool rowUsed[5][6] = {};
        bool colUsed[5][6] = {};
        bool regionUsed[5][6] = {};
        for (int i = 0; i < 5; ++i)
        {
            for (int j = 0; j < 5; ++j)
            {
                int num = board_data[i][j];
                if (num == 0)
                {
                    continue;
                }
                if (num < 1 || num > 5)
                {
                    return 0;
                }
                int regionIndex = regionMap[i][j];
                if (rowUsed[i][num] || colUsed[j][num] || regionUsed[regionIndex][num])
                {
                    return 0;
                }
                grid[i][j] = num;
                rowUsed[i][num] = true;
                colUsed[j][num] = true;
                regionUsed[regionIndex][num] = true;
            }
        }
        return solveGrid(grid, regionMap, rowUsed, colUsed, regionUsed, limit);
    }
    private:
        int counter = 0;
        std::vector<region> list{5};
};
