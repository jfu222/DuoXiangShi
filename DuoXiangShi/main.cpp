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


int main(int argc, char *argv[])
{
    int ret = 0;
    CDuoXiangShiZuHe dxszh;
    std::string strSrc26EnglishLetters = "abcd";
    int exponential = 4;
    std::vector<std::string> vecStrsDst;
    dxszh.createCombinePolynomial(strSrc26EnglishLetters, exponential, vecStrsDst);

    return 0;
}

int main2(int argc, char *argv[])
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

//    system(outPdfCmd);

//    system("pause");

    return 0;
}

