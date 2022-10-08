//
// Created by arnisfet on 06.10.2022.
//

#include "includes.h"

std::string Remove_Space(std::string line)
{
	std::string::size_type begin;
	std::string::size_type end;
	int i = 0;

	while (1)
	{// Вырезаю хештеги к чертовой матери, их наличие усложняет алгоритм
		begin = line.find_first_of('#', 0);
		if (begin == std::string::npos)
			break ;
		end = line.find_first_of('\n', begin);
		line.erase(begin, end - begin);
	}
	/********* Заменяю все символы переноса на пробелы *********/
	while (line[i])
	{
		if (isspace(line[i]) && line[i] != ' ')
			line[i] = ' ';
		i++;
	}
	i = 0;
	/********* Убираю все лишние пробелы *********/
	while(line[i])
	{
		if (isspace(line[0]))
		{// Если в самом начале есть такой символ то вырезаем его нахуй
			line.erase(0, 1);
			continue;
		}
		if (isspace(line[i]) && isspace(line[i+1]))
		{// Основное условие для обработки пробела
			begin = i;
			end = line.find_first_not_of(line[i], begin);
			line.erase(begin, end - begin - 1);
			i = 0; continue;
		}
		i++;
	}
	return (line);
}

void Split_Tokens(std::string keys)
{
	std::string::size_type begin = 0;
	std::string::size_type end;
	std::string substr;
	t_keys pointer;
	int i = 0;

	begin = i;
	while (keys[i])
	{
		if (keys[i] == ' ')
		{
			substr = keys.substr(begin, i - begin);
			pointer.config.push_back(substr);
			begin = i + 1;
		}
		i++;
	}
}


int main ()
{

	std::string file_key;
	std::string keys;

	std::ifstream read("another/api_key");
	if (!read)
	{
		std::cerr << "File couldn't oppenning or reading!" << std::endl;
		exit (1);
	}
	while (getline(read, file_key))
		keys = keys + file_key + "\n";
	read.close();
	keys = Remove_Space(keys);
	Split_Tokens(keys);
//	string api_key 		= API_KEY;
//	string secret_key = SECRET_KEY;
//	BinaCPP::init( api_key , secret_key );
}