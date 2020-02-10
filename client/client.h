/* Copyright (C) 2020 Di Fan. All rights reserved. */
#ifndef CLIENT_CLIENT_H_
#define CLIENT_CLIENT_H_

#include <iostream>
#include <memory>
#include <string>

#include "absl/memory/memory.h"
#include "third_party/ibapi/EClientSocket.h"
#include "third_party/ibapi/EReader.h"
#include "third_party/ibapi/EReaderOSSignal.h"
#include "third_party/ibapi/EWrapper.h"

namespace experimental {
namespace dayfine {

class IbClient : public EWrapper {
 public:
  IbClient()
      : os_signal_(/*timeout=*/2000),
        socket_client_(absl::make_unique<EClientSocket>(this, &os_signal_)) {}
  ~IbClient() {}

  bool Connect(const std::string& host, int port, int client_id) {
    std::cout << "Connecting\n";
    bool ok = socket_client_->eConnect(host.c_str(), port, client_id,
                                       /*extraAuth=*/false);

    if (ok) {
      reader_ = absl::make_unique<EReader>(socket_client_.get(), &os_signal_);
      reader_->start();
      std::cout << "Connected and started Reader\n";
    }
    return ok;
  }

  bool IsConnected() const { return socket_client_->isConnected(); }

  // Process message received through Socket, where most work is done.
  void ProcessMessages();

 public:
// Include all the virtual methods of EWrapper that need to be implemented.
#include "third_party/ibapi/EWrapper_prototypes.h"

 private:
  EReaderOSSignal os_signal_;
  std::unique_ptr<EClientSocket> socket_client_;
  std::unique_ptr<EReader> reader_;
};

}  // namespace dayfine
}  // namespace experimental

#endif  // CLIENT_CLIENT_H_
