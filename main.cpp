#include <iostream>
#include <ctime>
#include <fstream>
#include <cstdlib>

std::ifstream fin("date_de_intrare.txt");

int v[100000000], c[100000000], counts[100000000], TIMP;   ///100 de milioane
clock_t timpStart, now, timpFinal;

void generare_vector(int a[], int len, int maxi)
{
    srand((int)time(0));
    for (int i=0; i<len; i++)
        a[i] = rand() % maxi + 1;
}

void print(int a[], int len)
{
    for (int i=0; i<len; i++)
        std::cout<<a[i]<<" ";
}

bool verif(int a[], int len)
{
    for (int i=0; i<len-1; i++)
        if (a[i]>a[i+1])
            return false;

    return true;
}

void copyArr(int a[], int b[], int len)
{
    for (int i=0; i<len; i++)
        b[i]=a[i];
}



void bubbleSort(int a[], int len)
{

    bool ok = true;
    while(ok)
    {
        ok = false;
        now = clock();
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
        {
            for (int i=0; i<len-1; i++)
                if (a[i]>a[i+1])
                {
                    int aux = a[i];
                    a[i]=a[i+1];
                    a[i+1] = aux;
                    ok = true;
                }
        }
        else
            TIMP = 0;
    }
}



void countSort(int a[], int len, int maxi)
{
    int Size ;

    for (int i=0; i<=maxi; i++)
        counts[i] = 0;

    now = clock();
    for(int i = 0; i < len; i++)
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
            counts[a[i]]++;
        else
            TIMP = 0;

    now = clock();
    Size = 0;
    for(int i = 0; i <= maxi; i++)
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
            for(int j = 0; j < counts[i]; j++)
                a[Size++] = i;
        else
            TIMP = 0;
}



void countRadix(int a[], int len, int exp)
{
    int counts[10]={0}, output[len];

    for (int i=0; i<len; i++)
        counts[(a[i]/exp)%10] ++;

    for (int i=1; i<10; i++)
        counts[i] += counts[i-1];

    for (int i=len-1; i>=0; i--)
    {
        output[counts[(a[i]/exp)%10] - 1] = a[i];
        counts[(a[i]/exp)%10] --;
    }

    for (int i=0; i<len; i++)
        a[i]=output[i];

}

int getMax(int a[], int len)
{
    int maxi = a[0];
    for (int i=1; i<len; i++)
        if (a[i] > maxi)
            maxi = a[i];
    return maxi;
}

void radixSort(int a[], int len)
{
    int maxi = getMax(a,len);
    for (int exp=1; maxi/exp > 0; exp *= 10)
    {
        now = clock();
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
            countRadix(a,len,exp);
        else
            TIMP = 0;
    }
}

void Merge(int a[], int left, int m, int right)
{
    int temp[right-left+1];
    int i=left, j=m+1, k=0;
    while(i<=m && j<=right)
    {
        if (a[i]<=a[j])
        {
            temp[k]=a[i];
            k++; i++;
        }
        else
        {
            temp[k]=a[j];
            k++; j++;
        }
    }

    while(i<=m)
    {
        temp[k]=a[i];
        k++; i++;
    }

    while(j<=right)
    {
        temp[k]=a[j];
        k++; j++;
    }

    for (i=left; i<=right; i++)
        a[i]=temp[i-left];

}
void mergeSort(int a[], int left, int right)
{
    if (left < right)
    {
        int m;

        m=(left+right)/2;
        mergeSort(a,left,m);
        mergeSort(a,m+1,right);

        now = clock();
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
            Merge(a,left,m,right);
    }

}


void Swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partit(int low, int high)
{
    int pivot = c[high];
    int i = low-1;

    for (int j = low; j < high; j++)
    {
        if (c[j] <= pivot)
        {
            i++;
            Swap(&c[i], &c[j]);
        }
    }
    Swap(&c[i+1], &c[high]);
    return i+1;
}

void quickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = partit(low, high);

        now = clock();
        if ((now - timpStart) / (double)CLOCKS_PER_SEC < 0.5)
        {
            quickSort(low, pivot-1);
            quickSort(pivot+1, high);
        }
    }
}

int main()
{
    int nrTeste, len, maxi;
    double duration;

    fin >> nrTeste;
    for (int it=0; it<nrTeste; it++)
    {
        std::cout<<"Testul "<<it+1<<":\n";
        fin >> len >> maxi;

        generare_vector(v,len,maxi);

///BUBBLESORT:
        std::cout<<"BubbleSort: ";
        copyArr(v,c,len);

        TIMP = 1;
        timpStart = clock();
        bubbleSort(c,len);
        timpFinal = clock();


        duration = (timpFinal - timpStart) / (double)CLOCKS_PER_SEC;
        if (TIMP == 1)
        {
            if (verif(c,len))
                std::cout<<"-- YES -- "<<duration<<"\n";
            else
                std::cout<<"-- NO SORT -- \n";
        }
        else
            std::cout<<"-- NO TIME -- \n";

///COUNTSORT:
        std::cout<<"CountSort: ";
        copyArr(v,c,len);

        TIMP = 1;

        timpStart = clock();
        countSort(c,len,maxi);
        timpFinal = clock();

        duration = (timpFinal - timpStart) / (double)CLOCKS_PER_SEC;
        if (TIMP == 1)
        {
            if (verif(c,len))
                std::cout<<" -- YES -- "<<duration<<"\n";
            else
                std::cout<<" -- NO SORT -- \n";
        }
        else
            std::cout<<" -- NO TIME -- \n";

///RADIXSORT:
        std::cout<<"RadixSort: ";
        copyArr(v,c,len);

        TIMP = 1;
        timpStart = clock();
        radixSort(c,len);
        timpFinal = clock();

        duration = (timpFinal - timpStart) / (double)CLOCKS_PER_SEC;
        if (TIMP == 1)
        {
            if (verif(c,len))
                std::cout<<" -- YES -- "<<duration<<"\n";
            else
                std::cout<<" -- NO SORT -- \n";
        }
        else
            std::cout<<" -- NO TIME -- \n";



///MERGESORT:
        std::cout<<"MergeSort: ";
        copyArr(v,c,len);

        TIMP = 1;
        timpStart = clock();
        mergeSort(c,0,len-1);
        timpFinal = clock();

        duration = (timpFinal - timpStart) / (double)CLOCKS_PER_SEC;
        if (TIMP == 1)
        {
            if (verif(c,len))
                std::cout<<" -- YES -- "<<duration<<"\n";
            else
                std::cout<<" -- NO SORT -- \n";
        }
        else
            std::cout<<" -- NO TIME -- \n";

///QUICKSORT:
        std::cout<<"QuickSort: ";
        copyArr(v,c,len);

        TIMP = 1;
        timpStart = clock();
        quickSort(0,len-1);
        timpFinal = clock();

        duration = (timpFinal - timpStart) / (double)CLOCKS_PER_SEC;

        if (TIMP == 1)
        {
            if (verif(c,len))
                std::cout<<" -- YES -- "<<duration<<"\n";
            else
                std::cout<<" -- NO SORT -- \n";
        }
        else
            std::cout<<" -- NO TIME -- \n";

        std::cout<<"\n\n";

    }

    return 0;
}

