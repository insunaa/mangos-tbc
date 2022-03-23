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

#include "ByteBuffer.h"
#include "Common.h"
#include "Config/Config.h"
#include "Database/DatabaseEnv.h"
#include "Database/SQLStorage.h"
#include "Errors.h"
#include "Log.h"
#include "Platform/Define.h"
#include "ProgressBar.h"
#include "Threading.h"
#include "WorldPacket.h"

#endif // PCHDEF_H
