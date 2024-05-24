#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> global_variable = 0; // ��������� ����������

void increment_global(int id)
{
   for (int i = 0; i < 1000000; i++)
   {
      global_variable++;
   }
   std::cout << "Thread " << id << " finished work." << std::endl;
}

int main()
{
   std::thread threads[4]; // ������ �� 4 �������

   // �������� 4 ������� � ������ ������� increment_global � ������
   for (int i = 0; i < 4; i++)
   {
      threads[i] = std::thread(increment_global, i);
   }

   // �������� ���������� ���� �������
   for (int i = 0; i < 4; i++)
   {
      threads[i].join();
   }

   std::cout << "Global var: " << global_variable << std::endl;

   return 0;
}