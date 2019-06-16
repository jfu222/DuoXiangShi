#include "DuoXiangShiZuHe.h"


CDuoXiangShiZuHe::CDuoXiangShiZuHe()
{

}


CDuoXiangShiZuHe::~CDuoXiangShiZuHe()
{

}


// strSrc26EnglishLetters = "abc"; 单项式由哪些英文字母组成
// exponential = 3; 指数的最大值
// vecStrsDst = ["(a+b+c)^3", "a^3+b^3+c^3", "abc", "ab^2+ac^2+bc^2", "(a+b+c)(a^2+b^2+c^2)", "(a+b+c)(ab+ac+bc)"];
int CDuoXiangShiZuHe::createCombinePolynomial(std::string strSrc26EnglishLetters, int exponential, std::vector<std::string> &vecStrsDst)
{
    const char * p1 = strSrc26EnglishLetters.c_str();
    int len = strSrc26EnglishLetters.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int cnt1 = 0;
    int cnt2 = 0;
    int flag = 0;
    int ret = 0;

     int momomial[27] = {0};
     std::vector<char> vecLetters;
     std::string str2 = "";

    for(int i = 0; i < len; ++i)
    {
        if(p1[i] >= 'a' && p1[i] <= 'z') //26个英文字母
        {
            vecLetters.push_back(p1[i]);
        }else
        {
            printf("%s: Error: 1111\n", __FUNCTION__);
            return -1;
        }
    }

    //---------------------------
    int vecLettersLen = vecLetters.size();
    int baseN = exponential + 1;
    std::vector<int> maxVecCnt; //计数器
    std::vector<int> maxVecNum;
    std::vector<int> summandVec; //被加数

     for(int i = 1; i <= exponential; ++i)
    {
        maxVecCnt.push_back(0);
        maxVecNum.push_back(baseN - 1);
        summandVec.push_back(0);
    }
    
    maxVecCnt[exponential - 1] = 1; //计数器初始值为一
    summandVec[exponential - 1] = 1; //被加数个位置1，每次加一

    std::vector< std::vector<std::string> > vecStrs;
    std::map<Momomial2, int> hash;
    Momomial2 mom2;

    while(isTwoVecNumberLe(maxVecCnt, maxVecNum) == true) //相当于 i <= len;
    {
//        printf("%s: maxVecCnt = [%d, %d, %d, %d];\n", __FUNCTION__, maxVecCnt[0], maxVecCnt[1], maxVecCnt[2], maxVecCnt[3]);
        
        mom2.reset();
        for(int i = 0; i < exponential; ++i)
        {
            if(maxVecCnt[i] > 0 && maxVecCnt[i] <= vecLettersLen)
            {
                mom2.momomial[vecLetters[maxVecCnt[i] - 1] - 'a'] += 1; //如果按照0-'null', 1-a, 2-b, 3-c, 4-d,...来对应，则maxVecCnt = [1,3,2,3]; 表示 [a, c, b, c];
                mom2.exponentialSum += 1;
            }
        }

        //----------------------
        for (int i = 0; i < 25; ++i)
        {
            if (mom2.momomial[i] != 0)
            {
                mom2.exponentialIndexs.push_back(mom2.momomial[i]);
            }
        }

        std::sort(mom2.exponentialIndexs.begin(), mom2.exponentialIndexs.end(), std::less<int>()); //升序排列

        //--------------------
        hash[mom2] += 1;
        cnt1++;
        
        ret = vecPlusBaseN(maxVecCnt, baseN, summandVec, maxVecCnt); //相当于 ++i;
        if(ret != 0)
        {
            break;
        }
    }

    //----------------------
    CDuoXiangShi dxs;
    cnt1 = 0;
    std::map<std::string, std::string> hash2;
    std::map<std::string, int> hash3;
    std::map<int, int> hash4;

    std::map<Momomial2, int>::iterator it;
    for(it = hash.begin(); it != hash.end(); it++)
    {
        Momomial2 mom2_temp = it->first;
        std::string str2 = "";

        mom2_temp.momomial[26] = 1;
        ret = dxs.convertMonomialToStr(mom2_temp.momomial, str2);

        std::string strIndexs = "";
        for(int i = 0; i < mom2_temp.exponentialIndexs.size(); ++i)
        {
            strIndexs += "+" + std::to_string(mom2_temp.exponentialIndexs[i]);
        }

        hash2[strIndexs] += str2;
        hash3[strIndexs] = mom2_temp.exponentialSum;
        hash4[mom2_temp.exponentialSum] = 0;

        printf("%s: %d/%d: hash[%s]=%d; exponentialSum=%d; strIndexs=%s;\n", __FUNCTION__, cnt1, hash.size(), str2.c_str(), it->second, mom2_temp.exponentialSum, strIndexs.c_str());
        cnt1++;
    }

    //-------------------------
    cnt1 = 0;
    std::vector< std::vector<std::string> > vecStrsTemp; // vecStrsTemp = [["2","+a^2+b^2+c^2","+ab+ac+bc"], ["1","+a+b+c"]];
    std::map<std::string, std::string>::iterator it2;
    std::map<int, int>::iterator it4;
    
    for(it4 = hash4.begin(); it4 != hash4.end(); it4++)
    {
        std::vector<std::string> temp1;
        int exponentialSum = it4->first;

        temp1.push_back(std::to_string(exponentialSum));

        vecStrsTemp.push_back(temp1);
    }

    int lenTemp = vecStrsTemp.size();

    for(it2 = hash2.begin(); it2 != hash2.end(); it2++)
    {
        std::string key = it2->first;
        
        for(int i = 0; i < lenTemp; ++i)
        {
            if(std::to_string(hash3[key]) == vecStrsTemp[i][0])
            {
                vecStrsTemp[i].push_back(hash2[key]); // vecStrsTemp = [["2","+a^2+b^2+c^2","+ab+ac+bc"], ["1","+a+b+c"]];
            }
        }

        printf("%s: %d/%d: hash2[%s]=%s; exponentialSum=%d;\n", __FUNCTION__, cnt1, hash2.size(), it2->first.c_str(), it2->second.c_str(), hash3[it2->first]);
        cnt1++;
    }
    
    //--------------------
    std::vector<int> maxVecCnt2; //计数器
    std::vector<int> maxVecNum2;
    std::vector<int> baseN2; //非等进制数组的加法（比如：个位为5进制，十位为3进制，...）
    std::vector<int> summandVec2; //被加数

    for(int i = 0; i < lenTemp; ++i)
    {
        //对于 vecStrsTemp[i][0]="2"; vecStrsTemp[i][1]表示"+a^2+b^2+c^2"; vecStrsTemp[i][2]表示"+ab+ac+bc"; 进制数为: 4 / 2 * 2 = 4; 数值范围[1,4]
        //其中[1,2]表示"(+a^2+b^2+c^2)"和"(+a^2+b^2+c^2)^2"; [3,4]表示"(+ab+ac+bc)"和"(+ab+ac+bc)^2";
        int base_N2 = (exponential / atoi(vecStrsTemp[i][0].c_str())) * (vecStrsTemp[i].size() - 1) + 1;

        maxVecCnt2.push_back(0);
        baseN2.push_back(base_N2);
        maxVecNum2.push_back(base_N2 - 1);
        summandVec2.push_back(0);
    }
    
    maxVecCnt2[lenTemp - 1] = 1; //计数器初始值为一
    summandVec2[lenTemp - 1] = 1; //被加数个位置1，每次加一

    //------------------------
    std::vector< std::vector<std::string> > vecStrs3;
    std::map<Momomia3, int> hash33;
    Momomia3 mom3;

    std::vector< std::vector<int> > mom3Temp;
    for(int i = 0; i < lenTemp; ++i)
    {
        std::vector<int> temp;

        for(int j = 0; j < vecStrsTemp[i].size() - 1; ++j)
        {
            temp.push_back(0);
        }
        mom3Temp.push_back(temp);
    }

    mom3.init(mom3Temp); //初始化

    cnt1 = 0;
    while(isTwoVecNumberLe(maxVecCnt2, maxVecNum2) == true) //相当于 i <= len;
    {
        printf("%s: maxVecCnt2 = [%d, %d, %d, %d];\n", __FUNCTION__, maxVecCnt2[0], maxVecCnt2[1], maxVecCnt2[2], maxVecCnt2[3]);
        
        if(maxVecCnt2[0] == 4 &&  maxVecCnt2[1] == 4 &&  maxVecCnt2[2] == 3 &&  maxVecCnt2[3] == 5)
        {
            int a = 1;
        }

        mom3.setZero(); //重置为0

        for(int i = 0; i < lenTemp; ++i)
        {
            if(maxVecCnt2[i] > 0 && maxVecCnt2[i] <= baseN2[i])
            {
                int baseN23 = (baseN2[i] - 1) / (vecStrsTemp[i].size() - 1);
                int index = (maxVecCnt2[i] - 1) / baseN23;
                int exponential = maxVecCnt2[i] - baseN23 * index;
                mom3.momomial[i][index] += exponential; //maxVecCnt2 = [1,2,1] 表示 ['a+b+c','ab+ac+bc'c, 'a^3+b^3+c^3']; maxVecCnt2 = [1,1,1] 表示 ['a+b+c','a^2+b^2+c^2'c, 'a^3+b^3+c^3'];
                mom3.exponentialSum += exponential * atoi(vecStrsTemp[i][0].c_str());
            }
        }

        //--------------------
        hash33[mom3] += 1;
        cnt1++;
        
        ret = vecPlusNonBaseN(maxVecCnt2, baseN2, summandVec2, maxVecCnt2); //相当于 ++i;
        if(ret != 0)
        {
            break;
        }
    }

    //-----------------------
    std::map<Momomia3, int>::iterator it33;
    std::vector<std::string> vecStrsDstTemp;
    cnt1 = 0;

    for(it33 = hash33.begin(); it33 != hash33.end(); it33++)
    {
        Momomia3 mom3_temp = it33->first;

        std::string strTemp = "";

        for(int i = 0; i < mom3_temp.momomial.size(); ++i)
        {
            for(int j = 0; j < mom3_temp.momomial[i].size(); ++j)
            {
                if(mom3_temp.momomial[i][j] > 0)
                {
                    if(mom3_temp.momomial[i][j] == 1)
                    {
                        strTemp += "(" + vecStrsTemp[i][j + 1] + ")";
                    }else if(mom3_temp.momomial[i][j] > 1)
                    {
                        strTemp += "(" + vecStrsTemp[i][j + 1] + ")^" + std::to_string(mom3_temp.momomial[i][j]);
                    }
                }
            }
        }

        if(mom3_temp.exponentialSum == exponential) //将两个多项式的指数和等于总指数的多项式配对，例如：(a+b+c)(a^2+b^2+c^2)是一对，(a+b+c)(ab+ac+bc)也是一对
        {
            vecStrsDstTemp.push_back(strTemp);
        }

        printf("%s: %d/%d: hash33[]: %s; exponentialSum=%d;\n", __FUNCTION__, cnt1, hash33.size(), strTemp.c_str(), mom3_temp.exponentialSum);
        cnt1++;
    }

    //--------------------
    vecStrsDst = vecStrsDstTemp;
    cnt1 = 0;

    for(int i = 0; i < vecStrsDst.size(); ++i)
    {
        printf("%s: %d/%d: vecStrsDst[]: %s;\n", __FUNCTION__, cnt1, vecStrsDst.size(), vecStrsDst[i].c_str());
        cnt1++;
    }

    //----------------------
    ret = loopPolynomialCoefficientsValues(vecStrsDstTemp, 10);

    return 0;
}


// srcVec = [1,3,2,3];
// baseN =4;
// summandVec = [0,0,0,2]; //被加数
// dstVec = [1,3,3,1];
int CDuoXiangShiZuHe::vecPlusBaseN(std::vector<int> srcVec, int baseN, std::vector<int> summandVec, std::vector<int> &dstVec)
{
    if(srcVec.size() != summandVec.size())
    {
        return -1;
    }

    dstVec = srcVec;
    int len = srcVec.size();
    int carryNum = 0; //进位数

    for(int i = len - 1; i >= 0; --i) //从个位开始进行加法
    {
        if(srcVec[i] < 0 ||srcVec[i] >= baseN || summandVec[i] < 0 || summandVec[i] >= baseN)
        {
            printf("%s: Error:1111\n", __FUNCTION__);
            return -1;
        }

        int sum = srcVec[i] + summandVec[i] + carryNum;
        dstVec[i] = sum % baseN;
        carryNum = sum / baseN; //进位
    }

    if(carryNum > 0)
    {
//        printf("%s: Error: plus overflow\n", __FUNCTION__); //加法最高位溢出了
        return -1;
    }

    return 0;
}


int CDuoXiangShiZuHe::isTwoVecNumberEqual(std::vector<int> a, std::vector<int> b)
{
    if(a.size() != b.size())
    {
        return false;
    }

    int len = a.size();

    for(int i = 0; i < len; ++i)
    {
        if(a[i] != b[i])
        {
            return false;
        }
    }
    
    return true;
}


int CDuoXiangShiZuHe::isTwoVecNumberLe(std::vector<int> a, std::vector<int> b)
{
    if(a.size() != b.size())
    {
//        return false;
    }

    int len = a.size();

    for(int i = 0; i < len; ++i)
    {
        if(a[i] > b[i])
        {
            return false;
        }
    }
    
    return true;
}


//--------------------------------------
int CDuoXiangShiZuHe::vecPlusNonBaseN(std::vector<int> srcVec, std::vector<int> baseNVec, std::vector<int> summandVec, std::vector<int> &dstVec)
{
    if(srcVec.size() != summandVec.size() || srcVec.size() != baseNVec.size())
    {
        return -1; //数组的第一维长度必须相等
    }

    //-------------------------------------
    dstVec = srcVec;
    int len = srcVec.size();
    int carryNum = 0; //进位数

    for(int i = len - 1; i >= 0; --i) //从个位开始进行加法
    {
        int sum = srcVec[i] + summandVec[i] + carryNum;
        dstVec[i] = sum % baseNVec[i];
        carryNum = sum / baseNVec[i]; //进位
    }

    if(carryNum > 0)
    {
//        printf("%s: Error: plus overflow\n", __FUNCTION__); //加法最高位溢出了
        return -1;
    }

    return 0;
}


//------------------------------
int CDuoXiangShiZuHe::loopPolynomialCoefficientsValues(std::vector<std::string> strSrcVecs, int loopValueMax)
{
    int len = strSrcVecs.size();
    int ret = 0;
    int cnt = 0;
    std::string str = "";
    std::string str2 = "";
    std::string str3 = "";
    
    int momomialValue[27] = {0};
    
    for(int i = 0; i < 26; ++i)
    {
        momomialValue[i] = 1;
    }

    //----------------------
    CDuoXiangShi dxs;
    
    std::vector<std::string> strSrcVecs2;
    std::vector<int> valueVecs2;
    
    for(int i = 0; i < len; ++i)
    {
        //-----------------------
        str = strSrcVecs[i];
        str2 = str;
        printf("%s: str: %s\n", __FUNCTION__, str.c_str());

        ret = dxs.justDoIt(str, str2); //打开括号，以便加快速度

        printf("%s: str2: %s\n", __FUNCTION__, str2.c_str());

        strSrcVecs2.push_back(str2);
        
        //------------------------------------------------
        ret = dxs.setStrValue(str2, momomialValue, str3);

        printf("str3: 4444: %s\n", str3.c_str());

        int value = atoi(str3.c_str());
        valueVecs2.push_back(value);
    }

    //---------------------------
    int baseN = loopValueMax + 1;
    std::vector<int> maxVecCnt; //计数器
    std::vector<int> maxVecNum;
    std::vector<int> summandVec; //被加数

    for(int i = 0; i < len; ++i)
    {
        maxVecCnt.push_back(0);
        maxVecNum.push_back(baseN - 1);
        summandVec.push_back(0);
    }
    
    maxVecCnt[len - 1] = 1; //计数器初始值为一
    summandVec[len - 1] = 1; //被加数个位置1，每次加一
    
    //--------------------------
    char out[] = "./out_result.log";
    FILE * fp = fopen(out, "w");

    while(isTwoVecNumberLe(maxVecCnt, maxVecNum) == true) //相当于 i <= len;
    {
        printf("%s: maxVecCnt = [", __FUNCTION__);
        for (int i = 0; i < len; ++i)
        {
            printf("%d, ", maxVecCnt[i]);
        }
        printf("];\n", __FUNCTION__);
        
        //----------------
        str = "";
        int valueTotal = 0;
        int flag = 0;
        for(int i = 0; i < len; ++i)
        {
            int coefficients = maxVecCnt[i] - loopValueMax / 2;
            flag = 0;
            if(maxVecCnt[i] > 0 && maxVecCnt[i] <= loopValueMax && coefficients != 0)
            {
//                str += std::to_string(coefficients) + strSrcVecs[i]; //str2 = "3(+a+b+c)(ab+ac+bc)";

                if(coefficients >= 0)
                {
                    str += "+" + std::to_string(coefficients) + "(" + strSrcVecs2[i] + ")"; //str2 = "3(+a+b+c)(ab+ac+bc)";
                }else
                {
                    str += std::to_string(coefficients) + "(" + strSrcVecs2[i] + ")"; //str2 = "3(+a+b+c)(ab+ac+bc)";
                }

                valueTotal += coefficients * valueVecs2[i];
                flag = 1;
            }
        }

        //--------------------
        if(valueTotal == 0 && flag == 1)
        {
            //-----------------------
            str2 = str;
            printf("%s: str: %s\n", __FUNCTION__, str.c_str());

            ret = dxs.justDoIt(str, str2);

            printf("%s: str2: %s\n", __FUNCTION__, str2.c_str());

            //-------------
            if(str2.length() < 50)
            {
                std::string strTemp = "-----------cnt=" + std::to_string(cnt) + ";\n";
                std::string strTemp2 = "";
                for(int i = 0; i < len; ++i)
                {
                    int coefficients = maxVecCnt[i] - loopValueMax / 2;
                    int coefficients2 = 0;
                    if(maxVecCnt[i] > 0 && coefficients != 0)
                    {
                        if(coefficients > 0)
                        {
                            strTemp2 += "+" + std::to_string(coefficients) + strSrcVecs[i]; //str2 = "3(+a+b+c)(ab+ac+bc)";
                        }else
                        {
                            strTemp2 += std::to_string(coefficients) + strSrcVecs[i]; //str2 = "3(+a+b+c)(ab+ac+bc)";
                        }

                        coefficients2 = coefficients;
                    }
                    strTemp += "[" + std::to_string(i) + "]=" + std::to_string(coefficients2) + "; ";
                }

                strTemp += "\n" + strTemp2 + "\n" + str2 + "\n";

                fwrite(strTemp.c_str(), strTemp.length(), 1, fp);
            }
        }
        
        //-------------
        cnt++;

        ret = vecPlusBaseN(maxVecCnt, baseN, summandVec, maxVecCnt); //相当于 ++i;
        if(ret != 0)
        {
            break;
        }
    }
    
    fclose(fp);

    return 0;
}

