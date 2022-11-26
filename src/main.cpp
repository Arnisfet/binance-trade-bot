//
// Created by arnisfet on 06.10.2022.
//

#include "includes.h"
std::map < string, map <string,double> >  userBalance;
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

void Split_Tokens(std::string keys, t_keys *pointer)
{
	std::string::size_type begin = 0;
	std::string::size_type end;
	std::string substr;
	int i = 0;
/********* Бью все данные из конфига на токены по пробелам и кладу в вектор, ничего сложного *************/
	begin = i;
	while (keys[i])
	{
		if (keys[i] == ' ')
		{
			substr = keys.substr(begin, i - begin);
			pointer->config.push_back(substr);
			begin = i + 1;
		}
		i++;
	}
}

/************** Мэппинг по значениям из вектора внутрь структуры ********************/
void MakeConstruction(t_keys *pointer)
{
	auto begin = pointer->config.begin();
	auto end = pointer->config.end();
	for (; begin != end; begin++)
	{
		if (*begin == "api_key:")
			pointer->api_key = *(begin + 1);
		else if (*begin == "secret_key:")
			pointer->secret_key = *(begin + 1);
        else if (*begin == "tapi_key:")
            pointer->tapi_key = *(begin + 1);
        else if (*begin == "tsecret_key:")
            pointer->tsecret_key = *(begin + 1);
	}
}



void print_userBalance() {

    map < string, map<string,double> >::iterator it_i;

    cout << "==================================" << endl;

    for ( it_i = userBalance.begin() ; it_i != userBalance.end() ; it_i++ ) {

        string symbol 			= (*it_i).first;
        map <string,double> balance 	= (*it_i).second;

        cout << "Symbol :" << symbol << ", ";
        printf("Free   : %.08f, ", balance["f"] );
        printf("Locked : %.08f " , balance["l"] );
        cout << " " << endl;

    }

}

int main ()
{

	std::string file_key;
	std::string keys;
	t_keys pointer;
    Json::Value result;
    long recvWindow = 10000;

	std::ifstream read("another/api_key");
	if (!read)
	{
		std::cerr << "File couldn't oppenning or reading!" << std::endl;
		exit (1);
	}
	while (getline(read, file_key))
		keys = keys + file_key + "\n";
	read.close();
	keys = Remove_Space(keys);  // минус лишние невидимые символы
	Split_Tokens(keys, &pointer); // Бьем на токены
	MakeConstruction(&pointer); //
	BinaCPP::init( pointer.tapi_key, pointer.tsecret_key );
//    double bnbeth_price = BinaCPP::get_price( "BNBETH");
//    std::cout << bnbeth_price;

    BinaCPP::get_account( recvWindow , result );
    for ( int i  = 0 ; i < result["balances"].size() ; i++ ) {
        string symbol = result["balances"][i]["asset"].asString();
        userBalance[symbol]["f"] = atof( result["balances"][i]["free"].asString().c_str() );
        userBalance[symbol]["l"] = atof( result["balances"][i]["locked"].asString().c_str() );
    }
    print_userBalance();
}