//#include <iostream>
//#include <thread>
//#include <mutex>
//
//int global_variable = 0; // ���������� ����������
//std::mutex mutex; // ������� ��� ���������� ������� � ���������� ����������
//
//void increment_global(int id)
//{
//   for (int i = 0; i < 1000000; i++)
//   {
//      mutex.lock(); // ���������� �������� ����� ���������� ����������
//      global_variable++;
//      mutex.unlock(); // ������������� �������� ����� ��������� ����������
//   }
//   std::cout << "Thread " << id << " finished work." << std::endl;
//}
//
//int main()
//{
//   std::thread threads[4]; // ������ �� 4 �������
//
//   // �������� 4 ������� � ������ ������� increment_global � ������
//   for (int i = 0; i < 4; i++)
//   {
//      threads[i] = std::thread(increment_global, i);
//   }
//
//   // �������� ���������� ���� �������
//   for (int i = 0; i < 4; i++)
//   {
//      threads[i].join();
//   }
//
//   std::cout << "Global var: " << global_variable << std::endl;
//
//   return 0;
//}