#pragma once

#include <functional>
#include <tuple>
#include <memory>
#include <vector>
#include <utility>

#include <QStringView>
#include <QString>
#include <QHash>
#include <QList>
#include <QRegularExpression>
#include <QApplication>

// Some windows kit parser is messing stuff up, this is to exclude it
#define _PARSER_H

#include "decl.h"