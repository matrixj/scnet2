#ifndef SCNET2_BASE_TIMESTAMP_H
#define SCNET2_BASE_TIMESTAMP_H

namespace scnet2
{
class Timerstamp : public scnet2::copyable,
                    public boost::less_than_compareable<Timestamp>
{ 
    public:
        explicit Timestamp(int64_t m);
        
        void swap(Timestamp& that)
        {
            std::swap(_ms, that._ms);
        };

        string toString() const;
}
}


#endif
