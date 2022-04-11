/* circularQ.c */

#include <stdio.h>//기본 입출력 함수
#include <stdlib.h>//라이브러리 함수

#define MAX_QUEUE_SIZE 4//MAX_QUEUE_SIZE = 4 입력

typedef char element;//char 를 별칭 element로 정의
typedef struct {//구조체 QueueType 생성
	element queue[MAX_QUEUE_SIZE];//char형 queue배열 4칸 생성
	int front, rear;//정수형 변수 2가지 생성
}QueueType;


QueueType *createQueue();//QueueType의 구조체*createQueue() 선언
int freeQueue(QueueType *cQ);//함수 freeQueue 선언
int isEmpty(QueueType *cQ);//함수 isEmpty 선언
int isFull(QueueType *cQ);//함수 isFull 선언
void enQueue(QueueType *cQ, element item);//함수 enQueue 선언
void deQueue(QueueType *cQ, element* item);//함수 deQueue 선언
void printQ(QueueType *cQ);//함수 printQ 선언
void debugQ(QueueType *cQ);//함수 debugQ 선언
element getElement();//element getElement() 선언


int main(void)
{
	printf("[----- [Lee hyeondo]  [2019038085] -----]\n");
	QueueType *cQ = createQueue();//구조체 cQ생성하고 초기화
	element data;//element형 변수 생성

	char command;//char형 변수 생성. 명령 입력받을때 사용

	do{//실행
		printf("\n-----------------------------------------------------\n");//메뉴 출력
		printf("                     Circular Q                   \n");
		printf("------------------------------------------------------\n");
		printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
		printf("------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);//Command 입력받음

		switch(command) {
		case 'i': case 'I'://i또는I면
			data = getElement();//함수 getElement()로 원소 입력받고 data에 저장
			enQueue(cQ, data);//생성한 큐에 입력
			break;//멈추기
		case 'd': case 'D'://d또는D면
			deQueue(cQ,&data);//원소 삭제
			break;//멈추기
		case 'p': case 'P'://p또는P면
			printQ(cQ);//큐 원소 출력
			break;//멈추기
		case 'b': case 'B'://b또는B면
			debugQ(cQ);//큐 디버그
			break;//멈추기
		case 'q': case 'Q'://q또는Q면
			break;//멈추기
		default://모두 아니면
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");//>>>>>   Concentration!!   <<<<<출력
			break;//멈추기
		}

	}while(command != 'q' && command != 'Q');//command가 q 또는 Q 가 아니면 다시 반복


	return 1;
}

QueueType *createQueue()//큐 생성
{
	QueueType *cQ;//구조체 *cQ생성
	cQ = (QueueType *)malloc(sizeof(QueueType));//cQ 동적할당//
	cQ->front = 0;//cQ.fornt = 0
	cQ->rear = 0;//cQ.rear = 0
	return cQ;//cq의 주소 리턴
}

int freeQueue(QueueType *cQ)//생성된 큐 메모리 해제 함수
{
    if(cQ == NULL) return 1;//만약 cQ가 NULL이면 리턴
    free(cQ);//아니면 메모리 해제
    return 1;//리턴
}

element getElement()//원소 받는 함수
{
	element item;//변수 item 생성
	printf("Input element = ");//Input element = 출력
	scanf(" %c", &item);//item 입력 받음
	return item;//item 리턴
}


int isEmpty(QueueType *cQ)//큐가 비어있을때 알려주는 함수
{
	if (cQ->front == cQ->rear){//cQ.front가 cq.rear 라면
		printf("Circular Queue is empty!");//Circular Queue is empty!출력
		return 1;//리턴 1
	}
	else return 0;//아니면 리턴 0 
}

int isFull(QueueType *cQ)//큐가 다 찼을때 알려주는 함수
{
	if (((cQ->rear+1)%MAX_QUEUE_SIZE) == cQ->front) {//만약 cQ의rear+1%4 가 cQ의front와 같을경우
		printf(" Circular Queue is full!");//Circular Queue is full! 출력
		return 1;
	}
	else return 0;//아니면 리턴 0
}

void enQueue(QueueType *cQ, element item)//큐에 입력받은 원소 넣는 함수
{
	if(isFull(cQ)) return;//만약 모두 차있다면 리턴
	else {//아니면
		cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE;//rear를 한칸 옮김. 3을 넘으면 0으로.
		cQ->queue[cQ->rear] = item;//큐의 한칸 옮긴 rear자리에 item입력
	}
}

void deQueue(QueueType *cQ, element *item)//큐의 원소 하나 삭제할때 사용하는 함수
{
	if(isEmpty(cQ)) return;//큐가 비어있으면 리턴
	else {//아니면
		cQ->front = (cQ->front + 1)%MAX_QUEUE_SIZE;//큐의 front를 한칸 옮김. 3을넘으면 0으로
		*item = cQ->queue[cQ->front];//cQ의 큐의 fornt를 item에다 넣음/////
		return;//리턴
	}
}


void printQ(QueueType *cQ)//큐 출력하는 함수
{
	int i, first, last;//변수 i,first,last생성

	first = (cQ->front + 1)%MAX_QUEUE_SIZE;//first = 큐의 fornt +1 %4
	last = (cQ->rear + 1)%MAX_QUEUE_SIZE;//last = 큐의 rear +1 %4

	printf("Circular Queue : [");//Circular Queue : 출력

	i = first;//i에 first입력
	while(i != last){//i 와 last가 같지 않는동안
		printf("%3c", cQ->queue[i]);//큐의 원소 출력
		i = (i+1)%MAX_QUEUE_SIZE;//(i+1)/4

	}
	printf(" ]\n");//괄호 닫기
}


void debugQ(QueueType *cQ)//큐 디버그 함수
{

	printf("\n---DEBUG\n");
	for(int i = 0; i < MAX_QUEUE_SIZE; i++)//i가 4보다 작은동안 반복
	{
		if(i == cQ->front) {//i가 cQ의 front와 같다면
			printf("  [%d] = front\n", i);//[%d] = front출력 %d는 i
			continue;//건너뛰기/////
		}
		printf("  [%d] = %c\n", i, cQ->queue[i]);//큐의 0부터 3까지 입력된 큐의 값 보여주기

	}
	
	printf("front = %d, rear = %d\n", cQ->front, cQ->rear);//front와 rear 보여주기
}


