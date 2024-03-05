//词法分析器

#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/* 单词编码 */
enum Tokencode
{
	/*未定义符号*/
	SYM_UNDEF = 0,

	/* 关键字 */
	KEY_INT,	    //int
	KEY_IF,		//if
	KEY_FOR,		//for
	KEY_WHILE,	//while
	KEY_DO,      //do
	KEY_RETURN,	//return
	KEY_BREAK,   //break
	KEY_CONTINUE,//continue
	KEY_INCLUDE, //include
	KEY_MAIN,	//main
	KEY_IOSTREAM,//iostream
	KEY_USING,   //using
	KEY_NAMESPACE,//namespace
	KEY_DOUBLE,	//double
	KEY_STD,	    //std
	KEY_ELSE,	//else

	/* 运算符 */
	SYM_PLUS,	//+
	SYM_MINUS,	//-
	SYM_STAR,	//*
	SYM_DIVIDE,	///
	SYM_ASSIGN,	//=
	SYM_EQ,		//==
	SYM_LT,		//<
	SYM_LEQ,		//<=
	SYM_GT,		//>
	SYM_GEQ,		//>=
	SYM_UEQ,     //!=

	/* 分隔符 */
	SYM_OPENPA,	//(
	SYM_CLOSEPA,	//)
	SYM_OPENBR,	//[
	SYM_CLOSEBR,	//]
	SYM_BEGIN,	//{
	SYM_END,		//}
	SYM_COMMA,	//,
	SYM_SEMOCOLOM,	//;

	/* 常量 */
	SYM_INT,		//整型常量
	SYM_DOUBLE,	//浮点型常量

	/* 标识符 */
	SYM_IDENT
};

//全局变量
Tokencode code = SYM_UNDEF;		//记录单词的种别码
int row = 1;					//记录字符所在的行数
string token = "";				//用于存储单词
const int MAX = 16;				//关键字数量
char  keyWord[][10] = { "int","if","for","while","do","return","break","continue",
"include","main","iostream","using","namespace","double","std","else"};	//存储关键词


//函数部分
//打印词法分析的结果
void print(Tokencode code)
{
	switch (code)
	{
		/*未识别的符号*/
	case SYM_UNDEF:
		cout << "(" << token << " , " << code << ") " << "，符号未识别，且未识别的符号在第" << row << "行" << endl;
		return;
		break;
		/*关键字*/
	case KEY_INT:	    //int
	case KEY_IF:		//if
	case KEY_FOR:		//for
	case KEY_WHILE:	//while
	case KEY_DO:      //do
	case KEY_RETURN:	//return
	case KEY_BREAK:   //break
	case KEY_CONTINUE://continue
	case KEY_INCLUDE: //include
	case KEY_MAIN:	//main
	case KEY_IOSTREAM://iostream
	case KEY_USING:   //using
	case KEY_NAMESPACE://namespace
	case KEY_DOUBLE:	//double
	case KEY_STD:	    //std
	case KEY_ELSE:	//else
		cout << "(" << token << " , " << code << ") --关键字" << endl;
		break;

		/* 运算符 */
	case SYM_PLUS:	//+
	case SYM_MINUS:	//-
	case SYM_STAR:	//*
	case SYM_DIVIDE:	///
	case SYM_ASSIGN:	//=
	case SYM_EQ:		//==
	case SYM_LT:		//<
	case SYM_LEQ:	//<=
	case SYM_GT:		//>
	case SYM_GEQ:		//>=
	case SYM_UEQ:    //!=
		cout << "(" << token << " , " << code << ") --运算符" << endl;
		break;
	/* 分隔符 */
	case SYM_OPENPA:	//(
	case SYM_CLOSEPA:	//)
	case SYM_OPENBR:	//[
	case SYM_CLOSEBR:	//]
	case SYM_BEGIN:	//{
	case SYM_END:	//}
	case SYM_COMMA:	//,
	case SYM_SEMOCOLOM:	//;
		cout << "(" << token << " , " << code << ") --分界符" << endl;
		break;

		/* 常量 */
	case SYM_INT:	//整型常量
	case SYM_DOUBLE:	//浮点型常量
		if (token.find('.') == token.npos)
			cout << "(" << atoi(token.c_str()) << " , " << code << ") --整型常量" << endl;						//单词为整型
		else
			cout << "(" << atof(token.c_str()) << " , " << code << ") --浮点型常量" << endl;							//单词为浮点型
		return;
		break;
		/* 标识符 */
	case SYM_IDENT:
		cout << "(" << token << " , " << code << ") --标识符" << endl;
		break;
	default:
		break;
	}
}

/*判断是否是关键字*/
bool isKey(string token)
{
	for (int i = 0; i < MAX; i++)
	{
		if (token.compare(keyWord[i]) == 0)
			return true;
	}
	return false;
}

/*返回关键字的内码值*/
int  getKeyID(string token)
{
	for (int i = 0; i < MAX; i++)
	{	//关键字的内码值为keyWord数组中对应的下标加1
		if (token.compare(keyWord[i]) == 0)
			return i + 1;
	}
	return -1;
}

/*判断一个字符是否是字母*/
bool isLetter(char letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
		return true;
	return false;

}

/*判断一个字符是否是数字*/
bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9')
		return true;
	return false;
}

/*词法分析*/
void lexicalAnalysis(FILE* fp)//fp：文件指针,code：单词对应的种别码
{
	char ch;			//用于存储从文件中获取的单个字符
	while ((ch = fgetc(fp)) != EOF)	//未读取到文件尾，从文件中获取一个字符
	{
		token = ch;									//将获取的字符存入token中
		if (ch == ' ' || ch == '\t' || ch == '\n')	//忽略空格、Tab和回车
		{
			if (ch == '\n')							//遇到换行符，记录行数的row加1
				row++;
			continue;								//继续执行循环
		}
		else if (isLetter(ch))			//以字母开头，关键字或标识符
		{
			token = "";					//token初始化
			while (isLetter(ch) || isDigit(ch))	//非字母或数字时退出，将单词存储在token中
			{
				token.push_back(ch);	//将读取的字符ch存入token中
				ch = fgetc(fp);			//获取下一个字符
			}
			//文件指针后退一个字节，即重新读取上述单词后的第一个字符
			fseek(fp, -1L, SEEK_CUR);
			if (isKey(token))	//关键字
				code = Tokencode(getKeyID(token));
			else	//标识符
				code = SYM_IDENT;	//单词为标识符
		}
		else if (isDigit(ch))	//无符号常数以数字开头
		{
			int isdouble = 0;	//标记是否为浮点数
			token = "";			//token初始化
			while (isDigit(ch))	//当前获取到的字符为数字
			{
				token.push_back(ch);		//读取数字，将其存入token中
				ch = fgetc(fp);				//从文件中获取下一个字符
				//该单词中第一次出现小数点
				if (ch == '.' && isdouble == 0)
				{
					//小数点下一位是数字
					if (isDigit(fgetc(fp)))
					{
						isdouble = 1;		//标记该常数中已经出现过小数点
						fseek(fp, -1L, SEEK_CUR);		//将超前读取的小数点后一位重新读取	
						token.push_back(ch);			//将小数点入token中
						ch = fgetc(fp);				//读取小数点后的下一位数字
					}
				}
			}
			if (isdouble == 1)
				code = SYM_DOUBLE;	//单词为浮点型
			else
				code = SYM_INT;				//单词为整型
			//文件指针后退一个字节，即重新读取常数后的第一个字符
			fseek(fp, -1L, SEEK_CUR);
		}
		else switch (ch)
		{
			/*运算符*/
		case '+': code = SYM_PLUS;		//+加号			
			break;
		case '-': code = SYM_MINUS;		//-减号
			break;
		case '*': code = SYM_STAR;		//*乘号		
			break;
		case '/': code = SYM_DIVIDE;		//除号
			break;
		case '=':
		{
			ch = fgetc(fp);				//超前读取'='后面的字符
			if (ch == '=')				//==等于号
			{
				token.push_back(ch);	//将'='后面的'='存入token中
				code = SYM_EQ;			//单词为"=="
			}
			else {						//=赋值运算符
				code = SYM_ASSIGN;		//单词为"="
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		case '<':
		{
			ch = fgetc(fp);				//超前读取'<'后面的字符
			if (ch == '=')				//<=小于等于号
			{
				token.push_back(ch);	//将'<'后面的'='存入token中
				code = SYM_LEQ;			//单词为"<="
			}
			else {						//<小于号
				code = SYM_LT;			//单词为"<"
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		case '>':
		{
			ch = fgetc(fp);				//超前读取'>'后面的字符
			if (ch == '=')				//>=大于等于号
			{
				token.push_back(ch);	//将'>'后面的'='存入token中
				code = SYM_GEQ;			//单词为">="
			}
			else {						//>大于号
				code = SYM_GT;			//单词为">"
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		case '!':
		{
			ch = fgetc(fp);				//超前读取'!'后面的字符
			if (ch == '=')				//!=不等于号
			{
				token.push_back(ch);	//将'!'后面的'='存入token中
				code = SYM_UEQ;			//单词为"!="
			}
			else {						
				code = SYM_UNDEF;			//单词为未识别符号
				fseek(fp, -1L, SEEK_CUR);	//将超前读取的字符重新读取
			}
		}
		break;
		/*分界符*/
		case '(': code = SYM_OPENPA;		//(左圆括号
			break;
		case ')': code = SYM_CLOSEPA;	//)右圆括号
			break;
		case '[': code = SYM_OPENBR;		//[左中括号
			break;
		case ']': code = SYM_CLOSEBR;	//]右中括号
			break;
		case '{': code = SYM_BEGIN;		//{左大括号
			break;
		case '}': code = SYM_END;		//}右大括号
			break;
		case ',': code = SYM_COMMA;		//,逗号
			break;
		case ';': code = SYM_SEMOCOLOM;	//;分号
			break;
			//未识别符号
		default: code = SYM_UNDEF;
		}
		print(code);				
	}
}

int main()
{
	string filename;		//文件路径
	FILE* fp;				//文件指针
	cout << "*----请输入源文件名----*：" << endl;
	while (true) {
		cin >> filename;		//读取文件路径
		if ((fopen_s(&fp, filename.c_str(), "r")) == 0)		//打开文件
			break;
		else
			cout << "路径输入错误！" << endl;	
	}
	cout << "/-------词法分析结果-------/" << endl;
	lexicalAnalysis(fp);		//词法分析
	fclose(fp);					//关闭文件
	return 0;
}
