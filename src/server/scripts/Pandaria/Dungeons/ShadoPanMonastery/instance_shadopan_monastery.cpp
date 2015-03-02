#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "shadopan_monastery.h"

class instance_shadopan_monastery : public InstanceMapScript
{
public:
    instance_shadopan_monastery() : InstanceMapScript("instance_shadopan_monastery", 959) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_shadopan_monastery_InstanceMapScript(map);
    }

    struct instance_shadopan_monastery_InstanceMapScript : public InstanceScript
    {
        instance_shadopan_monastery_InstanceMapScript(Map* map) : InstanceScript(map) { }
    };
};

void AddSC_instance_shadopan_monastery()
{
    new instance_shadopan_monastery();
}
