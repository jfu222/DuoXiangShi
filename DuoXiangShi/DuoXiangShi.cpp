#include "DuoXiangShi.h"


CDuoXiangShi::CDuoXiangShi()
{

}


CDuoXiangShi::~CDuoXiangShi()
{

}


int CDuoXiangShi::justDoIt(std::string strSrc, std::string &strDst)
{
    //-------------------------
    std::string str2 = strSrc;
    std::string str_temp = str2;
    int ret = 0;

    //-------------------------
    ret = removeAllWhiteSpace(str_temp, str2);
    printf("步骤1： 移除字符串中所有空白字符：end: [out]=%s;\n", str2.c_str());

    //---------------------------
    bool isStrSyntaxOk = isSyntaxOk(str2);
    printf("步骤2： 检查字符串里面的语法规则是否正确：end: [out]=%s;\n", isStrSyntaxOk == true ? "Yes" : "No");

    if (isStrSyntaxOk == false)
    {
        return -1;
    }

    //---------------------------
    while(ret == 0)
    {
        str_temp = str2;
        ret = findParenthesesRightAndExponent(str_temp, str2); //将指数次方展开成乘法
        int a = 1;
    }
    
    printf("步骤3： 将指数次方展开成乘法： str2: 1111: %s\n", str2.c_str());

    //-------------------------
    ret = 0;
    int cnt = 0;
    while(1)
    {
        str_temp = str2;
        printf("步骤4： 打开相邻的两对相乘的括号：start: cnt=%d: [in]=%s;\n", cnt, str_temp.c_str());
        ret = openTwoPairsParentheses(str_temp, str2);
        printf("步骤4： 打开相邻的两对相乘的括号：end: cnt=%d; ret=%d; [out]=%s;\n", cnt, ret, str2.c_str());

        printf("步骤5： 去掉无效的括号以及单对括号：start: cnt=%d: [in]=%s;\n", cnt, str2.c_str());
        ret = deleteInvalidParentheses(str2, strDst);
        printf("步骤5： 去掉无效的括号以及单对括号：end: cnt=%d; ret=%d; [out]=%s;\n", cnt, ret, strDst.c_str());

        printf("步骤6： 合并同类项：start: cnt=%d: [in]=%s;\n", cnt, strDst.c_str());
        ret = combiningSimilarTerms(strDst, str2);
        printf("步骤6： 合并同类项：end: cnt=%d; ret=%d; [out]=%s;\n", cnt, ret, str2.c_str());

        if (isFoundAnyParentheses(str2) == false) //字符串中不存在任何小括号了
        {
            printf("步骤7： 字符串中不存在任何小括号了, cnt=%d;\n", cnt);
            break;
        }

        cnt++;
    }
    
    strDst = str2;

    printf("步骤8： 最终结果: %s;\n", strDst.c_str());

    return 0;
}


int CDuoXiangShi::removeAllWhiteSpace(std::string strSrc, std::string &strDst)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    std::string str2 = "";

    while (p2 < p1 + len)
    {
        if (*p2 != ' ') //跳过空白字符
        {
            str2 += *p2;
        }
        p2++;
    }

    strDst = str2;

    return 0;
}


bool CDuoXiangShi::isSyntaxOk(std::string strSrc)
{

    return true;
}


bool CDuoXiangShi::isFoundAnyParentheses(std::string strSrc)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;

    while (p2 < p1 + len)
    {
        if (*p2 == '(')
        {
            return true;
        }
        p2++;
    }

    return false;
}


// strSrc = "(a+5b)^3";
// strDst = "(a+5b)(a+5b)(a+5b)";
int CDuoXiangShi::findParenthesesRightAndExponent(std::string strSrc, std::string &strDst)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1 + len;
    int flag = 0;
    
    //-----------)^------------
    while(p2 > p1)
    {
        if(*p2 == '^' && *(p2 - 1) == ')')
        {
            flag = 1;
            break;
        }
        p2--;
    }

    //-------------------
    if(flag == 0)
    {
        printf("Error: %s: 1111\n", __FUNCTION__);
        return -1;
    }

    //----------(-------------
    const char * p3 = p2 - 1;
    int cnt = 0;
    flag = 0;
    
    while(p3 >= p1)
    {
        if(*p3 == ')')
        {
            cnt++;
        }
        if(*p3 == '(')
        {
            cnt--;
            if(cnt == 0)
            {
                flag = 1;
                break;
            }
        }
        p3--;
    }
    
    //-------------------
    if(flag == 0)
    {
        printf("Error: %s: 2222\n", __FUNCTION__);
        return -1;
    }

    //----------()^153---------------
    const char * p4 = p2 + 1;
    cnt = 0;
    
    while(p4 < p1 + len)
    {
        if(*p4 >= '0' && *p4 <= '9')
        {
            cnt++;
        }else
        {
            break;
        }
        p4++;
    }
    
    //-------------------
    if(cnt == 0)
    {
        printf("Error: %s: 3333\n", __FUNCTION__);
        return -1;
    }

    //-------------------------------
    std::string strExponent = strSrc.substr(p2 - p1 + 1, p4 - p2 - 1);

    int exponent = atoi(strExponent.c_str());

    std::string strBaseNumber = strSrc.substr(p3 - p1, p2 - p3);

    std::string temp1 = "";

    for(int i = 0; i < exponent; ++i)
    {
        temp1 += strBaseNumber;
    }
    
    std::string temp20 = strSrc.substr(0, p3 - p1);
    std::string temp21 = strSrc.substr(p4 - p1);

    strDst = temp20 + temp1 + temp21;

    return 0;
}


int CDuoXiangShi::openTwoPairsParentheses(std::string strSrc, std::string &strDst)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    const char * p3 = p1;
    const char * p4 = p1;
    int flag = 0;
    int cnt1 = 0;
    int cnt2 = 0;
    int ret = 0;
    
    //-----------查找(...)(...)两个连续相邻的小括号对------------
    while (p2 < p1 + len)
    {
        //------先查找左边一对小括号-----------
        cnt1 = 0;
        while (p2 < p1 + len && *p2 != ')')
        {
            if (*p2 == '(')
            {
                p3 = p2;
                cnt1++;
            }
            p2++;
        }

        if (cnt1 == 0 || *p2 != ')') //说明字符串中没有小括号，或者字符串中有未配对的小括号
        {
            printf("Error: %s: 1111\n", __FUNCTION__);
            return -1;
        }

        if (p2 + 1 < p1 + len ) //说明不是 "(...)(" 形式字符串
        {
            p2++;

            if (*p2 != '(')
            {
                continue;
            }
        }

        //----------再查找右边一对小括号-----------
        p4 = p2; // *p4 = '(';
        p2++;
        cnt1 = 0;
        while (p2 < p1 + len && *p2 != ')')
        {
            if (*p2 == '(')
            {
                cnt1++;
                break;
            }
            p2++;
        }

        if (cnt1 == 0 && *p2 == ')') //说明找到了右边一对小括号
        {
            flag = 1;
            break;
        }
    }

    //-------------------
    if (flag == 0)
    {
        printf("Error: %s: 字符串中，没有查找到(...)(...)两个连续相邻的小括号对\n", __FUNCTION__);
        return -1;
    }

    //-------------------------------
    std::string strParentheses1 = strSrc.substr(p3 - p1 + 1, p4 - p3 - 2); // strParentheses1 = "+b^2+ab-5b-2";
    std::string strParentheses2 = strSrc.substr(p4 - p1 + 1, p2 - p4 - 1);

    std::vector<std::string> vecStrs1;
    std::vector<std::string> vecStrs2;

    ret = splitPlusAndMunisItems(strParentheses1, vecStrs1);
    if (ret != 0)
    {
        printf("Error: %s: 4444\n", __FUNCTION__);
        return -1;
    }

    ret = splitPlusAndMunisItems(strParentheses2, vecStrs2);
    if (ret != 0)
    {
        printf("Error: %s: 5555\n", __FUNCTION__);
        return -1;
    }

    //------------------------------
    int len1 = vecStrs1.size();
    int len2 = vecStrs2.size();
    std::string strTemp1 = "";
    std::string strTemp2 = "";

    ret = twoPolynomialMultiplication(vecStrs1, vecStrs2, strTemp1);
    if (ret != 0)
    {
        printf("Error: %s: 6666\n", __FUNCTION__);
        return -1;
    }

    //--------------------
    std::string str1 = strSrc.substr(0, p3 - p1 + 1);
    std::string str2 = strSrc.substr(p2 - p1);

    std::string strDst3 = str1 + strTemp1 + str2;

    strDst = strDst3;

    return 0;
}


// strSrc = "2a^2-3a+7";
// vecStrs = ["2a^2", "-3a", "+7"];
int CDuoXiangShi::splitPlusAndMunisItems(std::string strSrc, std::vector<std::string> &vecStrs)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int flag = 0;
    std::string itemStr = "";

    if( *p3 == '+' ||  *p3 == '-')
    {
        p3++;
    }
    
    //-----------------------
    while(p3 <= p1 + len)
    {
        if( *p3 == '+' ||  *p3 == '-' || p3 == p1 + len)
        {
            itemStr = strSrc.substr(p2 - p1, p3 - p2);
            if(*p2 != '+' && *p2 != '-')
            {
                itemStr = "+" + itemStr;
            }
            vecStrs.push_back(itemStr);

            p2 = p3;
        }
        p3++;
    }

    //-------------------
    if(vecStrs.size() == 0)
    {
        printf("Error: %s: 1111\n", __FUNCTION__);
        return -1;
    }
    
    return 0;
}


int CDuoXiangShi::twoPolynomialMultiplication(std::vector<std::string> multiplier1, std::vector<std::string> multiplier2, std::string &strDst)
{
    int ret = 0;
    strDst = "";
    std::string strDst2 = "";

    int len1 = multiplier1.size();
    int len2 = multiplier2.size();

    for(int i = 0; i < len1; ++i)
    {
        std::string str1 = multiplier1[i];
        int momomial1[27] = {0};
        ret = splitMonomial(str1, momomial1);
        if(ret != 0)
        {
            printf("Error: %s 1111\n", __FUNCTION__);
            return -1;
        }

        //---------------------------------
        for(int j = 0; j < len2; ++j)
        {
            std::string str2 = multiplier2[j];
            
            int momomial2[27] = {0};
            ret = splitMonomial(str2, momomial2);
            if(ret != 0)
            {
                printf("Error: %s 2222\n", __FUNCTION__);
                return -1;
            }

            //---------multiplication--------------
            int result[27] = {0};
            ret = multiplication(momomial1, momomial2, result);
            if(ret != 0)
            {
                printf("Error: %s 3333\n", __FUNCTION__);
                return -1;
            }

            std::string strTemp1 = "";
            ret = convertMonomialToStr(result, strTemp1);
            if(ret != 0)
            {
                printf("Error: %s 4444\n", __FUNCTION__);
                return -1;
            }

            strDst2 += strTemp1;
        }
    }

    //------------------------
    ret = combiningSimilarTerms(strDst2, strDst);
    if (ret != 0)
    {
        printf("Error: %s 5555\n", __FUNCTION__);
//        return -1;
    }

    return 0;
}


// strSrc = "-2a^3d^7";
// momomial[] = {'a'==>3, 'b'==>0, ... 'd'==>7, ... 'z'==>0, -2};
int CDuoXiangShi::splitMonomial(std::string strSrc, int momomial[27])
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    int flag = 0;

    memset(momomial, 0, 27);
    
    //--------"-2a^3d^7" ==> momomial[26]=-2;--------------
    if(*p2 == '+' || *p2 == '-')
    {
        p2++;
    }
    
    while(p2 < p1 + len)
    {
        if(*p2 < '0' || *p2 > '9')
        {
            break;
        }
        p2++;
    }

    std::string numStr = strSrc.substr(0, p2 - p1);
    int num = atoi(numStr.c_str());

    momomial[26] = 1;

    if(num == 0)
    {
        if(*p1 == '-')
        {
            momomial[26] = -1;
        }
    }else
    {
        momomial[26] = atoi(numStr.c_str());
    }
    
    //--------"-2a^3d^7" ==> momomial['a' - 'a']=3;--------------
    char character = '\0';

    while(p2 < p1 + len)
    {
        if(*p2 < 'a' || *p2 > 'z')
        {
            printf("Error: %s: 1111\n", __FUNCTION__);
            return -1;
        }

        character = *p2;
        momomial[character - 'a'] = 1;
        p2++;

        //---------------------------
        if(*p2 == '^')
        {
            p2++;
            flag = 0;
            const char * p3 = p2;

            while(p2 < p1 + len)
            {
                if(*p2 < '0' || *p2 > '9')
                {
                    break;
                }
                p2++;
            }

            //-------------------
            if(p2 == p3)
            {
                printf("Error: %s: 2222\n", __FUNCTION__);
                return -1;
            }

            //-------------------
            numStr = strSrc.substr(p3 - p1, p2 - p3);
            num = atoi(numStr.c_str());
            momomial[character - 'a'] = num;
        }
    }

    return 0;
}


// result[0..26] = a[0..26] * b[0..26];
int CDuoXiangShi::multiplication(int a[27], int b[27], int result[27])
{
    //----------constant-------------
    result[26] = a[26] * b[26];
    
    //----------character-------------
    for(int i = 0; i < 26; ++i)
    {
        result[i] = a[i] + b[i];
    }
    
    return 0;
}


int CDuoXiangShi::convertMonomialToStr(int momomial[27], std::string &strDst)
{
    //----------constant-------------
    if(momomial[26] == 1)
    {
        strDst = "+";
    }else if (momomial[26] == -1)
    {
        strDst = "-";
    }else
    {
        strDst = std::to_string(momomial[26]);
    }

    if(strDst[0] != '+' && strDst[0] != '-')
    {
        strDst = "+" + strDst;
    }
    
    //----------character-------------
    char character = '\0';

    for(int i = 0; i < 26; ++i)
    {
        character = 'a' + i;
        if(momomial[i] != 0)
        {
            strDst += character;

            if(momomial[i] > 1)
            {
                strDst += "^" + std::to_string(momomial[i]);
            }
        }
    }
    
    if(strDst == "+" || strDst == "-")
    {
        strDst += "1";
    }

    return 0;
}


int CDuoXiangShi::combiningSimilarTerms(std::string strSrc, std::string &strDst)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int cnt1 = 0;
    int cnt2 = 0;
    int flag = 0;
    int ret = 0;

    std::string strTemp1;
    std::string strTemp2;
    std::string strTemp3;
    std::string strTemp11;
    std::string strTemp22;

    std::string str2 = strSrc;

    strDst = strSrc;

    while (p2 < p1 + len)
    {
        //---------查找非嵌套的一对小括号---------------
        cnt1 = 0;
        p3 = p2;

        while (p2 < p1 + len && *p2 != ')')
        {
            if (*p2 == '(')
            {
                p3 = p2;
                cnt1++;
            }
            p2++;
        }

        if (cnt1 == 0)
        {
            flag = 1;
            strTemp11 = str2.substr(p3 - p1, p2 - p3);
            strTemp1 = str2.substr(0, p3 - p1);
            strTemp3 = str2.substr(p2 - p1);
        }else
        {
            strTemp11 = str2.substr(p3 - p1 + 1, p2 - p3 - 1);
            strTemp1 = str2.substr(0, p3 - p1 + 1);
            strTemp3 = str2.substr(p2 - p1);

            if (*p2 == ')')
            {
                p2++;
            }
        }

        //-----------------------
        ret = combiningSimilarTermsKernel(strTemp11, strTemp22); //将不包含小括号的字符串，进行合并同类项
        if (ret == 0 && strTemp11 != strTemp22)
        {
            str2 = strTemp1 + strTemp22 + strTemp3;
            
            p1 = str2.c_str();
            len = str2.length();
            p2 = p1;
            p3 = p1;
        }

        if (flag == 1)
        {
            break;
        }
    }

    strDst = str2;

    return 0;
}


// strSrc = "+2b+2b";
// strDst = "+4b";
int CDuoXiangShi::combiningSimilarTermsKernel(std::string strSrc, std::string &strDst)
{
    int ret = 0;
    std::vector<std::string> vecStrs1;
    strDst = strSrc;

    if (strSrc == "")
    {
        return -1;
    }

    ret = splitPlusAndMunisItems(strSrc, vecStrs1);
    if(ret != 0)
    {
        printf("Error: %s: 1111\n", __FUNCTION__);
        return -1;
    }

    //------------------------
    std::vector<Momomial> vecMomomial1s;
    int len1 = vecStrs1.size();

    for(int i = 0; i < len1; ++i)
    {
        std::string str1 = vecStrs1[i];
        Momomial m;
        ret = splitMonomial(str1, m.momomial);
        if(ret != 0)
        {
            printf("Error: %s 2222\n", __FUNCTION__);
            return -1;
        }

        vecMomomial1s.push_back(m);
    }

    //----------------------------------
    std::vector<Momomial> vecResult;
    int len2 = vecMomomial1s.size();
    std::vector<Momomial>::iterator it1;
    std::vector<Momomial>::iterator it2;

    for(it1 = vecMomomial1s.begin(); it1 < vecMomomial1s.end(); ++it1)
    {
        for(it2 = it1 + 1; it2 < vecMomomial1s.end();)
        {
            Momomial m1 = *it1;
            Momomial m2 = *it2;
            bool bSimilarTerm = isSimilarTerm(m1.momomial, m2.momomial);
            if(bSimilarTerm == true)
            {
                ret = plusTwoSimilarTerms(m1.momomial, m2.momomial, it1->momomial);
                if(ret != 0)
                {
                    printf("Error: %s 3333\n", __FUNCTION__);
                    return -1;
                }
                it2 = vecMomomial1s.erase(it2);
            }else
            {
                 ++it2;
            }
        }
    }

    //----------------------
    std::string strTemp2 = "";

    int len3 = vecMomomial1s.size();
    for(int i = 0; i < len3; ++i)
    {
        Momomial m1 = vecMomomial1s[i];
        if (isZeroTerm(m1.momomial) == true) //如果是常数等于0的项，则跳过
        {
            continue;
        }

        std::string strTemp1 = "";
        ret = convertMonomialToStr(m1.momomial, strTemp1);
        if (ret != 0)
        {
            printf("Error: %s 4444\n", __FUNCTION__);
            return -1;
        }
        strTemp2 += strTemp1;
    }

    if (strTemp2 == "")
    {
        strTemp2 = "+0";
    }

    strDst = strTemp2;

    return 0;
}


bool CDuoXiangShi::isSimilarTerm(int a[27], int b[27])
{
    //----------constant-------------
//    a[26] == b[26];
    
    //----------character-------------
    for(int i = 0; i < 26; ++i)
    {
        if(a[i] != b[i])
        {
            return false;
        }
    }
    
    return true;
}


bool CDuoXiangShi::isZeroTerm(int a[27])
{
    if (a[26] == 0)
    {
        return true;
    }
    return false;
}


// result[0..26] = a[0..26] + b[0..26];
int CDuoXiangShi::plusTwoSimilarTerms(int a[27], int b[27], int result[27])
{
    //----------constant-------------
    result[26] = a[26] + b[26];
    
    //----------character-------------
    for(int i = 0; i < 26; ++i)
    {
        result[i] = a[i];
    }
    
    return 0;
}


// strSrc = "((a+b))";
// strDst = "(a+b)";
int CDuoXiangShi::deleteInvalidParentheses(std::string strSrc, std::string &strDst)
{
    const char * p1 = strSrc.c_str();
    int len = strSrc.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int cnt1 = 0;
    int cnt2 = 0;
    int flag = 0;
    int ret = 0;

    std::string strTemp1;
    std::string strTemp2;
    std::string strTemp3;
    std::string strTemp221;
    std::string strParentheses1;
    std::string strParentheses2;

    std::vector<std::string> vecStrs1;
    std::vector<std::string> vecStrs2;
    int len1;
    int len2;

    strDst = strSrc;

    //------------------------
    while(p2 < p1 + len)
    {
        if(*p2 == '(')
        {
            cnt1++;
        }
        p2++;
    }

    if(cnt1 == 0)
    {
        return -1; //说明没有括号
    }
    
    p2 = p1;
    cnt1 = 0;

    //---------(())--------------
    while(p2 < p1 + len)
    {
        cnt1 = 0;
        while(p2 < p1 + len && *p2 == '(') // ((
        {
            cnt1++;
            p2++;
        }

        if (cnt1 > 1)
        {
            p3 = p2;

            while (p2 < p1 + len && *p2 != ')')
            {
                p2++;
            }

            cnt2 = 0;
            while (p2 < p1 + len && *p2 == ')') // ))
            {
                cnt2++;
                p2++;
            }

            if(cnt1 == cnt2)
            {
                std::string strTemp1 = strSrc.substr(0, p3 - p1 - cnt1 + 1);
                std::string strTemp2 = strSrc.substr(p3 - p1, p2 - p3 - cnt2);
                std::string strTemp3 = strSrc.substr(p2 - p1 - 1);

                strDst = strTemp1 + strTemp2 + strTemp3;

                strSrc = strDst; //redo again
                p1 = strSrc.c_str();
                len = strSrc.length();
                p2 = p1;
                p3 = p1;
                break;
            }
        }
        p2++;
    }

    //-----------------
    // src="a-2(b+c^2)+3d";
    // dst="a-2b-2c^2+3d";

    strSrc = strDst; //redo again
    
    if(strSrc[0] == '(')
    {
        strSrc = "+" + strSrc;
    }

    p1 = strSrc.c_str();
    len = strSrc.length();
    p2 = p1;
    p3 = p1;

    //---------x+(xxx)+x ==> x+xxx+x--------------
redo2:
    while(p2 < p1 + len)
    {
        cnt1 = 0;
        while(p2 < p1 + len && *p2 != ')') //查找无嵌套的小括号对(...)
        {
            if (*p2 == '(')
            {
                p3 = p2;
                cnt1++;
                if (p2 - 1 >= p1 && *(p1 - 1) == ')') //像 ...)(...) 这样的字符串，没法打开单个括号对，需要跳过
                {
                    cnt1 = 0;
                }
            }
            p2++;
        }

        //---------------------------------------
        if (cnt1 > 0)
        {
            if (*p2 == ')' && ((p2 + 1 < p1 + len && (*(p2 + 1) != '(')) || p2 + 1 == p1 + len))
            {
                const char * p4 = p3;

                char sign = '+';

                while (p4 - 1 >= p1) // 提取 -5a(b+c) 中的 -5a
                {
                    p4--;
                    if (*p4 == '+' || *p4 == '-' || *p4 == '(')
                    {
                        break;
                    }
                }
                
                if (*p4 == '-')
                {
                    sign = '-';
                }

                if (*p4 == '(')
                {
                    strTemp221 = strSrc.substr(p4 - p1 + 1, p3 - p4 - 1);
                }else
                {
                    strTemp221 = strSrc.substr(p4 - p1, p3 - p4);
                }

                if(strTemp221 == "" || strTemp221 == "+" || strTemp221 == "-")
                {
                    strTemp221 = sign == '+' ? "+1" : "-1";
                }else
                {
                    if(sign == '-')
                    {
//                        strTemp221 = "-" + strTemp221;
                    }
                }

                std::string strTemp23 = "";

                //-------------------------------
                strParentheses1 = strTemp221; // strParentheses1 = "+b^2+ab-5b-2";
                strParentheses2 = strSrc.substr(p3 - p1 + 1, p2 - p3 - 1);

                ret = splitPlusAndMunisItems(strParentheses1, vecStrs1);
                if (ret != 0)
                {
                    printf("Error: %s: 4444\n", __FUNCTION__);
                    return -1;
                }

                ret = splitPlusAndMunisItems(strParentheses2, vecStrs2);
                if (ret != 0)
                {
                    printf("Error: %s: 5555\n", __FUNCTION__);
                    return -1;
                }

                //------------------------------
                len1 = vecStrs1.size();
                len2 = vecStrs2.size();

                ret = twoPolynomialMultiplication(vecStrs1, vecStrs2, strTemp23);
                if (ret != 0)
                {
                    printf("Error: %s: 6666\n", __FUNCTION__);
                    return -1;
                }

                //------------------------------------------
                if (*p4 == '(') //类似 ...((...)...
                {
                    strTemp1 = strSrc.substr(0, p4 - p1 + 1);
                }else
                {
                    strTemp1 = strSrc.substr(0, p4 - p1);
                }

                strTemp2 = strTemp23;
                strTemp3 = strSrc.substr(p2 - p1 + 1);

                strDst = strTemp1 + strTemp2 + strTemp3;

                strSrc = strDst; //redo again
                p1 = strSrc.c_str();
                len = strSrc.length();
                p2 = p1;
                p3 = p1;

                break;
            }
        }
        p2++;
    }

    return 0;
}


int CDuoXiangShi::setStrValue(std::string strSrc, int momomialValue[27], std::string &strDst)
{
    std::string strTemp1 = strSrc;
    const char * p1 = strTemp1.c_str();
    int len = strTemp1.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int cnt1 = 0;
    int cnt2 = 0;
    int ret = 0;

    while(p2 < p1 + len)
    {
        if(*p2 == '(')
        {
            p3 = p2;
        }
        if(*p2 == ')')
        {
            cnt1 = 0;
            const char * p4 = p3 + 1;
            while(p4 < p2)
            {
                if(*p4 == '+' || *p4 == '-' || (*p4 >= '0' && *p4 <= '9'))
                {
                    cnt1++;
                }
                p4++;
            }

            if(cnt1 != p2 - p3 - 1) // not like str="(-231)", but like  str="(-2ab+4b^2c)".
            {
                std::string strTemp22 = strSrc.substr(p3 - p1 + 1, p2 - p3 - 1); // strTemp22 = "-2ab+4b^2c";
                
                ret = setOneStrValue(strTemp22, momomialValue, strTemp1);
                if (ret != 0)
                {
                    printf("Error: %s 1111\n", __FUNCTION__);
                    continue;
                }

                p1 = strTemp1.c_str();
                len = strTemp1.length();
                p2 = p1;
                p3 = p1;
            }
        }
        p2++;
    }

    //------------------------
    std::string strTemp2 = strTemp1;
    ret = setOneStrValue(strTemp1, momomialValue, strTemp2);
    if (ret != 0)
    {
        printf("Error: %s 1111\n", __FUNCTION__);
//        return -1;
    }

    //------------------------
    std::string strTemp3 = "";
    ret = openTwoPairsParentheses(strTemp2, strTemp3);
    if (ret != 0)
    {
        strTemp3 = strTemp2;
//        printf("Error: %s 5555\n", __FUNCTION__);
//        return -1;
    }

    //------------------------
    strDst = strTemp3;

    return 0;
}


int CDuoXiangShi::setOneStrValue(std::string strSrc, int momomialValue[27], std::string &strDst)
{
    std::string strTemp1 = strSrc;
    const char * p1 = strTemp1.c_str();
    int len = strTemp1.length();
    const char * p2 = p1;
    const char * p3 = p1;
    int cnt1 = 0;
    int cnt2 = 0;
    int ret = 0;
    
    //-------------------
    while (p2 < p1 + len)
    {
        if (*p2 == '(' || *p2 == ')')
        {
            printf("Error: %s 1111\n", __FUNCTION__);
            return -1;
        }
        p2++;
    }

    //-------------------
    strDst = strSrc;

    cnt1 = 0;
    const char * p4 = p3 + 1;
    while (p4 < p2)
    {
        if (*p4 == '+' || *p4 == '-' || (*p4 >= '0' && *p4 <= '9'))
        {
            cnt1++;
        }
        p4++;
    }

    if (cnt1 != p2 - p3 - 1) // not like str="(-231)", but like  str="(-2ab+4b^2c)".
    {
//        std::string strTemp22 = strSrc.substr(p3 - p1, p2 - p3 ); // strTemp22 = "-2ab+4b^2c";
        std::string strTemp22 = strSrc; // strTemp22 = "-2ab+4b^2c";

        std::vector<std::string> vecStrs1;

        ret = splitPlusAndMunisItems(strTemp22, vecStrs1);
        if (ret != 0)
        {
            printf("Error: %s: 1111\n", __FUNCTION__);
            return -1;
        }

        //---------------------------
        int len1 = vecStrs1.size();
        std::string strTemp33 = "";

        for (int i = 0; i < len1; ++i)
        {
            std::string str1 = vecStrs1[i];
            int momomial[27] = { 0 };
            ret = splitMonomial(str1, momomial);
            if (ret != 0)
            {
                printf("Error: %s 2222\n", __FUNCTION__);
                return -1;
            }

            //--------------------
            int result[27] = { 0 };
            ret = setMomomialValue(momomial, momomialValue, result);
            if (ret != 0)
            {
                printf("Error: %s 3333\n", __FUNCTION__);
                return -1;
            }

            //--------------------
            std::string str2 = "";
            ret = convertMonomialToStr(result, str2);
            if (ret != 0)
            {
                printf("Error: %s 4444\n", __FUNCTION__);
                return -1;
            }

            //-------------------
            strTemp33 += str2;
        }

        //-------------------
        strDst = strTemp33;
    }

    //---------------
    std::string strTemp2 = strDst;
    ret = combiningSimilarTerms(strTemp2, strDst);
    if (ret != 0)
    {
        printf("Error: %s 5555\n", __FUNCTION__);
        return -1;
    }

    return 0;
}


int CDuoXiangShi::setMomomialValue(int src[27], int momomialValue[27], int result[27])
{
    memcpy(result, src, sizeof(int) * 27);
    
    for(int i = 0; i < 26; ++i)
    {
        if(momomialValue[i] != 0 && src[i] != 0)
        {
            for(int j = 0; j < src[i]; ++j)
            {
                result[26] *= momomialValue[i];
            }

            result[i] = 0;
        }
    }

    return 0;
}


// valuesStr="a=1,b=-2,c=3";
int CDuoXiangShi::valuesStrToMomomial(std::string valuesStr, int momomialValue[27])
{
    const char * p1 = valuesStr.c_str();
    int len = valuesStr.length();
    const char * p2 = p1;
    const char * p3 = p1;
    char character = '\0';

    memset(momomialValue, 0, sizeof(int) * 27);

    while(p2 < p1 + len)
    {
        if(*p2 >= 'a' && *p2 <= 'z')
        {
            character = *p2;
            p2++;

            //---------------------------
            if(*p2 == '=')
            {
                p2++;
                p3 = p2;

                if(*p2 == '+' || *p2 == '-')
                {
                    p2++;
                }
    
                while(p2 < p1 + len)
                {
                    if(*p2 < '0' || *p2 > '9')
                    {
                        break;
                    }
                    p2++;
                }

                std::string numStr = valuesStr.substr(p3 - p1, p2 - p3);
                int num = atoi(numStr.c_str());

                momomialValue[character - 'a'] = num;
            }else
            {
                printf("Error: %s 1111\n", __FUNCTION__);
                return -1;
            }
        }else if(*p2 == ',')
        {
            
        }else
        {
            printf("Error: %s 2222\n", __FUNCTION__);
            return -1;
        }

        p2++;
    }

    return 0;
}

