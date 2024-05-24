#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <vector>
#include <mutex>
#include <algorithm>
#include <iostream>

typedef struct File 
{
	std::string name;
	std::string data;
	int size;

	std::mutex file_mt;
} File;

class FileSystem
{
	std::vector<File*> files;

public:
	FileSystem();
	~FileSystem();

	File* searchFile(std::string name);
	void createFile(std::string name);
	void readFile(std::string name);
	void writeFile(std::string name, std::string data);
	void deleteFile(std::string name);
	void printFsInfo();
};

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
	for (auto it = files.begin(); it < files.end(); ++it)
	{
		delete((*it));
	}

	files.clear();
}

File* FileSystem::searchFile(std::string name)
{
	for (auto it = files.begin(); it < files.end(); ++it)
	{

		if ((*it)->name == name)
		{
			return *it;
		}

	}

	return nullptr;
}

void FileSystem::createFile(std::string name)
{
	if (searchFile(name) != nullptr) // Если файл с таким именем существует, то выход
	{
		std::cout << "File with name " << name << " already exist" << std::endl;
		return;
	}

	// Создание файла и блокировка доступа к нему, во время записи начальных данных
	File* newFile = new File; 

	newFile->file_mt.lock(); 
	
	newFile->name = name;
	newFile->size = 0;
	newFile->data = "";

	newFile->file_mt.unlock();

	files.push_back(newFile);
}

void FileSystem::readFile(std::string name)
{
	File* file = searchFile(name);

	if (file == nullptr) // Файла с таким именем не существует
	{
		std::cout << "File " << name << " does not exist" << std::endl;
		return;
	}

	file->file_mt.lock();

	std::cout << "File " << name << " data: " << file->data << std::endl;

	file->file_mt.unlock();

}

void FileSystem::writeFile(std::string name, std::string data)
{
	File* file = searchFile(name);

	if (file == nullptr) // Файла с таким именем не существует
	{
		std::cout << "File " << name << " does not exist" << std::endl;
		return;
	}

	file->file_mt.lock();

	file->data = data;
	file->size = data.size();

	file->file_mt.unlock();

}

void FileSystem::deleteFile(std::string name)
{
	for (auto it = files.begin(); it < files.end(); ++it)
	{

		if (it == files.end())
		{
			std::cout << "File " << name << " does not exist" << std::endl;
			return;
		}
		else if ((*it)->name == name)
		{
			delete((*it));
			files.erase(it);

			return;
		}
	}
}

void FileSystem::printFsInfo()
{
	std::cout << "FS STATS:" << std::endl;
	std::cout << "Number of files: " << files.size() << std::endl;

	for (auto it = files.begin(); it < files.end(); ++it)
	{
		File* file = *it;

		std::cout << "File " << file->name << " size: " << file->size << std::endl;
	}
}


int main()
{
	FileSystem fs;
	fs.createFile("Mister");
	fs.createFile("Mersedes");
	fs.createFile("Mark Zuckerberg");
	fs.printFsInfo();

	std::cout << std::endl;

	fs.writeFile("Mister", "Beast");
	fs.writeFile("Mersedes", "SLS McLaren");
	fs.writeFile("Mark Zuckerberg", "Nice job team");
	fs.readFile("Mister");
	fs.readFile("Mersedes");
	fs.readFile("Mark Zuckerberg");
	std::cout << std::endl;
	fs.printFsInfo();

	std::cout << std::endl;

	fs.createFile("Mister");
	fs.writeFile("Rudge", "Masters");
	fs.deleteFile("Rudge");

	std::cout << std::endl;

	fs.deleteFile("Mister");
	fs.printFsInfo();

	std::cout << std::endl;

	fs.deleteFile("Mark Zuckerberg");
	fs.printFsInfo();

	std::cout << std::endl;

	fs.deleteFile("Mersedes");
	fs.printFsInfo();

	return 0;
}