/* postfix.c */
#include<stdio.h>//표준 입출력 헤더 
#include<stdlib.h>//표준 라이브러리 함수
#include<ctype.h>//문자열비교 함수
#include<string.h>//문자열 처리함수

#define MAX_STACK_SIZE 10//스택 사이즈 10
#define MAX_EXPRESSION_SIZE 20//MAX_EXPRESSION_SIZE는 20 

/* stack 내에서 우선순위는 내림차순, lparen = 0 가장 낮음 */
typedef enum{//우선순위 정하는 구조체 precedence
	lparen = 0,  /* ( 왼쪽 괄호 */
	rparen = 9,  /* ) 오른쪽 괄호*/
	times = 7,   /* * 곱셈 */
	divide = 6,  /* / 나눗셈 */
	plus = 5,    /* + 덧셈 */
	minus = 4,   /* - 뺄셈 */
	operand = 1 /* 피연산자 */
} precedence;

char infixExp[MAX_EXPRESSION_SIZE];//infix형태 배열
char postfixExp[MAX_EXPRESSION_SIZE];//postfixExp 형태 배열
char postfixStack[MAX_STACK_SIZE];//postfixStack 형태 배열
int evalStack[MAX_STACK_SIZE];// int형 evalStack 배열

int postfixStackTop = -1;// postfixStackTop은 -1로 초기화
int evalStackTop = -1;//evalStackTop은 -1로 초기화

int evalResult = 0;//evalResult은 0로 초기화

void postfixPush(char x);//입력받은 토큰을 스택에 푸쉬하는 함수
char postfixPop();//스택에 있는 연산자 pop하는 함수
void evalPush(int x);//연산결과 스택에 토큰 푸쉬하는 함수
int evalPop();//연산결과 스택에 있는 값을 출력하는 함수
void getInfix();//infix expression을 입력받는 함수
precedence getToken(char symbol);//토큰의 타입과 문자 심볼 반환
precedence getPriority(char x);//우선사항 결정 함수
void charCat(char* c);//문자열 추가 함수
void toPostfix();//포스트 픽스 변환 함수
void debug();//디버그 함수
void reset();//초기화 함수
void evaluation();//계산 함수

int main()
{
	char command;//커멘드 입력 변수 생성
	printf("[----- [Lee hyeondo]  [2019038085] -----]\n");

	do{//while 조건에 따라 반복
		printf("----------------------------------------------------------------\n");//메뉴 출력
		printf("               Infix to Postfix, then Evaluation               \n");
		printf("----------------------------------------------------------------\n");
		printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//커멘드 입력받기

		switch(command) {//커멘드에 따라 
		case 'i': case 'I'://i혹은 I이면
			getInfix();//infix받는 함수 호출
			break;//종료
		case 'p': case 'P'://p혹은 P이면
			toPostfix();//postfix로 변환하는 함수 호출
			break;//종료
		case 'e': case 'E'://e혹은 E이면
			evaluation();//계산하는 함수 호출
			break;//종료
		case 'd': case 'D'://d혹은 D이면
			debug();//디버그로 상태 보여주는 함수 호출
			break;//종료
		case 'r': case 'R'://r혹은 R이면
			reset();//초기화 함수 호출
			break;//종료
		case 'q': case 'Q'://q혹은 Q이면
			break;//종료
		default://해당되는게 없으면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//>>>>>   Concentration!!   <<<<<<출력
			break;//종료
		}

	}while(command != 'q' && command != 'Q');//q혹은Q가 아니면 다시 반복

	return 1;


}

void postfixPush(char x)//입력받은 토큰을 스택에 푸쉬하는 함수
{
    postfixStack[++postfixStackTop] = x;//스택의 top을 ++하고 그 위치에 x값 입력
}

char postfixPop()//스택에 있는 연산자 pop하는 함수
{
	char x;//char 형 변수 생성
    if(postfixStackTop == -1)//만약 스택의 탑이 -1이면
        return '\0';//리턴
    else {//아니면
    	x = postfixStack[postfixStackTop--];//스택의 탑 x로 입력하고 스택의 탑 --
    }
    return x;//리턴 x
}

void evalPush(int x)//연산결과 스택에 토큰 푸쉬하는 함수
{
    evalStack[++evalStackTop] = x;//evalStack[++evalStackTop]에 x값 입력
}

int evalPop()//연산결과 스택에 있는 값을 출력하는 함수
{
    if(evalStackTop == -1)//evalStackTop이 -1이면
        return -1;//리턴 -1 
    else//아니면
        return evalStack[evalStackTop--];//evalStack의 탑 리턴 후 --
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */

void getInfix()//infix expression을 입력받는 함수
{
    printf("Type the expression >>> ");//Type the expression >>>출력
    scanf("%s",infixExp);//infixExp 입력
}

precedence getToken(char symbol)//토큰의 타입과 문자 심볼 반환
{
	switch(symbol) {//심볼이
	case '(' : return lparen;//(면 return lparen
	case ')' : return rparen;//)면 return rparen
	case '+' : return plus;//+ 면 return plus
	case '-' : return minus;//-면 return minus
	case '/' : return divide;// /면  return divide
	case '*' : return times;//*면  return times
	default : return operand;//모두 아니면 오퍼랜드.
	}
}

precedence getPriority(char x)//우선사항 결정 함수
{
	return getToken(x);//리턴 getToken
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c)//문자열 추가 함수
{
	if (postfixExp == '\0')//postfixExp가 \0이면
		strncpy(postfixExp, c, 1);//문자 c 를 복사하여 postfixExp에 입력
	else
		strncat(postfixExp, c, 1);//postfixExp에 문자 c 추가
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix()//포스트 픽스 변환 함수
{
	/* infixExp의 문자 하나씩을 읽기위한 포인터 */
	char *exp = infixExp;
	char x; /* 문자하나를 임시로 저장하기 위한 변수 */

	/* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
	while(*exp != '\0')//infixExp가 0이 아닌 동안
	{
		if(getPriority(*exp) == operand)//문자가 오퍼렌드라면
		{
			x = *exp;//문자 x에 입력
        	charCat(&x);//postfixExp에 문자 추가. 바로출력
		}
        else if(getPriority(*exp) == lparen) {//문자가 왼쪽 괄호라면

        	postfixPush(*exp);//스택으로 푸쉬
        }
        else if(getPriority(*exp) == rparen)//문자가 오른쪽 괄호라면
        {
        	while((x = postfixPop()) != '(') {//왼괄호가 나올때까지 x 출력
        		charCat(&x);//postfixExp에 문자 추가//
        	}
        }
        else//아니면
        {
            while(getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))//postfixStack의 탑에 있는 값이 getPriority(*exp)  보다 크면
            {
            	x = postfixPop();//x = 먼저 pop
            	charCat(&x);//문자열 추가
            }
            postfixPush(*exp);//스택의 값보다 exp가 크면 푸쉬
        }
        exp++;//exp++ 다음칸 이동
	}

    while(postfixStackTop != -1)//postfixStackTop 이 -1 이 아니면
    {
    	x = postfixPop();//x 모두 출력. postfixStackTop이 -1 이 될때까지 1씩 빼주지만 스택에 입력되어있던 연산자들은 쓰레기 값으로 남아 있음.
    	charCat(&x);//x 모두 postfixExp에 추가
    }

}

void debug()//디버그 함수
{
	printf("\n---DEBUG\n");//---DEBUG 출력
	printf("infixExp =  %s\n", infixExp);//infixExp = 인픽스 출력
	printf("postExp =  %s\n", postfixExp);//postExp =  포스트 픽스 출력
	printf("eval result = %d\n", evalResult);//eval result = 계산값 출력

	printf("postfixStack : ");//postfixStack : 출력
	for(int i = 0; i < MAX_STACK_SIZE; i++)//스텍 크기만큼 반복
		printf("%c  ", postfixStack[i]);//스택모두 출력. 남아있는 연산자들 쓰레기 값으로 출력됨.

	printf("\n");

}

void reset()//초기화 함수
{
	infixExp[0] = '\0';//infixExp[0]에 \0 입력
	postfixExp[0] = '\0';//postfixExp[0]에 \0 입력

	for(int i = 0; i < MAX_STACK_SIZE; i++)//스택 크기만큼 반복
		postfixStack[i] = '\0';//스택 모두 0으로 초기화
         
	postfixStackTop = -1;//포스트 스택 탑 값 -1
	evalStackTop = -1;//evalStackTop 값 -1 
	evalResult = 0;//evalResult 값 0
}

void evaluation()//계산 함수
{
	int opr1, opr2, i;//변수 3개 생성

	int length = strlen(postfixExp);//길이 변수에 postfixExp의 길이 입력
	char symbol;//문자열 하나씩 받을 변수 생성
	evalStackTop = -1;//evalStackTop은 -1 

	for(i = 0; i < length; i++)//postfixExp 문자열의 길이 만큼 반복
	{
		symbol = postfixExp[i];//postfixExp의 문자 하나씩 심볼에 입력
		if(getToken(symbol) == operand) {//심볼이 오퍼랜드면
			evalPush(symbol - '0');//문자이므로 48빼고 푸쉬
		}
		else {//아니면
			opr2 = evalPop();//스택 삭제
			opr1 = evalPop();//스택 삭제
			switch(getToken(symbol)) {//심볼이
			case plus: evalPush(opr1 + opr2); break;//플러스면 opr1 + opr2하여 푸쉬
			case minus: evalPush(opr1 - opr2); break;//마이너스면opr1 - opr2하여 푸쉬
			case times: evalPush(opr1 * opr2); break;//곱하기면 opr1 * opr2하여 푸쉬
			case divide: evalPush(opr1 / opr2); break;//나누기면 opr1/opr2하여 푸쉬
			default: break;//모두 아니면 종료
			}
		}
	}
	evalResult = evalPop();//결과 출력
}

