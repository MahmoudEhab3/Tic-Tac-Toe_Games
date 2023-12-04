// File: A3_S1_20220037_Problem4.cpp
// Purpose: Set immplemntation
// Author: Ahmed Elkholy
// Section: S1
// ID: 20220037
// TA: Khaled Ibrahim

#include <bits/stdc++.h>
using namespace std;
template<class T>
class Set{
private:
    int size,cnt;
    T *arr;
public:
    Set(){
        size=5;cnt=0;
        arr= new T [size];
    }

    void insert(T x){
        if(cnt==size){
            Expand();
        }
        if(check(x)==-1){
            arr[cnt]=x;
            cnt++;
            for(int i=0; i<cnt; i++)
                for(int j=0; j<cnt-1; j++)
                    if(arr[j]>arr[j+1])
                        swap(arr[j],arr[j+1]);
        }
    }

    void erase(T x){
        if(check(x)!=-1){
            for(int i = check(x);i<cnt;i++){
                arr[i]=arr[i+1];
            }
            cnt--;
        }
    }

    int Size(){
        return cnt;
    }

    T* toArray() {
        T* array = new T[cnt];
        for (int i = 0; i < cnt; i++) {
            array[i] = arr[i];
        }
        return array;
    }

    void Expand(){
        size*=2;
        T*temp=new T [size];
        for(int i=0;i<cnt;i++){
            temp[i]=arr[i];
        }
        delete [] arr;
        arr=temp;
    }

    int check(T x){
        for(int i=0;i<cnt;i++){
            if(arr[i]==x){
                return i;
            }
        }
        return -1;
    }

    ~Set(){
        delete [] arr;
    }
};


int main() {

    Set<int> s1;
    s1.insert(20);
    s1.insert(10);
    s1.insert(5);
    s1.insert(5);
    s1.insert(1);
    s1.insert(9);
    s1.erase(20);

    cout << "Size of set: " << s1.Size() << endl;
    cout << "Contains 10: " << s1.check(10) << endl;

    int* arr = s1.toArray();

    for (int i = 0; i < s1.Size(); i++) {
        cout << arr[i] << " ";
    }

    return 0;
}
