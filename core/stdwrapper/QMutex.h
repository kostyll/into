/* This file is part of Into.
 * Copyright (C) Intopii 2013.
 * All rights reserved.
 *
 * Licensees holding a commercial Into license may use this file in
 * accordance with the commercial license agreement. Please see
 * LICENSE.commercial for commercial licensing terms.
 *
 * Alternatively, this file may be used under the terms of the GNU
 * Affero General Public License version 3 as published by the Free
 * Software Foundation. In addition, Intopii gives you special rights
 * to use Into as a part of open source software projects. Please
 * refer to LICENSE.AGPL3 for details.
 */

#ifndef _QMUTEX_H
#define _QMUTEX_H

#ifdef PII_CXX11
#  include <mutex>
typedef std::mutex QMutex;
#else
// If C++11 support is not available, you need to have another class
// that implements the mutex interface in a file called mutex.h. You
// must also have a typedef that aliases your type as QMutex (see
// above).
#  include <atomic.h>
#endif

#endif //_QMUTEX_H
