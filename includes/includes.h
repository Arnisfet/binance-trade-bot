//
// Created by arnisfet on 08.10.2022.
//

#ifndef BINANCE_TRADE_BOT_INCLUDES_H
#define BINANCE_TRADE_BOT_INCLUDES_H

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "binacpp.h"
#include "binacpp_websocket.h"
#include <json/json.h>

typedef struct s_struct
{
	std::string api_key;
	std::string secret_key;
    std::string tapi_key;
    std::string tsecret_key;
	std::vector<std::string> config;
} t_keys;

#endif //BINANCE_TRADE_BOT_INCLUDES_H
