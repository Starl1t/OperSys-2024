//#include <iostream>
//#include <thread>
//#include <mutex>
//
//int global_variable = 0; // Глобальная переменная
//std::mutex mutex; // Мьютекс для блокировки доступа к глобальной переменной
//
//void increment_global(int id)
//{
//   for (int i = 0; i < 1000000; i++)
//   {
//      mutex.lock(); // Блокировка мьютекса перед изменением переменной
//      global_variable++;
//      mutex.unlock(); // Разблокировка мьютекса после изменения переменной
//   }
//   std::cout << "Thread " << id << " finished work." << std::endl;
//}
//
//int main()
//{
//   std::thread threads[4]; // Массив из 4 потоков
//
//   // Создание 4 потоков и запуск функции increment_global в каждом
//   for (int i = 0; i < 4; i++)
//   {
//      threads[i] = std::thread(increment_global, i);
//   }
//
//   // Ожидание завершения всех потоков
//   for (int i = 0; i < 4; i++)
//   {
//      threads[i].join();
//   }
//
//   std::cout << "Global var: " << global_variable << std::endl;
//
//   return 0;
//}