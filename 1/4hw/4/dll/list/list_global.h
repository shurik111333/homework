#ifndef LIST_GLOBAL_H
#define LIST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(LIST_LIBRARY)
#  define LISTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define LISTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // LIST_GLOBAL_H
