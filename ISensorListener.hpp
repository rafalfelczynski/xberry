#pragma once

#include <vector>
#include <string>
#include "Observer/ISubscriber.h"

using ISensorListener = ISubscriber<unsigned, std::vector<std::string>>;
