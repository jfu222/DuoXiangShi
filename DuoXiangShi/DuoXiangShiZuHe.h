#pragma once

#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <assert.h>
#include "DuoXiangShi.h"


//-------------------------------------
typedef struct _Momomial2_
{
    int momomial[27];
    int exponentialSum; //指数和
    std::vector<int> exponentialIndexs; //指数数组，比如a^3bc^2, 则exponentialIndex=[3,1,2];

public:
    _Momomial2_()
    {
        reset();
    }
    ~_Momomial2_()
    {

    }
    int reset()
    {
        memset(momomial, 0, sizeof(int) * sizeof(momomial) / sizeof(momomial[0]));
        exponentialSum = 0;
        exponentialIndexs.clear();
        return 0;
    }

    bool operator < (const _Momomial2_ &b) const
    {
        if(this->exponentialSum < b.exponentialSum)
        {
            return true;
        }else if(this->exponentialSum > b.exponentialSum)
        {
            return false;
        }else
        {
            std::vector<int> temp1;
            std::vector<int> temp2;

            for(int i = 0; i < 25; ++i)
            {
                if(this->momomial[i] != 0)
                {
                    temp1.push_back(this->momomial[i]);
                }
                if(b.momomial[i] != 0)
                {
                    temp2.push_back(b.momomial[i]);
                }
            }

            //-----------------
            int len1 = temp1.size();
            int len2 = temp2.size();

            if(len1 == len2)
            {
                for(int i = 0; i < len1; ++i)
                {
                    if(temp1[i] < temp2[i])
                    {
                        return true;
                    }else if(temp1[i] > temp2[i])
                    {
                        return false;
                    }
                }

                //---------------------------------
                for(int i = 0; i < 25; ++i) // [1,1,0,0,...] cmp [1,0,1,0,...]
                {
                    if(this->momomial[i] < b.momomial[i])
                    {
                         return false;
                    }else if(this->momomial[i] > b.momomial[i])
                    {
                        return true;
                    }
                }
            }else if(len1 < len2)
            {
                return true;
            }
        }

        return false;
    }
}Momomial2;


//-----------主要用于每个位（比如：个位为5进制，十位为3进制，...）非等进制(2维数组)加法--------------------------
typedef struct _Momomia3_
{
    std::vector< std::vector<int> > momomial;
    int exponentialSum; //指数和
    std::vector<int> exponentialIndexs; //指数数组，比如a^3bc^2, 则exponentialIndex=[3,1,2];

public:
    _Momomia3_()
    {
        reset();
    }

    ~_Momomia3_()
    {

    }

    int reset()
    {
        momomial.clear();
        exponentialSum = 0;
        exponentialIndexs.clear();
        return 0;
    }

    int setZero()
    {
        for(int i = 0; i < momomial.size(); ++i)
        {
            for(int j = 0; j < momomial[i].size(); ++j)
            {
                momomial[i][j] = 0;
            }
        }

        exponentialSum = 0;
        exponentialIndexs.clear();
        return 0;
    }

    int init(std::vector< std::vector<int> > srcVecs)
    {
        momomial = srcVecs;
        return 0;
    }

    bool operator < (const _Momomia3_ &b) const
    {
        if(this->momomial.size() != b.momomial.size())
        {
            assert(0); //两个2维数组的第一维长度必须相等
        }

        int len = this->momomial.size();
        for(int i = 0; i < len; ++i)
        {
            if(this->momomial[i].size() != b.momomial[i].size())
            {
                assert(0); //两个2维数组的第二维长度也必须相等
            }
        }

        //------------------------------------------
        if(this->exponentialSum < b.exponentialSum)
        {
            return true;
        }else if(this->exponentialSum > b.exponentialSum)
        {
            return false;
        }else
        {
            for(int i = 0; i < len; ++i)
            {
                for(int j = 0; j < this->momomial[i].size(); ++j)
                {
                    if(this->momomial[i][j] < b.momomial[i][j])
                    {
                        return true;
                    }else if(this->momomial[i][j] > b.momomial[i][j])
                    {
                        return false;
                    }
                }
            }
        }

        return false;
    }
}Momomia3;


typedef struct _PolynomialExponential_
{
    std::string strPolynomial; //以多项式为底数
    int exponential; //多项式的指数，(a+b+c)^7中的7
}PolynomialExponential;


//-------------------------------------
class CDuoXiangShiZuHe
{
public:


public:
    CDuoXiangShiZuHe();
    ~CDuoXiangShiZuHe();

    int createCombinePolynomial(std::string strSrc26EnglishLetters, int exponential, std::vector<std::string> &vecStrsDst); //创建多个多项式的线性相关的组合
    int vecPlusBaseN(std::vector<int> srcVec, int baseN, std::vector<int> summandVec, std::vector<int> &dstVec); //n进制数组的加法，主要用于替代多层for循环
    int isTwoVecNumberEqual(std::vector<int> a, std::vector<int> b); //两个n进制数是否相等
    int isTwoVecNumberLe(std::vector<int> a, std::vector<int> b); //两个n进制数是否小于等于

    int vecPlusNonBaseN(std::vector<int> srcVec, std::vector<int> baseNVec, std::vector<int> summandVec, std::vector<int> &dstVec); //非等进制数组的加法（比如：个位为5进制，十位为3进制，...），主要用于替代多层for循环

    int loopPolynomialCoefficientsValues(std::vector<std::string> strSrcVecs, int loopValueMax, std::vector< std::vector<PolynomialExponential> > vecPolynomialExponentials); //循环尝试多个多项式线性组合值为0
};

