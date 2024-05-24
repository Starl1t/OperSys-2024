#include <iostream>
#include <thread>
#include <mutex>

int global_variable = 0; // Ãëîáàëüíàÿ ïåðåìåííàÿ
std::mutex mutex; // Ìüþòåêñ äëÿ áëîêèðîâêè äîñòóïà ê ãëîáàëüíîé ïåðåìåííîé

void increment_global(int id)
{
  for (int i = 0; i < 1000000; i++)
  {
     mutex.lock(); // Áëîêèðîâêà ìüþòåêñà ïåðåä èçìåíåíèåì ïåðåìåííîé
     global_variable++;
     mutex.unlock(); // Ðàçáëîêèðîâêà ìüþòåêñà ïîñëå èçìåíåíèÿ ïåðåìåííîé
  }
  std::cout << "Thread " << id << " finished work." << std::endl;
}

int main()
{
  std::thread threads[4]; // Ìàññèâ èç 4 ïîòîêîâ

  // Ñîçäàíèå 4 ïîòîêîâ è çàïóñê ôóíêöèè increment_global â êàæäîì
  for (int i = 0; i < 4; i++)
  {
     threads[i] = std::thread(increment_global, i);
  }

  // Îæèäàíèå çàâåðøåíèÿ âñåõ ïîòîêîâ
  for (int i = 0; i < 4; i++)
  {
     threads[i].join();
  }

  std::cout << "Global var: " << global_variable << std::endl;

  return 0;
}
