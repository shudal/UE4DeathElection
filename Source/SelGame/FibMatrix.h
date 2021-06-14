// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <vector>
#include <iostream>
#include "CoreMinimal.h"

/**
 * 
 */
class SELGAME_API FibMatrix
{
public:
    long long  m[2][2];
    int MOD;
    // return res
    std::vector<int> res;
    FibMatrix() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                m[i][j] = 0;
        }
    }

    void print() {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++)
                std::cout << m[i][j] << ' ';
            std::cout << std::endl;
        }

    }

    FibMatrix times(FibMatrix a, FibMatrix b) {
        FibMatrix ans;
        ans.m[0][1] = ans.m[0][0] = ans.m[1][0] = ans.m[1][1] = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                for (int k = 0; k < 2; k++)
                    ans.m[i][j] = (ans.m[i][j] + a.m[i][k] * b.m[k][j]) % MOD;
            }
        }
        return ans;
    }

    void getXthFib(long long  x, FibMatrix& ans, FibMatrix& base) {
        base.m[0][0] = base.m[1][0] = base.m[0][1] = 1;
        base.m[1][1] = 0;
        ans.m[0][0] = ans.m[1][1] = 1;
        ans.m[0][1] = ans.m[1][0] = 0;
        while (x) {
            if (x & 1) {
                ans = times(ans, base);
            }
            x >>= 1;
            base = times(base, base);
        }
    }

    // 返回最后的fib
    std::vector<int> GetFibList(int number, int mod) {
        MOD = mod;
        res.clear();
        for (int i = 1; i <= number; i++) {
            FibMatrix ans;
            FibMatrix base;
            getXthFib(i, ans, base);
            res.push_back(ans.m[0][1]);
        }
        return res;
    }
};
