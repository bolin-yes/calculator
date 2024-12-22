#include"LinkedStack.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

#define MAX 260//用于fgets函数的读取字符数


Status InfixToPostfix(char* expression, char* post);
/*中缀表达式转后缀表达式
返回值OK代表运行成功，ERROR代表失败
参数expression为输入的表达式，post为转化后的后缀表达式
*/
double CalPostfix(char*post);
/*计算后缀表达式
返回值表示计算结果
参数post为经过转化后的后缀表达式
*/

int GetPriority(char operator);
/*获取运算符优先级
返回值表示优先级大小
参数operator为运算符
*/
void OutPutResult(const char*file,double result,char*fileInPut);
/*将结果写入文件
无返回值
参数file为文件名，result为运算结果，fileInPut为需要计算的式子
*/


int GetPriority(char operator) {
    switch (operator) {
            case '+':
            case '-':
                return 1;
            case '*':
            case '/':
                return 2;
            case '^':
                return 3;
            case's':
            case'c':
            case't':
            case'd':
            case'e':
            case'f':
            case'g':
            return 4;
            default:
                return 0;
    }
}//返回operator所指向的值的优先级大小


Status InfixToPostfix(char* expression, char post[MAX]){
    //expression为中缀表达式字符串，post为后缀表达式字符串,在这里后缀表达式post有栈的作用
    Stack* stack = StackConstruct(sizeof(char));
    char cTemp, cChar;
    void* r;
    int i, j = 0;
    for (i = 0; i < strlen(expression); i++){ //遍历中缀表达式
        //遍历中缀表达式到数字和小数点,直接输出
        int k=0;//k用于记录小数点个数
        while (isdigit(expression[i]) || '.' == expression[i]){
            if ('.'==expression[i]){
              k++;
              if(k>1){
                printf("表达式有误：小数点不正确");
                exit(0);
              }//判断是否正确输入，当一个数字中小数点个数大于一时，
            }
            post[j++] = expression[i++];
            if (!isdigit(expression[i]) && '.' != expression[i])
                post[j++] = ' ';   //一个数字输出后使用空格与其它运算符分隔开
        }
        //遍历中缀表达式到左括号直接入栈
        if ('(' == expression[i]) {
            StackPush(stack, &expression[i]);
        }

        //遍历中缀表达式到右括号,直接将栈内符号出栈，直到栈顶为左括号
        else if (')' == expression[i]) {
            while (1) {
                if (IsEmpty(stack) == 0) {
                    r = StackGetTop(stack);
                    cChar = *((char*)r);
                }
                if ('(' == cChar) break;
                StackPop(stack, &cTemp);
                post[j++] = cTemp;
                post[j++] = ' ';

            }
            StackPop(stack, &cTemp);  //左括号出栈但不输出
        }

        //遍历中缀表达式到+或—
        else if ('+' == expression[i] || '-' == expression[i]) {
            while (1) {
                if (IsEmpty(stack) == 0) {
                    r = StackGetTop(stack);
                    cChar = *((char*)r);
                }
                if (IsEmpty(stack) || '(' == cChar) break;
                while(GetPriority(cChar)>GetPriority(expression[i])){
                StackPop(stack, &cTemp);//栈中除了+-，其它运算符优先级更高，将其出栈
                post[j++] = cTemp;
                post[j++] = ' ';
                r = StackGetTop(stack);
                cChar = *((char*)r);
                }
            }
            if ('(' == expression[i - 1]||i==0){ //支持负数，如：当（-x）入栈时，在后缀表达式中添加0，将（-x）表示成0-x；
                post[j++] = '0';
                post[j++] = ' ';
            }
            StackPush(stack, &expression[i]);//把+-入栈
        }

        //遍历中缀表达式到*或/
        else if ('*' == expression[i] || '/' == expression[i] || '%' == expression[i]){
            while (1) {
                if (IsEmpty(stack) == 0) {
                    r = StackGetTop(stack);
                    cChar = *((char*)r);
                }
                if (IsEmpty(stack) || '(' == cChar || '+' == cChar || '-' == cChar) break;
                StackPop(stack, &cTemp);//栈中除了+-，其它运算符优先级更高，将其出栈
                post[j++] = cTemp;
                post[j++] = ' ';
            }
            StackPush(stack, &expression[i]);//将*/入栈
        }
        /*
        三角函数反三角函数和平方根函数的入栈，如果要将sin，cos等单词入栈时，
        出栈操作也比较麻烦，所以，用一个符号或者一个字母来代替sin等单词，只
        要这个符号不与已有符号重叠从而造成歧义，那么可以简化出入栈。
        */
        else if (strncmp(&expression[i],"sin",3)==0||strncmp(&expression[i],"cos",3)==0||
        strncmp(&expression[i],"tan",3)==0){
            StackPush(stack,&expression[i]);
            i+=2;//这里不是i+=3的原因是for循环后i会自增1，下同。
        }
        else if(strncmp(&expression[i],"arcsin",6)==0){
            cChar='d';
            StackPush(stack,&cChar);
            i+=5;
        }
        else if(strncmp(&expression[i],"arccos",6)==0){
            cChar='e';
            StackPush(stack,&cChar);
            i+=5;
        }
        else if(strncmp(&expression[i],"arctan",6)==0){
            cChar='f';
            StackPush(stack,&cChar);
            i+=5;
        }
        else if(strncmp(&expression[i],"sqrt",4)==0){
            cChar='g';
            StackPush(stack,&cChar);
            i+=3;
        }
        else if ('^' == expression[i]){
            StackPush(stack, &expression[i]);
        }
        else if('\n'==expression[i]){
             return OK;
        }
        //判断输入的表达式是否错误
        else{
            printf("表达式有误");
            
        }   
        printf("%s\n",post);
        
    }

    //判断栈空,非空则直接出栈并输出
    while (!IsEmpty(stack)){
        StackPop(stack, &cTemp);
        if ('(' != cTemp) {
            post[j++] = cTemp;
            post[j++] = ' ';
        }
    }
    post[--j] = '\0';
    StackDestruct(stack);
    return OK;

}
//计算后缀表达式
double CalPostfix(char*post){//返回值为计算结果
    double temp, dFro, dPost;
    char d[MAX];
    Stack* stack = StackConstruct(sizeof(double));
    for (int i = 0; i < strlen(post); i++){
        int j = 0;//每次for循环j都被重新赋值成0
        while (isdigit(post[i]) || '.' == post[i]) { //一次循环可以将一个数据转换成double类型并入栈
            d[j++] = post[i++];//把字符串里的数字和'.'放到另一个字符串中，以将其转换为double类型
            d[j] = '\0';//方便atof函数读取到'\0'时自动停止

            if (!isdigit(post[i]) && '.' != post[i]) { 
                //当expression中读取的不是数字(即expression[]中的运算符)后，将d[]中字符转换成double类型
                temp = atof(d);   //使用atof()将字符串形式的运算数转换为double型数据                
                StackPush(stack, &temp); //将类型转化成double后的运算数入栈
            }
        }
        int c;
        /*
        用于强制转换为int 使得在次方运算时避免出差错,发现使用pow函数时计算器无法运算2.1^2.1这样的表达式，
        计算结果会出现很大的差距，例如2.1^2.1pow函数输出的结果为8.4，但实际上只有4.几，于是我决定舍弃
        一部分精度来描绘出一个大致的结果
        */
        if (post[i] == '+' || post[i] == '-' || post[i] == '*' || post[i] == '/' || post[i] == '%' || post[i] == '^') {
            StackPop(stack, &dPost);
            StackPop(stack, &dFro);
            switch (post[i]){
            case '+':
                dFro += dPost;
                break;
            case '-':
                dFro -= dPost;
                break;
            case '*':
                dFro *= dPost;
                break;
            case '/':
                if (dPost == 0) {
                    printf("Error:分母不能为0");//分母为0时：ERROR
                    exit(0);
                }
                dFro /= dPost;
                break;
            case '^':
                c = (int)dFro;
                if (dPost == 0) {
                    dFro = 1;
                }
                else {
                    for (int i = 0; i < dPost - 1; i++) {
                        dFro *= c;
                    }
                }
                break;
            }
            StackPush(stack, &dFro);
            }
         //加入三角函数和反三角函数以及平方根函数
        if (post[i]=='s'||post[i]=='c'||post[i]=='t'||post[i]=='d'||post[i]=='e'||post[i]=='f'||post[i]=='g'){
             StackPop(stack, &dPost);
            switch (post[i]){
            case 's'://sin
               dFro = sin(dPost);
                break;
            case 'c'://cos
               dFro = cos(dPost);
                break;
            case 't'://tan
               dFro = tan(dPost);
                break;
            case 'd'://arcsin
               dFro = asin(dPost);
                break;
            case 'e'://arccos
               dFro = acos(dPost);
                break;
            case 'f'://arctan
               dFro = atan(dPost);
                break;
            case 'g'://square
               dFro = sqrt(dPost);
                break;
            }
            StackPush(stack, &dFro);
        } 
    }
    StackPop(stack, &temp);//将栈中最后计算出的结果放到变量e中
    StackDestruct(stack);
    return dFro;
}
void OutPutResult(const char*file,double result,char*fileInPut){
     FILE*fp=fopen(file,"a");
     if(fp!=NULL){
       fprintf(fp,"%s=%f\n",fileInPut,result);
       fclose(fp);
     }
}

int main(int argc,char*argv[]){
    FILE*file=NULL;
    double result;
    printf("argc=%d\n",argc);
    printf("第一个指令:%s\n",argv[0]);
    printf("表达式文件：%s\n",argv[1]);
    printf("结果文件：%s\n",argv[2]);
    if(argc==3){
      file=fopen(argv[1],"r");
      #if DEBUG
      if (file!=NULL){
        printf("successfully to open\n");
      }
      #endif
    while (file!=NULL){
      char *expression=malloc(MAX),*post=malloc(MAX);
      int i=0;
      fgets(expression,MAX,file);
      if(strcmp(expression,"stop\n")==0){
        break;
      }
      printf("%s",expression);
      if(expression[strlen(expression)-1]=='\n'){
        expression[strlen(expression)-1]='\0';
        }
      InfixToPostfix(expression,post);
      printf("%s\n",post);
      result=CalPostfix(post);

      OutPutResult(argv[2],result,expression);
      free(expression);
      free(post);
    }
    fclose(file);
    }
    return 0;  
}
