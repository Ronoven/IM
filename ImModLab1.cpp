/* Сафронов Е.А., гр. 426-2, вариант 18.
Психолог в службе «Телефон доверия» ведет разговор с клиентами. Время между поступлениями 
звонков на разговор подчиняется равномерному закону распределения на интервале 20+-5 минут. 
Длительность разговора подчиняется экспоненциальному закону распределения и равно в среднем 
для 40% случаев 15 ми-нутам, а для 60% случаев – 25 минутам.
Известно, что клиент, услышавший «занято», бросает трубку.
Оценить, какой процент клиентов получает обслуживание, если служба работает  с 16 до 24 часов.
*/

#include "pch.h"
#include <iostream>
#include <ctime>
#include <cmath>

//Генератор случайных чисел от 0 до 1
float rand01()
{
	float r = (float) std::rand() / RAND_MAX;
	return r;
}

int main()
{
	std::srand(unsigned(std::time(0)));

	int iter;
    std::cout << "Please enter quantity of iteration\n";
	std::cin >> iter;

	//callAmount - счётчик поступивших звонков за всё время
	//putDownAmount - счётчик необслуженных звонков за всё время
	int callAmount = 0, putDownAmount = 0;
	//callArrival - время поступления звонка после начала раб.дня
	//operatorTime - переменная для отслеживания свободности психолога
	//(если callArrival > operatorTime, то звонок поступил после окончания
	//разговора с предыдущим звонившим, иначе линия занята)
	float callArrival, operatorTime;

	for (int i = 0; i < iter; ++i)
	{
		callArrival = 0;
		operatorTime = 0;
		
		while (1)
		{
			callArrival += rand01() * 10 + 15;
			if (callArrival > 480)
				break;
			++callAmount;
			
			if (callArrival > operatorTime)
			{
				if (rand01() < 0.4)
					operatorTime = callArrival - 15 * std::log(1 - rand01());
				else
					operatorTime = callArrival - 25 * std::log(1 - rand01());
			}
			else
				++putDownAmount;
		}
	}

	std::cout << "Average serving ratio = " << (1 - ((float) putDownAmount / callAmount)) * 100 << "%\n";
	system("pause");
}
