//
// Created by khalidzhang on 2019/12/6.
//

#include "common_includes.h"
#include "dyn_aspect.hpp"
#include "tower_aoi.h"
#include "time_gap.hpp"

//    /**
//     *
//     * @tparam NumberT
//     * @tparam PayloadT
//     */
//    template<typename NumberT, typename PayloadT>
//    class ObjectT
//    {
//    public:
//        typedef NumberT Number;
//        typedef PayloadT Payload;
//
////        Point<Number> pos{};
//    private:
//        Payload payload;
//        uint8_t type;
//    public:
//        ObjectT() = default;
//
//        ObjectT(const Payload &_p, uint8_t _t) : payload(_p), type(_t)
//        {
//
//        }
//
//        friend bool operator==(const ObjectT<NumberT, PayloadT> &lhs, const ObjectT<NumberT, PayloadT> &rhs)
//        {
////            return lhs.payload == rhs.payload && lhs.type == rhs.type;
//            return lhs.payload == rhs.payload;      //id相等就因该相等，
//
//        }
//
//        friend bool operator<(const ObjectT<NumberT, PayloadT> &lhs, const ObjectT<NumberT, PayloadT> &rhs)
//        {
//            return lhs.payload < rhs.payload;
//        }
//
//    public:
//        void SetPayload(const Payload &p)
//        {
//            payload = p;
//        }
//
//        Payload GetPayload()
//        {
//            return payload;
//        }
//
//        void SetType(uint8_t _t)
//        {
//            type = _t;
//        }
//
//        uint8_t GetType()
//        {
//            return type;
//        }
//    };


typedef TowerAoi::TowerT<int, int> Tower;
typedef Tower::Point Point;
typedef Tower::Object Object;

#define AOPCALL(call) (AOP<bool,TimeElapsedAspect,LoggingAspect>([&]()->bool{ return (call);}))
Tower *ptower{};

struct TimeElapsedAspect
{
    void Before(...)
    {
    }

    void After(...)
    {
        INFO("time Use: " << m_t.gap())
    }

private:
    TimeGap m_t;
};

struct LoggingAspect
{
    void Before(...)
    {
        std::ostringstream oss;
        oss<<"Before:\t";
        ptower->ToString(oss);
        INFO(oss.str())
    }

    void After(...)
    {
        std::ostringstream oss;
        oss<<"After:\t";
        ptower->ToString(oss);
        INFO(oss.str())
    }
};

TEST(dev_tower, 1)
{
    int type = 1;
    Tower tower(0, Point(0, 0));
    ptower = &tower;

    INFO("ret: "<<AOPCALL(tower.Add(0, Point(0, 0), type)))
    INFO("ret: "<<AOPCALL(tower.Remove(0, type)))

    INFO("ret: "<<AOPCALL(tower.AddWatcher(1, Point(1, 1), type)))
    INFO("ret: "<<AOPCALL(tower.RemoveWatcher(1, type)))

    INFO("ret: "<<AOPCALL(tower.Add(0, Point(0, 0), type)))
    INFO("ret: "<<AOPCALL(tower.AddWatcher(1, Point(1, 1), type)))


}