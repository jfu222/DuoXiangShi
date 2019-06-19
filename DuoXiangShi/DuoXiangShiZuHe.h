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
    int exponentialSum; //ָ����
    std::vector<int> exponentialIndexs; //ָ�����飬����a^3bc^2, ��exponentialIndex=[3,1,2];

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


//-----------��Ҫ����ÿ��λ�����磺��λΪ5���ƣ�ʮλΪ3���ƣ�...���ǵȽ���(2ά����)�ӷ�--------------------------
typedef struct _Momomia3_
{
    std::vector< std::vector<int> > momomial;
    int exponentialSum; //ָ����
    std::vector<int> exponentialIndexs; //ָ�����飬����a^3bc^2, ��exponentialIndex=[3,1,2];

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
            assert(0); //����2ά����ĵ�һά���ȱ������
        }

        int len = this->momomial.size();
        for(int i = 0; i < len; ++i)
        {
            if(this->momomial[i].size() != b.momomial[i].size())
            {
                assert(0); //����2ά����ĵڶ�ά����Ҳ�������
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
    std::string strPolynomial; //�Զ���ʽΪ����
    int exponential; //����ʽ��ָ����(a+b+c)^7�е�7
}PolynomialExponential;


//-------------------------------------
class CDuoXiangShiZuHe
{
public:


public:
    CDuoXiangShiZuHe();
    ~CDuoXiangShiZuHe();

    int createCombinePolynomial(std::string strSrc26EnglishLetters, int exponential, std::vector<std::string> &vecStrsDst); //�����������ʽ��������ص����
    int vecPlusBaseN(std::vector<int> srcVec, int baseN, std::vector<int> summandVec, std::vector<int> &dstVec); //n��������ļӷ�����Ҫ����������forѭ��
    int isTwoVecNumberEqual(std::vector<int> a, std::vector<int> b); //����n�������Ƿ����
    int isTwoVecNumberLe(std::vector<int> a, std::vector<int> b); //����n�������Ƿ�С�ڵ���

    int vecPlusNonBaseN(std::vector<int> srcVec, std::vector<int> baseNVec, std::vector<int> summandVec, std::vector<int> &dstVec); //�ǵȽ�������ļӷ������磺��λΪ5���ƣ�ʮλΪ3���ƣ�...������Ҫ����������forѭ��

    int loopPolynomialCoefficientsValues(std::vector<std::string> strSrcVecs, int loopValueMax, std::vector< std::vector<PolynomialExponential> > vecPolynomialExponentials); //ѭ�����Զ������ʽ�������ֵΪ0
};

