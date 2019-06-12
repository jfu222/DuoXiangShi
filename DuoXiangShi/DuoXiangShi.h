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
    int removeAllWhiteSpace(std::string strSrc, std::string &strDst); //�Ƴ��ַ��������пհ��ַ�
    bool isSyntaxOk(std::string strSrc); //����ַ���������﷨�����Ƿ���ȷ
    bool isFoundAnyParentheses(std::string strSrc); //�ַ������Ƿ�������һ��С����
    int findParenthesesRightAndExponent(std::string strSrc, std::string &strDst); //������С���ź�ָ������
    int openTwoPairsParentheses(std::string strSrc, std::string &strDst); //��������˵�С����
    int splitPlusAndMunisItems(std::string strSrc, std::vector<std::string> &vecStrs); //�����мӼ��ŵ��ַ�����ֳ�����
    int twoPolynomialMultiplication(std::vector<std::string> multiplier1, std::vector<std::string> multiplier2, std::string &strDst); //��������ʽ���
    int splitMonomial(std::string strSrc, int momomial[27]); //��ֵ���ʽ
    int multiplication(int a[27], int b[27], int result[27]); //�����������
    int convertMonomialToStr(int momomial[27], std::string &strDst); //����������ת�����ַ���
    int combiningSimilarTerms(std::string strSrc, std::string &strDst); //������С���ŵ��ַ��������кϲ�ͬ����
    int combiningSimilarTermsKernel(std::string strSrc, std::string &strDst); //��������С���ŵ��ַ��������кϲ�ͬ����
    bool isSimilarTerm(int a[27], int b[27]); //�Ƿ���ͬ����
    bool isZeroTerm(int a[27]); //�Ƿ��ǳ�������0����
    int plusTwoSimilarTerms(int a[27], int b[27], int result[27]); //�ϲ�����ͬ����
    int deleteInvalidParentheses(std::string strSrc, std::string &strDst); //ɾ����������Ч��С����
    int setStrValue(std::string strSrc, int momomialValue[27], std::string &strDst); //�����ַ�����ĸȡֵ��a=2,b=5,c=3
    int setOneStrValue(std::string strSrc, int momomialValue[27], std::string &strDst); //�����ַ�����ĸȡֵ��a=2,b=5,c=3
    int setMomomialValue(int src[27], int momomialValue[27], int result[27]); //������ĸȡֵ��a=2,b=5,c=3
    int valuesStrToMomomial(std::string valuesStr, int momomialValue[27]); //�� valuesStr="a=1,b=-2,c=3" ת���� momomialValue[27];
};

