#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
using namespace std;

void delete_word(char arr1[1000000][20], char arr2[100000][20], int &arr1_size, int &arr2_size){
    for(int i=0; i<arr1_size; i++){
        for(int j=0; j<arr2_size; j++){
            if(strcmp(arr1[i], arr2[j]) == 0){
                for(int k=i; k<arr1_size; k++){
                    strcpy(arr1[k], arr1[k+1]);
                }
                arr1_size--;
                i--;
            }
        }
    }
}

void remove_duplicate(char arr[1000000][20], int &arr_size){
    for(int i=0; i<arr_size; i++){
        for(int j=i+1; j<arr_size; j++){
            if(strcmp(arr[i], arr[j]) == 0){
                for(int k=i; k<arr_size; k++){
                    strcpy(arr[k], arr[k+1]);
                }
                arr_size--;
                i--;
            }
        }
    }
}

bool smaller(char input[1000000][20], int a_index, int b_index) {
    char* a = input[a_index];
    char* b = input[b_index];
    for (int i = 0; a[i] != 0 && b[i] != 0; i++) {
        if (a[i] > b[i]) {
            return false;
        } else if (a[i] < b[i]){
            return true;
        }
    }
    return true;
}

void swap(char input[1000000][20], int a, int b) {
    for(int i = 0; i < 20; i++){
        char temp = input[a][i];
        input[a][i] = input[b][i];
        input[b][i] = temp;
    }
}

void sort(char input[1000000][20], int size){
    char temp;
    for(int k = 0; k < size; k++){
        for(int i = k + 1; i < size; i++){
            if (smaller(input, i, k)) {
                swap(input, i, k);
            }
        }
    }
}

int main()
{
    auto str1 = new char [1000000][20];
    ifstream myfile("alice30.txt");
    char ch;
    int str1_size=0;
    while (myfile >> noskipws >> ch){
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z') || ch == '.')
        {
            strncat(str1[str1_size], &ch, 1);
        }
        else if(str1[str1_size][0] != NULL)
        {
            str1_size++;
        }
    }

    auto str2 = new char [100000][20];
    int str2_size=0;
    ifstream myfile2("stopw.txt");
    while(myfile2 >> noskipws >> ch){
        if((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'))
        {
            strncat(str2[str2_size], &ch, 1);
        }
        else if(str2[str2_size][0] != NULL)
        {
            str2_size++;
        }
    }

    int str3_size = 0;
    auto str3 = new char [1000000][20];
    int j=0;
    for(int i=1; i<str1_size; i++)
    {
        if(isupper(str1[i][0]))
        {
            if(str1[i-1][(strlen(str1[i-1])-1)] != '.'){
                strcpy(str3[j], str1[i]);
                j++;
                str3_size++;
            }
        }
    }

    delete_word(str1, str3, str1_size, str3_size);

    for(int i=0; i<str1_size; i++){
        if(strcmp(str1[i],".") == 0){
            for(int k=i+1; k<str1_size; k++){
                strcpy(str1[k-1], str1[k]);
            }
            str1_size--;
        }

        if(str1[i][(strlen(str1[i])-1)] == '.'){
            str1[i][(strlen(str1[i])-1)] = str1[i][(strlen(str1[i]))];
        }
    }

    for(int i=0; i<str1_size; i++){
        for(int j=0; j<strlen(str1[i]); j++){
            str1[i][j] = tolower(str1[i][j]);
        }
    }

    delete_word(str1, str2, str1_size, str2_size);
    sort(str1, str1_size);
    remove_duplicate(str1, str1_size);

    auto index_table = new int [1000000][20];
    int index_table_size = 0;
    for(int i=0; i<str1_size; i++){
        ifstream file("alice30.txt");
        string line;
        transform(line.begin(), line.end(), line.begin(), ::tolower);
        int line_counter = 0;
        int word_counter = 0;
        while (getline(file, line)){
            line_counter++;
            if (line.find(str1[i]) != string::npos) {
                index_table[index_table_size][word_counter+1] = line_counter;
                word_counter++;
            }
        }
        index_table[index_table_size][0] = word_counter;
        index_table_size++;
    }
    int word=0;
    for(int j=0; j<index_table_size; j++){
        cout << str1[word] << " ";
        cout << index_table[j][0];
        for(int k=1; k<(index_table[j][0]+1); k++){
            cout << "," << index_table[j][k];
        }
        word++;
        cout << endl;
    }

    return 0;
}
