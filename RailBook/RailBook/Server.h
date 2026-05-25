#pragma once
#include "RailBookApp.h"

// Porneste serverul TCP pe portul dat
// Blocheaza thread-ul curent — apelat din main()
void runServer(RailBookApp& app, int port = 1234);