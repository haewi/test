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
void seeReport();
void sortByName();
void selectUpdate();

int main(){
	int menu;
	while(1){
		printf("\n\t\t--Menu--\n\t1.Bring\t\t\t2.Create\t\t3.Read\n\t4.List\t\t\t5.Make Report\t\t6.Total Profit\n\t7.Update\t\t8.Delete\t\t9.Save\n\t10.Sort(By Profit)\t11.See Report\t\t12.Sort(By Name)\n\t13.Selected Update\t0.Quit\n");
		printf("\n\t\t\t\t\t\t\tChoice : ");
		scanf("%d%*c", &menu);
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
			case 11:
				seeReport();
				break;
			case 12:
				sortByName();
				break;
			case 13:
				selectUpdate();
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

void seeReport(){
	char file[50], str[200];

	printf("filename? :");
	scanf("%s%*c", file);

	FILE* f = fopen(file, "r");
	
	printf("The %s report is...\n\n", file);

	while(!feof(f)){
		if(fgets(str, 200, f)==NULL) break;
		
		printf("%s", str);
	}
}

void sortByName(){
	p_sort_name();
	printf("Records are sorted by name!\n");
}


void selectUpdate(){
	char name[20];
	printf("Enter a name : ");
	//scanf("%*c");
	fgets(name, 20, stdin);
	name[strlen(name)-1] = '\0';
	printf("%s\n", name);
	Product* p = p_search_name(name);

	if(p==NULL){
		printf("There is no product!\n");
		return;
	}
	
	int choice;
	printf("Choose what you want to update\n");
	printf("\n\t\t--Menu--\n\t1.Name \t\t\t2.Price \t\t3.Sale Number\n\t4.Prime Cost\t\t5.labor Cost\t\t0.Quit\n");
	printf("\n\t\t\t\t\t\t\tChoice : ");
	scanf("%d%*c", &choice);

	switch(choice){
		case 1:
			p_change_name(p);
			break;
		case 2:
			p_change_price(p);
			break;
		case 3:
			p_change_saleNum(p);
			break;
		case 4:
			p_change_prime(p);
			break;
		case 5:
			p_change_labor(p);
		default:
			break;
	}
}








