/* Copyright (C) 2020 Di Fan. All rights reserved. */

#include <chrono>
#include <iostream>
#include <thread>

#include "client/client.h"

constexpr int kSleepTime = 5;

int main(int argc, char** argv) {
  while (true) {
    std::cout << "Creating a client\n";
    experimental::dayfine::IbClient client;

    std::cout << "Trying to connect...\n";
    client.Connect("", /*port=*/7496, /*client_id*/ 1);

    while (client.IsConnected()) {
      std::cout << "Processing Messages...\n";
      client.ProcessMessages();
    }
    std::this_thread::sleep_for(std::chrono::seconds(kSleepTime));
  }
}
