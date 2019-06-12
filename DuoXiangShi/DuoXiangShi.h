#pragma once

#include <string>
#include <vector>


typedef struct _Momomial_
{
    int momomial[27];

public:
    _Momomial_()
    {
        memset(momomial, 0, sizeof(int) * sizeof(momomial) / sizeof(momomial[0]));
    }
    ~_Momomial_()
    {

    }
}Momomial;


//------------------------------
class CDuoXiangShi
{
public:

public:
    CDuoXiangShi();
    ~CDuoXiangShi();

    int justDoIt(std::string strSrc, std::string &strDst);
    int removeAllWhiteSpace(std::string strSrc, std::string &strDst); //移除字符串中所有空白字符
    bool isSyntaxOk(std::string strSrc); //检查字符串里面的语法规则是否正确
    bool isFoundAnyParentheses(std::string strSrc); //字符串中是否含有至少一个小括号
    int findParenthesesRightAndExponent(std::string strSrc, std::string &strDst); //查找右小括号和指数符号
    int openTwoPairsParentheses(std::string strSrc, std::string &strDst); //打开两对相乘的小括号
    int splitPlusAndMunisItems(std::string strSrc, std::vector<std::string> &vecStrs); //将含有加减号的字符串拆分成数组
    int twoPolynomialMultiplication(std::vector<std::string> multiplier1, std::vector<std::string> multiplier2, std::string &strDst); //两个多项式相乘
    int splitMonomial(std::string strSrc, int momomial[27]); //拆分单项式
    int multiplication(int a[27], int b[27], int result[27]); //两个单项相乘
    int convertMonomialToStr(int momomial[27], std::string &strDst); //将单项数组转换成字符串
    int combiningSimilarTerms(std::string strSrc, std::string &strDst); //将包含小括号的字符串，进行合并同类项
    int combiningSimilarTermsKernel(std::string strSrc, std::string &strDst); //将不包含小括号的字符串，进行合并同类项
    bool isSimilarTerm(int a[27], int b[27]); //是否是同类项
    bool isZeroTerm(int a[27]); //是否是常数等于0的项
    int plusTwoSimilarTerms(int a[27], int b[27], int result[27]); //合并两个同类项
    int deleteInvalidParentheses(std::string strSrc, std::string &strDst); //删除连续的无效的小括号
    int setStrValue(std::string strSrc, int momomialValue[27], std::string &strDst); //设置字符串字母取值，a=2,b=5,c=3
    int setOneStrValue(std::string strSrc, int momomialValue[27], std::string &strDst); //设置字符串字母取值，a=2,b=5,c=3
    int setMomomialValue(int src[27], int momomialValue[27], int result[27]); //设置字母取值，a=2,b=5,c=3
    int valuesStrToMomomial(std::string valuesStr, int momomialValue[27]); //将 valuesStr="a=1,b=-2,c=3" 转换成 momomialValue[27];
};

