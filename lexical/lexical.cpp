//�ʷ�������

#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;

/* ���ʱ��� */
enum Tokencode
{
	/*δ�������*/
	SYM_UNDEF = 0,

	/* �ؼ��� */
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

	/* ����� */
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

	/* �ָ��� */
	SYM_OPENPA,	//(
	SYM_CLOSEPA,	//)
	SYM_OPENBR,	//[
	SYM_CLOSEBR,	//]
	SYM_BEGIN,	//{
	SYM_END,		//}
	SYM_COMMA,	//,
	SYM_SEMOCOLOM,	//;

	/* ���� */
	SYM_INT,		//���ͳ���
	SYM_DOUBLE,	//�����ͳ���

	/* ��ʶ�� */
	SYM_IDENT
};

//ȫ�ֱ���
Tokencode code = SYM_UNDEF;		//��¼���ʵ��ֱ���
int row = 1;					//��¼�ַ����ڵ�����
string token = "";				//���ڴ洢����
const int MAX = 16;				//�ؼ�������
char  keyWord[][10] = { "int","if","for","while","do","return","break","continue",
"include","main","iostream","using","namespace","double","std","else"};	//�洢�ؼ���


//��������
//��ӡ�ʷ������Ľ��
void print(Tokencode code)
{
	switch (code)
	{
		/*δʶ��ķ���*/
	case SYM_UNDEF:
		cout << "(" << token << " , " << code << ") " << "������δʶ����δʶ��ķ����ڵ�" << row << "��" << endl;
		return;
		break;
		/*�ؼ���*/
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
		cout << "(" << token << " , " << code << ") --�ؼ���" << endl;
		break;

		/* ����� */
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
		cout << "(" << token << " , " << code << ") --�����" << endl;
		break;
	/* �ָ��� */
	case SYM_OPENPA:	//(
	case SYM_CLOSEPA:	//)
	case SYM_OPENBR:	//[
	case SYM_CLOSEBR:	//]
	case SYM_BEGIN:	//{
	case SYM_END:	//}
	case SYM_COMMA:	//,
	case SYM_SEMOCOLOM:	//;
		cout << "(" << token << " , " << code << ") --�ֽ��" << endl;
		break;

		/* ���� */
	case SYM_INT:	//���ͳ���
	case SYM_DOUBLE:	//�����ͳ���
		if (token.find('.') == token.npos)
			cout << "(" << atoi(token.c_str()) << " , " << code << ") --���ͳ���" << endl;						//����Ϊ����
		else
			cout << "(" << atof(token.c_str()) << " , " << code << ") --�����ͳ���" << endl;							//����Ϊ������
		return;
		break;
		/* ��ʶ�� */
	case SYM_IDENT:
		cout << "(" << token << " , " << code << ") --��ʶ��" << endl;
		break;
	default:
		break;
	}
}

/*�ж��Ƿ��ǹؼ���*/
bool isKey(string token)
{
	for (int i = 0; i < MAX; i++)
	{
		if (token.compare(keyWord[i]) == 0)
			return true;
	}
	return false;
}

/*���عؼ��ֵ�����ֵ*/
int  getKeyID(string token)
{
	for (int i = 0; i < MAX; i++)
	{	//�ؼ��ֵ�����ֵΪkeyWord�����ж�Ӧ���±��1
		if (token.compare(keyWord[i]) == 0)
			return i + 1;
	}
	return -1;
}

/*�ж�һ���ַ��Ƿ�����ĸ*/
bool isLetter(char letter)
{
	if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z'))
		return true;
	return false;

}

/*�ж�һ���ַ��Ƿ�������*/
bool isDigit(char digit)
{
	if (digit >= '0' && digit <= '9')
		return true;
	return false;
}

/*�ʷ�����*/
void lexicalAnalysis(FILE* fp)//fp���ļ�ָ��,code�����ʶ�Ӧ���ֱ���
{
	char ch;			//���ڴ洢���ļ��л�ȡ�ĵ����ַ�
	while ((ch = fgetc(fp)) != EOF)	//δ��ȡ���ļ�β�����ļ��л�ȡһ���ַ�
	{
		token = ch;									//����ȡ���ַ�����token��
		if (ch == ' ' || ch == '\t' || ch == '\n')	//���Կո�Tab�ͻس�
		{
			if (ch == '\n')							//�������з�����¼������row��1
				row++;
			continue;								//����ִ��ѭ��
		}
		else if (isLetter(ch))			//����ĸ��ͷ���ؼ��ֻ��ʶ��
		{
			token = "";					//token��ʼ��
			while (isLetter(ch) || isDigit(ch))	//����ĸ������ʱ�˳��������ʴ洢��token��
			{
				token.push_back(ch);	//����ȡ���ַ�ch����token��
				ch = fgetc(fp);			//��ȡ��һ���ַ�
			}
			//�ļ�ָ�����һ���ֽڣ������¶�ȡ�������ʺ�ĵ�һ���ַ�
			fseek(fp, -1L, SEEK_CUR);
			if (isKey(token))	//�ؼ���
				code = Tokencode(getKeyID(token));
			else	//��ʶ��
				code = SYM_IDENT;	//����Ϊ��ʶ��
		}
		else if (isDigit(ch))	//�޷��ų��������ֿ�ͷ
		{
			int isdouble = 0;	//����Ƿ�Ϊ������
			token = "";			//token��ʼ��
			while (isDigit(ch))	//��ǰ��ȡ�����ַ�Ϊ����
			{
				token.push_back(ch);		//��ȡ���֣��������token��
				ch = fgetc(fp);				//���ļ��л�ȡ��һ���ַ�
				//�õ����е�һ�γ���С����
				if (ch == '.' && isdouble == 0)
				{
					//С������һλ������
					if (isDigit(fgetc(fp)))
					{
						isdouble = 1;		//��Ǹó������Ѿ����ֹ�С����
						fseek(fp, -1L, SEEK_CUR);		//����ǰ��ȡ��С�����һλ���¶�ȡ	
						token.push_back(ch);			//��С������token��
						ch = fgetc(fp);				//��ȡС��������һλ����
					}
				}
			}
			if (isdouble == 1)
				code = SYM_DOUBLE;	//����Ϊ������
			else
				code = SYM_INT;				//����Ϊ����
			//�ļ�ָ�����һ���ֽڣ������¶�ȡ������ĵ�һ���ַ�
			fseek(fp, -1L, SEEK_CUR);
		}
		else switch (ch)
		{
			/*�����*/
		case '+': code = SYM_PLUS;		//+�Ӻ�			
			break;
		case '-': code = SYM_MINUS;		//-����
			break;
		case '*': code = SYM_STAR;		//*�˺�		
			break;
		case '/': code = SYM_DIVIDE;		//����
			break;
		case '=':
		{
			ch = fgetc(fp);				//��ǰ��ȡ'='������ַ�
			if (ch == '=')				//==���ں�
			{
				token.push_back(ch);	//��'='�����'='����token��
				code = SYM_EQ;			//����Ϊ"=="
			}
			else {						//=��ֵ�����
				code = SYM_ASSIGN;		//����Ϊ"="
				fseek(fp, -1L, SEEK_CUR);	//����ǰ��ȡ���ַ����¶�ȡ
			}
		}
		break;
		case '<':
		{
			ch = fgetc(fp);				//��ǰ��ȡ'<'������ַ�
			if (ch == '=')				//<=С�ڵ��ں�
			{
				token.push_back(ch);	//��'<'�����'='����token��
				code = SYM_LEQ;			//����Ϊ"<="
			}
			else {						//<С�ں�
				code = SYM_LT;			//����Ϊ"<"
				fseek(fp, -1L, SEEK_CUR);	//����ǰ��ȡ���ַ����¶�ȡ
			}
		}
		break;
		case '>':
		{
			ch = fgetc(fp);				//��ǰ��ȡ'>'������ַ�
			if (ch == '=')				//>=���ڵ��ں�
			{
				token.push_back(ch);	//��'>'�����'='����token��
				code = SYM_GEQ;			//����Ϊ">="
			}
			else {						//>���ں�
				code = SYM_GT;			//����Ϊ">"
				fseek(fp, -1L, SEEK_CUR);	//����ǰ��ȡ���ַ����¶�ȡ
			}
		}
		break;
		case '!':
		{
			ch = fgetc(fp);				//��ǰ��ȡ'!'������ַ�
			if (ch == '=')				//!=�����ں�
			{
				token.push_back(ch);	//��'!'�����'='����token��
				code = SYM_UEQ;			//����Ϊ"!="
			}
			else {						
				code = SYM_UNDEF;			//����Ϊδʶ�����
				fseek(fp, -1L, SEEK_CUR);	//����ǰ��ȡ���ַ����¶�ȡ
			}
		}
		break;
		/*�ֽ��*/
		case '(': code = SYM_OPENPA;		//(��Բ����
			break;
		case ')': code = SYM_CLOSEPA;	//)��Բ����
			break;
		case '[': code = SYM_OPENBR;		//[��������
			break;
		case ']': code = SYM_CLOSEBR;	//]��������
			break;
		case '{': code = SYM_BEGIN;		//{�������
			break;
		case '}': code = SYM_END;		//}�Ҵ�����
			break;
		case ',': code = SYM_COMMA;		//,����
			break;
		case ';': code = SYM_SEMOCOLOM;	//;�ֺ�
			break;
			//δʶ�����
		default: code = SYM_UNDEF;
		}
		print(code);				
	}
}

int main()
{
	string filename;		//�ļ�·��
	FILE* fp;				//�ļ�ָ��
	cout << "*----������Դ�ļ���----*��" << endl;
	while (true) {
		cin >> filename;		//��ȡ�ļ�·��
		if ((fopen_s(&fp, filename.c_str(), "r")) == 0)		//���ļ�
			break;
		else
			cout << "·���������" << endl;	
	}
	cout << "/-------�ʷ��������-------/" << endl;
	lexicalAnalysis(fp);		//�ʷ�����
	fclose(fp);					//�ر��ļ�
	return 0;
}
