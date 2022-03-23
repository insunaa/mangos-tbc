// add here most rarely modified headers to speed up debug build compilation
#ifndef PCHDEF_H
#define PCHDEF_H

#include <assert.h>
#include <errno.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <algorithm>
#include <boost/asio.hpp>
#include <chrono>
#include <cmath>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>

#include "AI/BaseAI/CreatureAI.h"
#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "AI/ScriptDevAI/include/sc_creature.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/sc_grid_searchers.h"
#include "AI/ScriptDevAI/include/sc_instance.h"
#include "ByteBuffer.h"
#include "Common.h"
#include "DBScripts/ScriptMgr.h"
#include "Entities/Object.h"
#include "Entities/ObjectGuid.h"
#include "Entities/UpdateData.h"
#include "Entities/UpdateFields.h"
#include "Errors.h"
#include "Globals/ObjectAccessor.h"
#include "Globals/ObjectMgr.h"
#include "Globals/SharedDefines.h"
#include "Log.h"
#include "Platform/Define.h"
#include "Server/DBCStores.h"
#include "Server/DBCStructure.h"
#include "Server/Opcodes.h"
#include "Server/SQLStorages.h"
#include "Threading.h"
#endif // PCHDEF_H
