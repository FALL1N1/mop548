#ifndef _MASTERY_MGR_H
#define _MASTERY_MGR_H

#include <ace/Singleton.h>

#include "Player.h"
#include "Common.h"
#include "DatabaseEnv.h"
#include "DBCStructure.h"

struct Mastery
{
    float base;
    float ratio;

    float GetPercent(uint32 amount)
    {
        return base + ((ratio == 0.0f) ? 0.0f : (float(amount) / ratio));
    };
};

class MasteryMgr
{
    friend class ACE_Singleton <MasteryMgr, ACE_Null_Mutex>;
public:

    void LoadFromDB();
    Mastery GetMastery(uint32 spec);

private:
    MasteryMgr() { };
    ~MasteryMgr() { };

    std::map<uint32, Mastery> masteriesMap;
};

#define sMasteryMgr ACE_Singleton<MasteryMgr, ACE_Null_Mutex>::instance()

#endif