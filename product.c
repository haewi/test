#include "product.h"

Product* products[MAX_PRODUCT];     // 레코드
int _count = 0;                     // 현재 저장된 제품 수

// -------함수-------
void p_input_filename(char* file){
	FILE* f;
	char n[20];
	int pr, sn, pc, lc;
	f = fopen(file, "r");

	while(!feof(f)){
		int result = fscanf(f, "%s %d %d %d %d", n, &pr, &sn, &pc, &lc);
		if(result<1) break;

	#ifdef DEBUG
	printf("[DEBUG 1] (read file) file scaned : %s\n", n);
	#endif
		if(p_search_name(n)==NULL){
			p_create(n, pr, sn, pc, lc);
		}
	
	#ifdef DEBUG
	printf("[DEBUG 2] (read file) created %s's info\n", n);
	#endif
	}

	fclose(f);
} // 데이터 파일을 읽어 들여 레코드에 저장

int p_file_count(char* file){
	FILE* f;
	char n[20];
	int p, sn, s, pc, lc, pf;
	int count=0;

	f = fopen(file, "r");
	
	while(!feof(f)){
		int result = fscanf(f, "%s %d %d %d %d %d %d", n, &p, &sn, &s, &pc, &lc, &pf);
		if(result<1) break;
	
	#ifdef DEBUG
	printf("[DEBUG 3] (file count) file scaned : %s\n", n);
	#endif

		count++;
	}
	fclose(f);
	#ifdef DEBUG
	printf("[DEBUG 4] (file count) Reading the number of products in the data file is finished\n");
	#endif

	return count;
} // 데이터 파일에 있는 제품 수 리턴

// void p_file_to_record(){

// }

int p_available(int n){
	if(MAX_PRODUCT-_count >= n){
	#ifdef DEBUG
	printf("[DEBUG 5] (available) There is space for the data\n");
	#endif
		return 1;
	}
	return 0;
} // n개의 데터 저장할 수 있는 공간 있는지 리턴

int p_first_index(){
    for(int i=0; i<MAX_PRODUCT; i++){
        if(products[i]==NULL){
            return i;
        }
    }
    return -1;
} // 레코드에서 비어있는 첫번째 공간의 인덱스 리턴

Product* p_search_name(char* name){
	for(int i=0; i<MAX_PRODUCT; i++){
		if((products[i]!=NULL) && strcmp(products[i]->name, name)==0){
			return products[i];
		}
	}
	#ifdef DEBUG
	printf("[DEBUG 6] (search name) No product with the name %s\n", name);
	#endif

	return NULL;
} // 제품명이 name인 제품이 있으면 리턴 없으면 NULL 리턴

void p_create(char* name, int price, int saleNum, int prime, int labor){
	int index = p_first_index();
	int sales, profit;
	
	products[index] = (Product*) malloc(sizeof(Product));
	Product* p = products[index];

	#ifdef DEBUG
	printf("[DEBUG 7] (create) mallocation finished\n");
	#endif

	sales = price*saleNum;
	profit = sales - (labor + prime)*saleNum;

	strcpy(p->name, name);
	p->price = price;
	p->saleNum = saleNum;
	p->sales = sales;
	p->primeCost = prime;
	p->laborCost = labor;
	p->profit = profit;

	#ifdef DEBUG
	printf("[DEBUG 8] (create) creating the product %s finished\n", name);
	#endif

	_count++;
} // 레코드에 정보 저장      

int p_count(){
    return _count;
} // 저장된 제품 수 리턴

void p_get_all(Product* a[]){
	int count=0;
	for(int i=0; i<MAX_PRODUCT; i++){
		if(products[i]!=NULL){
			a[count] = products[i];
			count++;
	#ifdef DEBUG
	printf("[DEBUG 9] (get all) %s's info added\n", products[i]->name);
	#endif
		}
	}
} // 저장된 모든 레코드 정보 리턴

char* p_to_string(Product* a){
	static char str[200];
	sprintf(str, "%s\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d", a->name, a->price, a->saleNum, a->sales, a->primeCost, a->laborCost, a->profit);

	#ifdef DEBUG
	printf("[DEBUG 10] (to string) turning %s's info to string finished\n", a->name);
	#endif

	return str;
} // 레코드 정보 문자열로 리턴

// void p_update(Product* p, int price, int amount, int sales, int prime, int labor, int profit){
    
// }

// int p_all_profit(){
    
// }

// void p_delete(Product* p){
    
// }

// int* p_sort_profit(){
    
// }

