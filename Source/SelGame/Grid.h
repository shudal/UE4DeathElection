// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <ctime>
#include <random>
#include "CoreMinimal.h"

/**
 * 
 */

const int MAXN = 1e5;
const int MOD = 1e9 + 7;
typedef long long ll;

class point {
public:
    int x;
    int y;
    point(int xx, int yy) {
        this->x = xx;
        this->y = yy;
    }
};

class Grid {
    //, int end_x, int end_y, int &cnt, int** GameMap, int** vis, int MaxLenth, int MaxWidth
public:
    int lenth;
    int width;
    int TotalGrid;
    int start_x;
    int start_y;
    int callCount;
    int end_x;
    int end_y;
    int min_path;
    int cnt;
    int block_cnt;
    std::vector<int> GameMap;
    std::vector<bool> vis;

    Grid(int lenth, int width, int start_x, int start_y, int end_x, int end_y, int min_path, int block_cnt) {
        this->lenth = lenth;
        this->width = width;
        this->end_x = end_x;
        this->TotalGrid = lenth * width;
        this->end_y = end_y;
        this->start_x = start_x;
        this->start_y = start_y;
        this->min_path = min_path;
        this->block_cnt = block_cnt;
        this->vis.resize(lenth * width);
        this->cnt = 0;
        this->callCount = 0;
        fill(this->vis.begin(), this->vis.end(), false);

        this->GameMap.resize((lenth) * (width));
        fill(this->GameMap.begin(), this->GameMap.end(), 0);
    }

    int getPos(int x, int y) {
        return lenth * x + y;
    }

    /**
     * @lenth 地图长度
     * @width 地图宽度
     * @start_x 起点横坐标
     * @start_y 起点纵坐标
     * @end_x  终点横坐标
     * @end_y  终点纵坐标
     * @min_path 最少路径
     * @block_cnt 障碍物数量
     */
    void dfs(int x, int y) {
        if (callCount > 50000) {
            return;
        }
        if (x == this->end_x && y == this->end_y) {
            cnt++;
            return;
        }
        if (cnt > this->min_path) {
            return;
        }
        int dx[4] = { 0, 0, 1, -1 };
        int dy[4] = { 1, -1, 0, 0 };
        for (int i = 0; i < 4; i++) {
            int xx = x + dx[i];
            int yy = y + dy[i];
            if (this->GameMap[getPos(xx, yy)] == 0 && xx >= 0 && yy >= 0 && xx < this->lenth && yy < this->width && !this->vis[getPos(xx, yy)]) {
                this->vis[getPos(xx, yy)] = true;
                callCount += 1;
                dfs(xx, yy);
                this->vis[getPos(xx, yy)] = false;
            }
        }
    }

    static int random_unint(int minn, int maxx, int seed = 0) {
        long long res = rand();
        return res % (maxx - minn + 1) + minn;
    }

    /**
     *@ratio 获取结果的范围为[block_cnt - len*width*ratio,block_cnt]
     *
     */
    std::vector<std::vector<int> > getGameMap(double ratio) {
        bool ok = false;
        std::vector<point> blocks;
        srand(time(NULL));
        int BlockNumberLower = std::max(0, int(this->block_cnt - ratio * TotalGrid));
        int BlockNumber = random_unint(BlockNumberLower, block_cnt);
        while (BlockNumber > block_cnt || BlockNumber < BlockNumberLower) {
            BlockNumber = random_unint(BlockNumberLower, block_cnt);
        }
        while (!ok) {
            blocks.clear();
            // std::cout << "new" << std::endl;
            // std::cout << "block number : " << BlockNumber << std::endl;
            fill(this->vis.begin(), this->vis.end(), false);
            fill(this->GameMap.begin(), this->GameMap.end(), 0);
            for (int i = 0; i < BlockNumber; i++) {
                int block_x = random_unint(0, this->lenth - 1);
                int block_y = random_unint(0, this->width - 1);
                while (this->GameMap[getPos(block_x, block_y)] != 0 || (block_x == this->start_x && block_y == this->start_y) ||
                    (block_x == this->end_x && block_y == this->end_y)) {
                    block_x = random_unint(0, this->lenth - 1);
                    block_y = random_unint(0, this->width - 1);
                }
                this->GameMap[getPos(block_x, block_y)] = 1;
                blocks.push_back(point(block_x, block_y));
            }

            cnt = 0;
            this->vis[getPos(start_x, start_y)] = true;
            // << "start" << //;
            callCount = 0;
            dfs(this->start_x, this->start_y);
            if (cnt >= this->min_path) {
                // << "cnt = " << cnt << //;
                ok = true;
                break;
            }
        }
        // prepare return valuess
        std::vector<std::vector<int> > res;
        res.clear();
        for (int i = 0; i < this->lenth; i++) {
            res.push_back(std::vector<int>());
            for (int j = 0; j < this->width; j++) {
                res[i].push_back(this->GameMap[getPos(i, j)]);
            }
        } 
        // << "start" << //;

        dfs(start_x, start_y);
        // << (cnt == 0 ? "false" : "ok") << //;
        return res;
    }
};
