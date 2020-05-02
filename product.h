#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCT 100		//최대 저장 가능한 제품 정보

// 제품 정보 데이터 타입
typedef struct{
	char name[20];		// 제품명
	int price;		// 가격
	int saleNum;		// 판매개수
	int sales;		// 매출액
	int primeCost;		// 원가
	int laborCost;		// 인건비
	int profit;		// 이윤
} Product;

// 함수 원형
void p_input_filename(char* file);	// 데이터 파일 이름 저장
int p_file_count(char* file);		// 데이터 파일에 저장된 제품 수 리턴
int p_available(int n);			// 현재 n개의 정보만큼 추가할 수 있는 데이터 공간이 있는가? 있으면 1 없으면 0
int p_first_index();			// 비어있는 첫 인덱스 리턴
Product* p_search_name(char* name);	// 정보가 존재하는 제품인지, 있다면 그 정보 리턴, 없다면 NULL 리턴
void p_create(char* name, int price, int saleNum, int prime, int labor);	// 레코드에 정보 추가
int p_count();				// 존재하는 제품 개수 리턴
void p_get_all(Product* a[]);		// 모든 제품 정보 가져오기
char* p_to_string(Product* a);		// 제품 정보를 문자열로 만들기
void p_update(Product* p, int price, int saleNum, int prime, int labor);	// 제품 정보 업데이트
void p_report();			// 보고서 파일 작성
void p_delete(Product* p);		// 제품 정보 삭제
void p_save_file(Product* p);		// 제품 정보 파일에 저장
void p_sort_profit();			// 높은 이윤 순서대로 레코드 정보 정렬
void p_change_record(int x, int y);	// x와 y를 인덱스로 갖는 제품들의 정보를 바꿈
