#include "product.h"

//함수 원형
void bringInfo();
void createInfo();
void readInfo();
void listInfo();
void makeReport();
void printProfit();
void updateInfo();
void deleteInfo();
void saveInfo();
void sortByProfit();

int main(){
	int menu;
	while(1){
		printf("\nMenu : 1.Bring 2.Create 3.Read 4.List 5.Make Report 6.Total Profit 7.Update 8.Delete 9.Save 10.Sort(By Profit) 0.Quit > ");
		scanf("%d", &menu);
		printf("\n");
		switch(menu){
			case 1:
				bringInfo();
				break;
			case 2:
				createInfo();
				break;
			case 3:
				readInfo();
				break;
			case 4:
				listInfo();
				break;
			case 5:
				makeReport();
				break;
			case 6:
				printProfit();
				break;
			case 7:
				updateInfo();
				break;
			case 8:
				deleteInfo();
				break;
			case 9:
				saveInfo();
				break;
			case 10:
				sortByProfit();
				break;
			case 0:
			default:
				return 0;	
		}
	}
	return 0;
}

void bringInfo(){
	char filename[50];

	printf("Filename? :");
	scanf("%s", filename);
	
	int n = p_file_count(filename);

	if(!p_available(n)){
		printf("There is not enough space in the record to bring all info from the file!\n");
		return;
	}
	p_input_filename(filename);
}

void createInfo(){
	if(!p_available(1)){
		printf("There is not enough space!\n");
		return;
	}

	char name[20];
	int price, saleNum, primeCost, laborCost;

	printf("Enter a new product information\n");
	printf("Name? ");
	scanf("%*c");
	fgets(name, 20, stdin);
	name[strlen(name)-1] = '\0';

	if(p_search_name(name)!=NULL){
		printf("Duplicated name!\n");
		return;
	}

	printf("Price? ");
	scanf("%d", &price);
	printf("Number of sales? ");
	scanf("%d", &saleNum);
	printf("Prime cost? ");
	scanf("%d", &primeCost);
	printf("Labor cost? ");
	scanf("%d", &laborCost);

	p_create(name, price, saleNum, primeCost, laborCost);
}

void readInfo(){
	char name[20];
	Product* p;

	printf("Name? ");
	scanf("%*c");
	fgets(name, 20, stdin);
	name[strlen(name)-1] = '\0';
	
	p = p_search_name(name);
	if(p==NULL){
		printf("There is no product!\n");
		return;
	}

	printf("Name : %s\n", p->name);
	printf("Price : %d\n", p->price);
	printf("Number of sales : %d\n", p->saleNum);
	printf("Sales : %d\n", p->sales);
	printf("Prime cost : %d\n", p->primeCost);
	printf("Labor cost : %d\n", p->laborCost);
	printf("Profit : %d\n", p->profit);
}

void listInfo(){
	printf("All products\n");
	printf("Name\t\t\tPrice\t\tSale Number\tSales\t\t Prime Cost\tLabor Cost\tProfit\n");
	int size = p_count();
	Product* a[MAX_PRODUCT];

	p_get_all(a);
	for(int i=0; i<size; i++){
		printf("%d. %s\n", i+1, p_to_string(a[i]));
	}
}

void makeReport(){
	Product* a[MAX_PRODUCT];
	int size = p_count();
	char file[50], name[20];
	printf("filename? :");
	scanf("%s%*c", file);
	printf("Reporter? :");
	fgets(name, 20, stdin);

	FILE* f = fopen(file, "w");
	fprintf(f, "\t\t\t\t\tProduct Report\n");
	fprintf(f, "\t\t\t\t\t\b----------------\n\n");
	fprintf(f, "Number of products : %d\n", size);
	fprintf(f, "Reporter : %s\n\n", name);
	fprintf(f, "Contents\n");
	fprintf(f, "Name\t\t\tPrice\t\tSale Number\tSales\t\t Prime Cost\tLabor Cost\tProfit\n");
	fprintf(f, "-----------------------------------------------------------------------------------------------------------------\n");
	p_get_all(a);

	for(int i=0; i<size; i++){
		fprintf(f, "%d. %s\n", i+1, p_to_string(a[i]));
	}
	fclose(f);
	printf("Report created!\n");
}

void printProfit(){
	Product* a[MAX_PRODUCT];
	p_get_all(a);
	int size = p_count(), total=0;

	for(int i=0; i<size; i++){
		total += a[i]->profit;
	}

	printf("The Sum of Profit of All Products : %d\n", total);
}

void updateInfo(){
	char name[20];
	int price, saleNum, primeCost, laborCost;
	printf("Enter a name : ");
	scanf("%*c");
	fgets(name, 20, stdin);
	name[strlen(name)-1] = '\0';
	
	Product* p = p_search_name(name);
	
	if(p){
		printf("Price? ");
		scanf("%d", &price);
		printf("Number of sales? ");
		scanf("%d", &saleNum);
		printf("Prime cost? ");
		scanf("%d", &primeCost);
		printf("Labor cost? ");
		scanf("%d", &laborCost);

		p_update(p, price, saleNum, primeCost, laborCost);
	}   
	else{
		printf("No such product!\n");
	}
}

void deleteInfo(){
	char name[20];
	printf("Enter a name: ");
	scanf("%*c");
	scanf("%s", name);

	Product *p = p_search_name(name);
	if(p){
		p_delete(p);
		printf("Product is deleted.\n");
	}else{
		printf("No such product!\n");
	}
}

void saveInfo(){
	Product* a[MAX_PRODUCT];
	p_get_all(a);
	int size = p_count();
	FILE* f = fopen("new_data.txt", "w");

	for(int i=0; i<size; i++){
		fprintf(f, "%d %d %d %d %s\n", a[i]->price, a[i]->saleNum, a[i]->primeCost, a[i]->laborCost, a[i]->name);
	}
}

void sortByProfit(){
	p_sort_profit();
	printf("Records are sorted by profit!\n");
}





