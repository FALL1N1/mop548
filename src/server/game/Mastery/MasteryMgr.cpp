#include "MasteryMgr.h"

void MasteryMgr::LoadFromDB()
{
    uint32 oldMSTime = getMSTime();

    PreparedStatement* stmt = WorldDatabase.GetPreparedStatement(WORLD_SEL_MASTERIES);
    PreparedQueryResult result = WorldDatabase.Query(stmt);

    if (!result)
    {
        TC_LOG_INFO("server.loading", ">> Loaded 0 Masteries. DB table `masteries` is empty.");
        return;
    }

    uint32 count = 0;

    do
    {
        Field* fields = result->Fetch();

        Mastery mastery;

        uint32 id = fields[0].GetInt32();
        mastery.base = fields[1].GetFloat();
        mastery.ratio = fields[2].GetFloat();

        masteriesMap[(CharSpecialization)id] = mastery;

        ++count;
    } while (result->NextRow());

    TC_LOG_INFO("server.loading", ">> Loaded %u Masteries in %u ms", count, GetMSTimeDiffToNow(oldMSTime));
}


Mastery MasteryMgr::getMastery(CharSpecialization specId)
{
    std::map<CharSpecialization, Mastery>::const_iterator itr = masteriesMap.find(specId);
    if (itr != masteriesMap.end())
    {
        return itr->second;
    }
    else // Not loaded Mastery
    {
        Mastery mastery;
        mastery.base = 0.0f;
        mastery.ratio = 0.0f;
        return mastery;
    }
}