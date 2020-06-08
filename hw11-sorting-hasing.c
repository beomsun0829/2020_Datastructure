/*
 * hw5-sorting.c
 *
 *  Created on: May 22, 2019
 *
 *  Homework 5: Sorting & Hashing
 *  Department of Computer Science at Chungbuk National University
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ARRAY_SIZE			13	/* prime number */
#define MAX_HASH_TABLE_SIZE 	MAX_ARRAY_SIZE

 /* 필요에 따라 함수 추가 가능 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
/* recursive function으로 구현 */
int quickSort(int *a, int n);


/* hash code generator, key % MAX_HASH_TABLE_SIZE */
int hashCode(int key);

/* array a에대 한 hash table을 만든다. */
int hashing(int *a, int **ht);

/* hash table에서 key를 찾아 hash table의 index return */
int search(int *ht, int key);


int main()
{
	char command;
	int *array = NULL;
	int *hashtable = NULL;
	int key = -1;
	int index = -1;

	srand(time(NULL));
	initialize(&array);
	printf("---2019038058 hongbeomsun---\n");

	do {
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initialize(&array);
			break;
		case 'q': case 'Q':
			freeArray(array);
			break;
		case 's': case 'S':
			selectionSort(array);
			break;
		case 'i': case 'I':
			insertionSort(array);
			break;
		case 'b': case 'B':
			bubbleSort(array);
			break;
		case 'l': case 'L':
			shellSort(array);
			break;
		case 'k': case 'K':
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
			printArray(array);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initialize(int** a)			//배열할당/초기화
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if (*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE;		//0부터 MAX_ARRAY_SIZE-1까지 랜덤숫자 생성

	return 0;
}

int freeArray(int *a)
{
	if (a != NULL)
		free(a);
	return 0;
}

void printArray(int *a)
{
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}


int selectionSort(int *a)
{
	int min;			//최솟값
	int minindex;		//최솟값 배열index(위치찾기용으로 사용)
	int i, j;			//반복문에 쓸것

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)			//arrsize만큼 반복(전체탐색)
	{
		minindex = i;
		min = a[i];
		for (j = i + 1; j < MAX_ARRAY_SIZE; j++)		//정렬된 다음부분부터 배열의끝까지 순차탐색,
		{											//최솟값을 저장하여 i와 바꾸면 순서대로 정렬이된다.
			if (min > a[j])
			{
				min = a[j];
				minindex = j;						//더 작은경우 minindex에 저장
			}										//for문이 끝나게되면 minindex에는 j가 돌았던 곳 중 가장작은 배열의 값이 들어있음
		}
		a[minindex] = a[i];							//swap
		a[i] = min;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 1; i < MAX_ARRAY_SIZE; i++)
	{
		t = a[i];									//i번째 배열을 선택
		j = i;
		while (a[j - 1] > t && j > 0)					//j가 감소하는 for문과 동일, 조건을위해 while사용
		{
			a[j] = a[j - 1];							//원소를 하나씩 앞으로 땡김(오른차순)
			j--;									//위치가 정확하면 while문이 탈출될것, 탐색인덱스j 감소
		}
		a[j] = t;
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 1; j < MAX_ARRAY_SIZE; j++)						//기본적으로 이중for문 사용
		{
			if (a[j - 1] > a[j])										//이중for문 내에서 큰 수를 뒤로보내기
			{
				t = a[j - 1];
				a[j - 1] = a[j];
				a[j] = t;
			}
		}															//안쪽for문이 끝나면 큰 원소가 뒤로 정렬됨
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int shellSort(int *a)				//삽입정렬을 보완, 삽입정렬이 어느정도 정렬된 배열에 효율적이라는것에 착안
{									//삽입정렬의 문제점 : 요소들의 삽입될때 이웃한 위치로 이동
	int i, j, k, h, v;				//즉 삽입위치가 먼 거리면 많은 이동을 거쳐야 하므로 비효율적
									//부분리스트를 만들고 각 부분리스트를 삽입정렬을 이용하여 정렬
	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (h = MAX_ARRAY_SIZE / 2; h > 0; h /= 2)				//부분리스트 생성을 위한 for문 (부분리스트는 비연속적)
	{														//초기 부분리스트 간격은 MAX_ARRAY_SIZE의 절반, GAP을 두배씩 감소시키며 정렬
		for (i = 0; i < h; i++)								//삽입정렬
		{
			for (j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j];
				k = j;
				while (k > h - 1 && a[k - h] > v)
				{
					a[k] = a[k - h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1)
	{
		v = a[n - 1];			//피벗 선택
		i = -1;
		j = n - 1;

		while (1)
		{
			while (a[++i] < v);		//피벗보다 작은 값 찾기
			while (a[--j] > v);		//피벗보다 큰 값 찾기

			if (i >= j) break;		//i>=j일경우 while문 탈출
			t = a[i];				//오른쪽과 왼쪽 값 swap
			a[i] = a[j];
			a[j] = t;
		}
		t = a[i];			//피벗값과 i번째 값 변환
		a[i] = a[n - 1];
		a[n - 1] = t;

		quickSort(a, i);			//a ~ i(변환한곳) 까지 다시 부분리스트 만들어서 quicksort 진행(재귀)
		quickSort(a + i + 1, n - i - 1);
	}


	return 0;
}

int hashCode(int key) {
	return key % MAX_HASH_TABLE_SIZE;
}

int hashing(int *a, int **ht)
{
	int *hashtable = NULL;

	/* hash table이 NULL인 경우 메모리 할당 */
	if (*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	}
	else {
		hashtable = *ht;	/* hash table이 NULL이 아닌경우, table 재활용, reset to -1 */
	}

	for (int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/

	int key = -1;
	int hashcode = -1;
	int index = -1;
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i];
		hashcode = hashCode(key);
		/*
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		if (hashtable[hashcode] == -1)			//해시테이블에 할당되어있지 않다면
		{
			hashtable[hashcode] = key;			//제산함수를 통해 계산한 index에 key넣기
		}
		else {								//해시테이블에 이미 할당이 되어있는경우

			index = hashcode;

			while (hashtable[index] != -1)				//index를 점차 증가시키면서 hashtable이 비어있는(-1)인 곳까지 탐색. 배열의 끝에 닿으면 0으로 초기화
			{
				index = (++index) % MAX_HASH_TABLE_SIZE;
				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key;
		}
	}

	return 0;
}

int search(int *ht, int key)
{
	int index = hashCode(key);		//search를 하게 될경우, hash를 사용하여 이미 table을 만들어놓았기 때문에 똑같은 알고리즘으로 검색만 하면 된다

	if (ht[index] == key)
		return index;

	while (ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}
	return index;
}



