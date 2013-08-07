#ifndef SCNET2_BASE_TIMESTAMP_H
#define SCNET2_BASE_TIMESTAMP_H

#include <base/copyable.h>

#include <boost/operators.hpp>

namespace scnet2 {
class Timestamp : public scnet2::copyable,
                   public boost::less_than_comparable<Timestamp> { 
    public:
        explicit Timestamp(int64_t t);
       /* 
        void swap(Timestamp& that)
        {
            std::swap(_ms, that._ms);
        };

        */
        //string toString() const;

        Timestamp();
        int64_t microSecondsSinceEpoch() const {
            return _microSecondsSinceEpoch;
        }
        
        static Timestamp now();
        static Timestamp invalid();

        static const int microSecondsPersecond = 1000000;
    private:
        int64_t _microSecondsSinceEpoch;
};
inline bool operator<(Timestamp l, Timestamp r) { 
  return l.microSecondsSinceEpoch()  < r.microSecondsSinceEpoch();
}

inline bool operator==(Timestamp l, Timestamp r) {
  return l.microSecondsSinceEpoch() == r.microSecondsSinceEpoch();
}

inline Timestamp addTime(Timestamp ts, double s) {
  int64_t t = static_cast<int64_t>(s * Timestamp::microSecondsPersecond);
  return Timestamp(ts.microSecondsSinceEpoch() + t);
}
}


#endif
