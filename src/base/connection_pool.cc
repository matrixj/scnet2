ConnectionPoll:ConnectionPoll(int num)
  : num_(num),
    connPoll_(new vecotr(ConnectionPtr, )) {

  }

ConnectionPtr ConnectionPoll::getConnction() {
  return freeConn_.pop_back();
}

void ConnectionPoll::freeConnection(ConnectionPtr connPtr) {
  connPoll_.push_back(connPtr);
}
