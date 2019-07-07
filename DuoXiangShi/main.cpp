// DuoXiangShi.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "DuoXiangShi.h"
#include "DuoXiangShiZuHe.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int print_help(int argc, char *argv[])
{
    printf("=======过客 && 386520874@qq.com && 2019.06.12=========\n");
    printf("Usage:\n");
    printf("%s <isInputFile|1> <in|math_formula.txt> <outDir> [valuesStr|\"a=1,b=1,c=1,d=1,e=1\"]\n", argv[0]);
    printf("For Example:\n");
    printf("%s 1 ./math_formula.txt ./ \"a=1,b=1,c=1,d=1,e=1\"\n", argv[0]); // 1 D:\work\git\DuoXiangShi\x64\Debug\math_formula.txt ./ "a=1,b=2,c=3,d=1,e=1"
    printf("%s 0 \"(a+b+c)^3\" ./ \"a=1,b=1,c=1,d=1,e=1\"\n", argv[0]); // 0 "(a+b+c)^3" ./ "a=1,b=2,c=3,d=1,e=1"

    return 0;
}


int main1(int argc, char *argv[])
{
    int ret = 0;
    CDuoXiangShiZuHe dxszh;
    std::string strSrc26EnglishLetters = "abcd"; // "abcd";
    int exponential = strSrc26EnglishLetters.length(); //4;
    std::vector<std::string> vecStrsDst;
    dxszh.createCombinePolynomial(strSrc26EnglishLetters, exponential, vecStrsDst);

    return 0;
}


int main2(int argc, char *argv[])
{
    int ret = 0;
    CDuoXiangShiZuHe dxszh;

    std::vector<std::string> vecStrSrcs;
    std::string str = "";
    int baseNum = 4;

    str = "+a^3+b^3+c^3";
    vecStrSrcs.push_back(str);
    
    str = "+ab^2+ac^2+bc^2+a^2b+a^2c+b^2c";
    vecStrSrcs.push_back(str);
    
    str = "+abc";
    vecStrSrcs.push_back(str);
    
    str = "+a^3+ab^2+ac^2+a^2b+b^3+bc^2+a^2c+b^2c+c^3";
    vecStrSrcs.push_back(str);
    
    str = "+a^2b+a^2c+3abc+ab^2+b^2c+ac^2+bc^2";
    vecStrSrcs.push_back(str);
    
    str = "+a^3+3a^2b+3a^2c+3ab^2+6abc+3ac^2+b^3+3b^2c+3bc^2+c^3";
    vecStrSrcs.push_back(str);

    //----------------------------------------------
    ret = dxszh.convertStrsToInts(vecStrSrcs, baseNum);

    return 0;
}


/*
(+a^4+b^4+c^4+d^4)
(+a^2b^2+a^2c^2+a^2d^2+b^2c^2+b^2d^2+c^2d^2)
(+ab^3+ac^3+ad^3+bc^3+bd^3+cd^3+a^3b+a^3c+a^3d+b^3c+b^3d+c^3d)
(+abc^2+abd^2+acd^2+bcd^2+ab^2c+ab^2d+ac^2d+bc^2d+a^2bc+a^2bd+a^2cd+b^2cd)
(+abcd)
(+a^2+b^2+c^2+d^2)^2
(+ab+ac+ad+bc+bd+cd)^2
(+a+b+c+d)(+a^3+b^3+c^3+d^3)
(+a+b+c+d)(+ab^2+ac^2+ad^2+bc^2+bd^2+cd^2+a^2b+a^2c+a^2d+b^2c+b^2d+c^2d)
(+a+b+c+d)(+abc+abd+acd+bcd)
(+a+b+c+d)^2(+a^2+b^2+c^2+d^2)
(+a+b+c+d)^2(+ab+ac+ad+bc+bd+cd)
(+a+b+c+d)^4

步骤8： 最终结果: +a^4+b^4+c^4+d^4;
步骤8： 最终结果: +a^2b^2+a^2c^2+a^2d^2+b^2c^2+b^2d^2+c^2d^2;
步骤8： 最终结果: +ab^3+ac^3+ad^3+bc^3+bd^3+cd^3+a^3b+a^3c+a^3d+b^3c+b^3d+c^3d;
步骤8： 最终结果: +abc^2+abd^2+acd^2+bcd^2+ab^2c+ab^2d+ac^2d+bc^2d+a^2bc+a^2bd+a^2cd+b^2cd;
步骤8： 最终结果: +abcd;
步骤8： 最终结果: +a^4+2a^2b^2+2a^2c^2+2a^2d^2+b^4+2b^2c^2+2b^2d^2+c^4+2c^2d^2+d^4;
步骤8： 最终结果: +a^2b^2+2a^2bc+2a^2bd+2ab^2c+2ab^2d+6abcd+a^2c^2+2a^2cd+2abc^2+2ac^2d+a^2d^2+2abd^2+2acd^2+b^2c^2+2b^2cd+2bc^2d+b^2d^2+2bcd^2+c^2d^2;
步骤8： 最终结果: +a^4+ab^3+ac^3+ad^3+a^3b+b^4+bc^3+bd^3+a^3c+b^3c+c^4+cd^3+a^3d+b^3d+c^3d+d^4;
步骤8： 最终结果: +2a^2b^2+2a^2c^2+2a^2d^2+2abc^2+2abd^2+2acd^2+a^3b+a^3c+a^3d+2ab^2c+2ab^2d+2ac^2d+ab^3+2b^2c^2+2b^2d^2+2bcd^2+2a^2bc+2a^2bd+b^3c+b^3d+2bc^2d+ac^3+bc^3+2c^2d^2+2a^2cd+2b^2cd+c^3d+ad^3+bd^3+cd^3;
步骤8： 最终结果: +a^2bc+a^2bd+a^2cd+4abcd+ab^2c+ab^2d+b^2cd+abc^2+ac^2d+bc^2d+abd^2+acd^2+bcd^2;
步骤8： 最终结果: +a^4+2a^2b^2+2a^2c^2+2a^2d^2+2a^3b+2ab^3+2abc^2+2abd^2+2a^3c+2ab^2c+2ac^3+2acd^2+2a^3d+2ab^2d+2ac^2d+2ad^3+b^4+2b^2c^2+2b^2d^2+2a^2bc+2b^3c+2bc^3+2bcd^2+2a^2bd+2b^3d+2bc^2d+2bd^3+c^4+2c^2d^2+2a^2cd+2b^2cd+2c^3d+2cd^3+d^4;
步骤8： 最终结果: +a^3b+a^3c+a^3d+5a^2bc+5a^2bd+5a^2cd+2a^2b^2+5ab^2c+5ab^2d+12abcd+2a^2c^2+5abc^2+5ac^2d+2a^2d^2+5abd^2+5acd^2+ab^3+b^3c+b^3d+5b^2cd+2b^2c^2+5bc^2d+2b^2d^2+5bcd^2+ac^3+bc^3+c^3d+2c^2d^2+ad^3+bd^3+cd^3;
步骤8： 最终结果: +a^4+4a^3b+4a^3c+4a^3d+6a^2b^2+12a^2bc+12a^2bd+6a^2c^2+12a^2cd+6a^2d^2+4ab^3+12ab^2c+12ab^2d+12abc^2+24abcd+12abd^2+4ac^3+12ac^2d+12acd^2+4ad^3+b^4+4b^3c+4b^3d+6b^2c^2+12b^2cd+6b^2d^2+4bc^3+12bc^2d+12bcd^2+4bd^3+c^4+4c^3d+6c^2d^2+4cd^3+d^4;
*/
int main(int argc, char *argv[])
{
    int ret = 0;
    CDuoXiangShiZuHe dxszh;

    std::vector<std::string> vecStrSrcs;
    std::string str = "";
    int baseNum = 5;
    
    str = "+a^4+b^4+c^4+d^4";
    vecStrSrcs.push_back(str);
    str = "+a^2b^2+a^2c^2+a^2d^2+b^2c^2+b^2d^2+c^2d^2";
    vecStrSrcs.push_back(str);
    str = "+ab^3+ac^3+ad^3+bc^3+bd^3+cd^3+a^3b+a^3c+a^3d+b^3c+b^3d+c^3d";
    vecStrSrcs.push_back(str);
    str = "+abc^2+abd^2+acd^2+bcd^2+ab^2c+ab^2d+ac^2d+bc^2d+a^2bc+a^2bd+a^2cd+b^2cd";
    vecStrSrcs.push_back(str);
    str = "+abcd";
    vecStrSrcs.push_back(str);
    str = "+a^4+2a^2b^2+2a^2c^2+2a^2d^2+b^4+2b^2c^2+2b^2d^2+c^4+2c^2d^2+d^4";
    vecStrSrcs.push_back(str);
    str = "+a^2b^2+2a^2bc+2a^2bd+2ab^2c+2ab^2d+6abcd+a^2c^2+2a^2cd+2abc^2+2ac^2d+a^2d^2+2abd^2+2acd^2+b^2c^2+2b^2cd+2bc^2d+b^2d^2+2bcd^2+c^2d^2";
    vecStrSrcs.push_back(str);
    str = "+a^4+ab^3+ac^3+ad^3+a^3b+b^4+bc^3+bd^3+a^3c+b^3c+c^4+cd^3+a^3d+b^3d+c^3d+d^4";
    vecStrSrcs.push_back(str);
    str = "+2a^2b^2+2a^2c^2+2a^2d^2+2abc^2+2abd^2+2acd^2+a^3b+a^3c+a^3d+2ab^2c+2ab^2d+2ac^2d+ab^3+2b^2c^2+2b^2d^2+2bcd^2+2a^2bc+2a^2bd+b^3c+b^3d+2bc^2d+ac^3+bc^3+2c^2d^2+2a^2cd+2b^2cd+c^3d+ad^3+bd^3+cd^3";
    vecStrSrcs.push_back(str);
    str = "+a^2bc+a^2bd+a^2cd+4abcd+ab^2c+ab^2d+b^2cd+abc^2+ac^2d+bc^2d+abd^2+acd^2+bcd^2";
    vecStrSrcs.push_back(str);
    str = "+a^4+2a^2b^2+2a^2c^2+2a^2d^2+2a^3b+2ab^3+2abc^2+2abd^2+2a^3c+2ab^2c+2ac^3+2acd^2+2a^3d+2ab^2d+2ac^2d+2ad^3+b^4+2b^2c^2+2b^2d^2+2a^2bc+2b^3c+2bc^3+2bcd^2+2a^2bd+2b^3d+2bc^2d+2bd^3+c^4+2c^2d^2+2a^2cd+2b^2cd+2c^3d+2cd^3+d^4";
    vecStrSrcs.push_back(str);
    str = "+a^3b+a^3c+a^3d+5a^2bc+5a^2bd+5a^2cd+2a^2b^2+5ab^2c+5ab^2d+12abcd+2a^2c^2+5abc^2+5ac^2d+2a^2d^2+5abd^2+5acd^2+ab^3+b^3c+b^3d+5b^2cd+2b^2c^2+5bc^2d+2b^2d^2+5bcd^2+ac^3+bc^3+c^3d+2c^2d^2+ad^3+bd^3+cd^3";
    vecStrSrcs.push_back(str);
    str = "+a^4+4a^3b+4a^3c+4a^3d+6a^2b^2+12a^2bc+12a^2bd+6a^2c^2+12a^2cd+6a^2d^2+4ab^3+12ab^2c+12ab^2d+12abc^2+24abcd+12abd^2+4ac^3+12ac^2d+12acd^2+4ad^3+b^4+4b^3c+4b^3d+6b^2c^2+12b^2cd+6b^2d^2+4bc^3+12bc^2d+12bcd^2+4bd^3+c^4+4c^3d+6c^2d^2+4cd^3+d^4";
    vecStrSrcs.push_back(str);

    //----------------------------------------------
    ret = dxszh.convertStrsToInts(vecStrSrcs, baseNum);

    return 0;
}


int main4(int argc, char *argv[])
{
    int ret = 0;
    int cnt = 0;

//    std::string str = "(2a^2 - 3a +7)((a+2b)^3)(b^2 + ab +5b + 2)(a+5b)^3";
//    std::string str = "(2a^2-3a+7)((a+2b)^5)(b^2+ab+5b+2)((a+5b)^3)";
//    std::string str = "((a+5b)^3)";
//    std::string str = "(2a^2-3a+7)(b^2+ab+5b+2)";
    std::string str = "(a+b+c)^3";

    if(argc != 4 && argc != 5)
    {
        print_help(argc, argv);
        return -1;
    }
    
    //-------------------------
    CDuoXiangShi dxs;

    int isInputFile = 0;
    std::string file_in = "./math_formula.txt";
    std::string outDir = "./";
    std::string str2 = "";
    std::string str3 = "";
    char outTex[600] = "";

    int momomialValue[27] = {0};
    
    if(strcmp(argv[1], "0") == 0) // isInputFile = 0;
    {
        isInputFile = 0;
        str = argv[2];
        outDir = argv[3];
        
        str2 = str;
        printf("str: %s\n", str.c_str());

        ret = dxs.justDoIt(str, str2);

        printf("str2: 3333: %s\n", str2.c_str());

        //-------------check value----------------
        if(argc == 5)
        {
            std::string valuesStr = argv[4];

            ret = dxs.valuesStrToMomomial(valuesStr, momomialValue);
            if (ret != 0)
            {
                printf("Error: %s 11111\n", __FUNCTION__);
                return -1;
            }

            ret = dxs.setStrValue(str2, momomialValue, str3);

            printf("str3: 4444: %s\n", str3.c_str());
        }

        //--------------------------------
        sprintf(outTex, "%s/out.tex", outDir.c_str());
        printf("outTex: %s\n", outTex);

        FILE * fp = fopen(outTex, "w");

        std::string strPdf = "\\documentclass[10 pt]{article}\n\\usepackage{xcolor}\n\\usepackage{geometry}\n\\geometry{left=1cm,right=1cm,top=1cm,bottom=1cm}\n\\begin{document}\n";
        strPdf += "${\\color{red}" + str + "}=$\n";
        strPdf += "$" + str2 + "$\n";
        strPdf += "\\end{document}";

        fwrite(strPdf.c_str(), strPdf.length(), 1, fp);

        fclose(fp);
    }else // isInputFile = 1;
    {
        isInputFile = 1;
        file_in = argv[2];
        outDir = argv[3];
        const int size = 100 * 1024;
        char buff[size] = {0};

        std::string strPdf = "\\documentclass[10 pt]{article}\n\\usepackage{xcolor}\n\\usepackage{geometry}\n\\geometry{left=1cm,right=1cm,top=1cm,bottom=1cm}\n\\begin{document}\n";
//        strPdf += "{\\color{Blue}x^2}+{\\color{Brown}2x} -{\\color{OliveGreen}1}\n";
//        strPdf += "\\Bigg ( \\bigg [ \\Big \\{\\big\\langle \\left | \\| \\frac{a}{b} \\| \\right | \\big \\rangle\\Big\\}\\bigg ] \\Bigg )\n";

        //-----------------------------------------
        FILE * fp1 = fopen(file_in.c_str(), "rb");
        if(fp1 == NULL)
        {
            printf("Error: fp1 == NULL;:file_in: %s\n", file_in.c_str());
            return -1;
        }

        while(feof(fp1) == 0)
        {
            memset(buff, 0, sizeof(size));

            char * str31 = fgets(buff, size - 1, fp1);
            if(str31 == NULL)
            {
                break;
            }

            int len = strlen(buff);

            buff[len - 2] = '\0';
            if(buff[len - 3] == '\r')
            {
                buff[len - 3] = '\0';
            }

            //--------------------
            str = buff;
            
            std::string str4 = str;
            printf("str: %s\n", str.c_str());

            ret = dxs.justDoIt(str, str4); //多项式展开

            printf("str2: 3333: %s\n", str4.c_str());

            //-------------check value----------------
            if (argc == 5)
            {
                std::string valuesStr = argv[4];

                ret = dxs.valuesStrToMomomial(valuesStr, momomialValue);
                if (ret != 0)
                {
                    printf("Error: %s 11111\n", __FUNCTION__);
                    return -1;
                }

                ret = dxs.setStrValue(str4, momomialValue, str3);

                printf("str3: 4444: %s\n", str3.c_str());
            }

            //-----------------------
            strPdf += "\\noindent${\\color{red}" + str + "}=$\n";
            strPdf += "$" + str4 + "$\\\\\n";
        }
        fclose(fp1);
        
        //----------------------------------------
        sprintf(outTex, "%s/out.tex", outDir.c_str());
        printf("outTex: %s\n", outTex);

        FILE * fp = fopen(outTex, "w");
        strPdf += "\\end{document}";
        fwrite(strPdf.c_str(), strPdf.length(), 1, fp);
        fclose(fp);
    }

    //--------------------------
    char outPdfCmd[600] = {0};
    sprintf(outPdfCmd, "pdflatex %s", outTex);
    printf("outPdfCmd: %s\n", outPdfCmd);

    system(outPdfCmd);

//    system("pause");

    return 0;
}

