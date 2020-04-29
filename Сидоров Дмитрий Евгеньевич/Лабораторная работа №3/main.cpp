#include <iostream>

int hsh(int k, int s) {
    return k % s;
}

int num_k(int k, int* vx, int* s) { //return number of key, if find it in table
    int ke = hsh(k, *s);
    int i = ke;
    int sz = *s;
    while (sz > 0) {
        if (vx[i] == k) return i;
        else {
            i = (i + 1) % *s;
            sz--;
        }
    }
    return -1;
}

void del_k(int k, int* vx, int* s) { //delete by key
    int del_no = num_k(k, vx, s);
    if (del_no > 0) vx[del_no] = 0;
    else std::cout << "Didn't find key = " << k;
}

    int* add(int k, int* vx, int* s) {//s - размер массива hash table
    int ke = hsh(k, *s);          //vx - адрес первого элемента массива хэш таблицы
    int overfl = *s;              //
    int db_s = *s + *s;
                          //vv - указатель на массив для увеличенной хэш таблицы


    while (overfl and vx[ke] and vx[ke] != k)
    {
        ke = (ke + 1) % *s;
        overfl--;
    }
    if (overfl == 0)                //если вставлять некуда, то создаем увелич хэш таблицу
    {
        int* vv;
        vv = new int[db_s];         //выделяем память под новый удвоенный массив хэш таблицы

        for (int i = 0;i < db_s;i++) vv[i] = 0;
        for (int i = 0;i < *s;i++) add(vx[i], vv, &db_s);
        vx=add(k, vv, &db_s);
      //for (int i = 0;i < db_s;i++) std::cout << vv[i] << " ";
      //std::cout << std::endl;
        *s = db_s;
        //delete[] vx;

        vx = vv;    //записываем адрес нового увел массива вместо старого

      //for (int i = 0;i < db_s;i++) std::cout << vx[i] << " ";
      //std::cout << std::endl;

    }
    if (!vx[ke])  vx[ke] = k;
    return vx; // возрващаем либо старый адрес, либо новый увелич если заходили в if overfl
}



using namespace std;

int main()
{
    int sizeArr = 10;
    int x, kol;

    int* hTable;
    hTable = new int[sizeArr];

    /*add(15,v,u,&sizeArr);
    add(7,v,u,&sizeArr);
    add(42,v,u,&sizeArr);
    add(31,v,u,&sizeArr);
    add(12,v,u,&sizeArr);
    add(18,v,u,&sizeArr);
    add(34,v,u,&sizeArr);
    add(12,v,u,&sizeArr);
    add(36,v,u,&sizeArr);
    */
    for (int i = 0;i < sizeArr;i++) hTable[i] = 0;
    cout << "Enter num of elements to add >>>  ";
    cin >> kol;
    cout << "Enter list of " << kol << " values to add below" << endl;
    for (int i = 0;i < kol;i++) {
        cin >> x;
        hTable = add(x, hTable, &sizeArr);
    }

    for (int i = 0;i < sizeArr;i++) cout << hTable[i] << " ";

    cout << endl << "Enter value to delete >>   ";
    cin >> x;
    del_k(x, hTable, &sizeArr);

    for (int i = 0;i < sizeArr;i++) cout << hTable[i] << " ";

    delete [] hTable;

    return 0;
}
