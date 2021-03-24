#include <iostream>
#include<cstdlib>
#include<stdarg.h>
#include <omp.h>
#include <random>
using namespace std;

double          t_Start;       //таймер
double          t_Stop;

int main(int argc, char* argv[], char* envp[])   
{
	setlocale(LC_ALL, "Russian");   //понятия русского
	int tid = 0;                    //потоки
	const int n = 100000;           //значение перебра
	int a[n], b[n], res = 0;        //вектора с результатом

	for (int i = 0; i < n; i++)     //заполняется вектора
	{
		a[i] = rand();//1;
		b[i] = rand();//1;
	}

	t_Start = omp_get_wtime();      //включение таймера

#pragma omp parallel num_threads(4) private(tid) shared(res)
	{
		int numt = omp_get_num_threads(); //возвращает количество потоков  /  возвращает значение 1
		int locres = 0;             //счётчит решения if который обнуляется
		int kol = n / numt;         //разложение количество на потоки
		tid = omp_get_thread_num(); //возвращает номер потока в своей команде потока  /  возвращает 0
		if (tid < numt - 1)         //если потоков больше чем 0
			for (int i = 0; i < kol; i++)  
				locres += a[tid * kol + i] * b[tid * kol + i];

		else                        //если потоков небольше чем 0
			for (int i = 0; i < kol + n - kol * numt; i++)
				locres+= a[tid * kol + i] * b[tid * kol + i];
		res = res + locres;
	}

	t_Stop = omp_get_wtime() - t_Start;   //выключение таймера
	cout << res <<"\n"<< endl;            //вывод результат подщёта
	cout << "время=" << t_Stop << " секунд." << endl;   //вывод таймера

	system("pause");
	return 0;
}


