#include "ScriptMgr.h"
#include "InstanceScript.h"
#include "mogushan_palace.h"
class instance_mogushan_palace : public InstanceMapScript
{
public:
    instance_mogushan_palace() : InstanceMapScript("instance_mogushan_palace", 994) { }

    InstanceScript* GetInstanceScript(InstanceMap* map) const override
    {
        return new instance_mogushan_palace_InstanceMapScript(map);
    }

    struct instance_mogushan_palace_InstanceMapScript : public InstanceScript
    {
        instance_mogushan_palace_InstanceMapScript(Map* map) : InstanceScript(map) { }
    };
};

void AddSC_instance_mogushan_palace()
{
    new instance_mogushan_palace();
}
