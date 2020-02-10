/* Copyright (C) 2020 Di Fan. All rights reserved. */
#include "client/client.h"

#include <chrono>
#include <set>
#include <thread>
#include <vector>

#include "absl/strings/str_format.h"

namespace experimental {
namespace dayfine {

void requstAccountInfo(EClientSocket* client) {
  auto wait_time = std::chrono::seconds(2);

  client->reqManagedAccts();
  std::this_thread::sleep_for(wait_time);

  client->reqAccountSummary(9001, "All", "$LEDGER:ALL");
  std::this_thread::sleep_for(wait_time);
  client->cancelAccountSummary(9001);
  std::this_thread::sleep_for(wait_time);

  client->reqPositions();
  std::this_thread::sleep_for(wait_time);
  client->cancelPositions();
}

void IbClient::ProcessMessages() {
  requstAccountInfo(socket_client_.get());
  os_signal_.waitForSignal();
  reader_->processMsgs();
}

// Implementation of EWrapper virtual methods.
// Actually 'implemented'.
void IbClient::accountSummary(int reqId, const std::string& account,
                              const std::string& tag, const std::string& value,
                              const std::string& currency) {
  std::cout << absl::StrFormat(
      "Acct Summary. ReqId: %d, Account: %s, Tag: %s, Value: %s, "
      "Currency: %s\n",
      reqId, account, tag, value, currency);
}

void IbClient::position(const std::string& account, const Contract& contract,
                        double position, double avgCost) {
  std::cout << absl::StrFormat(
      "Position. %s - Symbol: %s, SecType: %s, Currency: %s, Position: %g, Avg "
      "Cost: %g\n",
      account, contract.symbol, contract.secType, contract.currency, position,
      avgCost);
}

// Not really 'implemented'.
void IbClient::tickPrice(TickerId tickerId, TickType field, double price,
                         const TickAttrib& attrib) {}
void IbClient::tickSize(TickerId tickerId, TickType field, int size) {}
void IbClient::tickOptionComputation(TickerId tickerId, TickType tickType,
                                     double impliedVol, double delta,
                                     double optPrice, double pvDividend,
                                     double gamma, double vega, double theta,
                                     double undPrice) {}
void IbClient::tickGeneric(TickerId tickerId, TickType tickType, double value) {
}
void IbClient::tickString(TickerId tickerId, TickType tickType,
                          const std::string& value) {}
void IbClient::tickEFP(TickerId tickerId, TickType tickType, double basisPoints,
                       const std::string& formattedBasisPoints,
                       double totalDividends, int holdDays,
                       const std::string& futureLastTradeDate,
                       double dividendImpact, double dividendsToLastTradeDate) {
}
void IbClient::orderStatus(OrderId orderId, const std::string& status,
                           double filled, double remaining, double avgFillPrice,
                           int permId, int parentId, double lastFillPrice,
                           int clientId, const std::string& whyHeld,
                           double mktCapPrice) {}
void IbClient::openOrder(OrderId orderId, const Contract&, const Order&,
                         const OrderState&) {}
void IbClient::openOrderEnd() {}
void IbClient::winError(const std::string& str, int lastError) {}
void IbClient::connectionClosed() {}
void IbClient::updateAccountValue(const std::string& key,
                                  const std::string& val,
                                  const std::string& currency,
                                  const std::string& accountName) {}
void IbClient::updatePortfolio(const Contract& contract, double position,
                               double marketPrice, double marketValue,
                               double averageCost, double unrealizedPNL,
                               double realizedPNL,
                               const std::string& accountName) {}
void IbClient::updateAccountTime(const std::string& timeStamp) {}
void IbClient::accountDownloadEnd(const std::string& accountName) {}
void IbClient::nextValidId(OrderId orderId) {}
void IbClient::contractDetails(int reqId,
                               const ContractDetails& contractDetails) {}
void IbClient::bondContractDetails(int reqId,
                                   const ContractDetails& contractDetails) {}
void IbClient::contractDetailsEnd(int reqId) {}
void IbClient::execDetails(int reqId, const Contract& contract,
                           const Execution& execution) {}
void IbClient::execDetailsEnd(int reqId) {}
void IbClient::error(int id, int errorCode, const std::string& errorString) {}
void IbClient::updateMktDepth(TickerId id, int position, int operation,
                              int side, double price, int size) {}
void IbClient::updateMktDepthL2(TickerId id, int position,
                                const std::string& marketMaker, int operation,
                                int side, double price, int size,
                                bool isSmartDepth) {}
void IbClient::updateNewsBulletin(int msgId, int msgType,
                                  const std::string& newsMessage,
                                  const std::string& originExch) {}
void IbClient::managedAccounts(const std::string& accountsList) {}
void IbClient::receiveFA(faDataType pFaDataType, const std::string& cxml) {}
void IbClient::historicalData(TickerId reqId, const Bar& bar) {}
void IbClient::historicalDataEnd(int reqId, const std::string& startDateStr,
                                 const std::string& endDateStr) {}
void IbClient::scannerParameters(const std::string& xml) {}
void IbClient::scannerData(int reqId, int rank,
                           const ContractDetails& contractDetails,
                           const std::string& distance,
                           const std::string& benchmark,
                           const std::string& projection,
                           const std::string& legsStr) {}
void IbClient::scannerDataEnd(int reqId) {}
void IbClient::realtimeBar(TickerId reqId, long time, double open, double high,
                           double low, double close, long volume, double wap,
                           int count) {}
void IbClient::currentTime(long time) {}
void IbClient::fundamentalData(TickerId reqId, const std::string& data) {}
void IbClient::deltaNeutralValidation(
    int reqId, const DeltaNeutralContract& deltaNeutralContract) {}
void IbClient::tickSnapshotEnd(int reqId) {}
void IbClient::marketDataType(TickerId reqId, int marketDataType) {}
void IbClient::commissionReport(const CommissionReport& commissionReport) {}
void IbClient::positionEnd() {}
void IbClient::accountSummaryEnd(int reqId) {}
void IbClient::verifyMessageAPI(const std::string& apiData) {}
void IbClient::verifyCompleted(bool isSuccessful,
                               const std::string& errorText) {}
void IbClient::displayGroupList(int reqId, const std::string& groups) {}
void IbClient::displayGroupUpdated(int reqId, const std::string& contractInfo) {
}
void IbClient::verifyAndAuthMessageAPI(const std::string& apiData,
                                       const std::string& xyzChallange) {}
void IbClient::verifyAndAuthCompleted(bool isSuccessful,
                                      const std::string& errorText) {}
void IbClient::connectAck() {}
void IbClient::positionMulti(int reqId, const std::string& account,
                             const std::string& modelCode,
                             const Contract& contract, double pos,
                             double avgCost) {}
void IbClient::positionMultiEnd(int reqId) {}
void IbClient::accountUpdateMulti(int reqId, const std::string& account,
                                  const std::string& modelCode,
                                  const std::string& key,
                                  const std::string& value,
                                  const std::string& currency) {}
void IbClient::accountUpdateMultiEnd(int reqId) {}
void IbClient::securityDefinitionOptionalParameter(
    int reqId, const std::string& exchange, int underlyingConId,
    const std::string& tradingClass, const std::string& multiplier,
    const std::set<std::string>& expirations, const std::set<double>& strikes) {
}
void IbClient::securityDefinitionOptionalParameterEnd(int reqId) {}
void IbClient::softDollarTiers(int reqId,
                               const std::vector<SoftDollarTier>& tiers) {}
void IbClient::familyCodes(const std::vector<FamilyCode>& familyCodes) {}
void IbClient::symbolSamples(
    int reqId, const std::vector<ContractDescription>& contractDescriptions) {}
void IbClient::mktDepthExchanges(
    const std::vector<DepthMktDataDescription>& depthMktDataDescriptions) {}
void IbClient::tickNews(int tickerId, time_t timeStamp,
                        const std::string& providerCode,
                        const std::string& articleId,
                        const std::string& headline,
                        const std::string& extraData) {}
void IbClient::smartComponents(int reqId, const SmartComponentsMap& theMap) {}
void IbClient::tickReqParams(int tickerId, double minTick,
                             const std::string& bboExchange,
                             int snapshotPermissions) {}
void IbClient::newsProviders(const std::vector<NewsProvider>& newsProviders) {}
void IbClient::newsArticle(int requestId, int articleType,
                           const std::string& articleText) {}
void IbClient::historicalNews(int requestId, const std::string& time,
                              const std::string& providerCode,
                              const std::string& articleId,
                              const std::string& headline) {}
void IbClient::historicalNewsEnd(int requestId, bool hasMore) {}
void IbClient::headTimestamp(int reqId, const std::string& headTimestamp) {}
void IbClient::histogramData(int reqId, const HistogramDataVector& data) {}
void IbClient::historicalDataUpdate(TickerId reqId, const Bar& bar) {}
void IbClient::rerouteMktDataReq(int reqId, int conid,
                                 const std::string& exchange) {}
void IbClient::rerouteMktDepthReq(int reqId, int conid,
                                  const std::string& exchange) {}
void IbClient::marketRule(int marketRuleId,
                          const std::vector<PriceIncrement>& priceIncrements) {}
void IbClient::pnl(int reqId, double dailyPnL, double unrealizedPnL,
                   double realizedPnL) {}
void IbClient::pnlSingle(int reqId, int pos, double dailyPnL,
                         double unrealizedPnL, double realizedPnL,
                         double value) {}
void IbClient::historicalTicks(int reqId,
                               const std::vector<HistoricalTick>& ticks,
                               bool done) {}
void IbClient::historicalTicksBidAsk(
    int reqId, const std::vector<HistoricalTickBidAsk>& ticks, bool done) {}
void IbClient::historicalTicksLast(int reqId,
                                   const std::vector<HistoricalTickLast>& ticks,
                                   bool done) {}
void IbClient::tickByTickAllLast(int reqId, int tickType, time_t time,
                                 double price, int size,
                                 const TickAttribLast& tickAttribLast,
                                 const std::string& exchange,
                                 const std::string& specialConditions) {}
void IbClient::tickByTickBidAsk(int reqId, time_t time, double bidPrice,
                                double askPrice, int bidSize, int askSize,
                                const TickAttribBidAsk& tickAttribBidAsk) {}
void IbClient::tickByTickMidPoint(int reqId, time_t time, double midPoint) {}
void IbClient::orderBound(long long orderId, int apiClientId, int apiOrderId) {}
void IbClient::completedOrder(const Contract& contract, const Order& order,
                              const OrderState& orderState) {}
void IbClient::completedOrdersEnd() {}

}  // namespace dayfine
}  // namespace experimental
