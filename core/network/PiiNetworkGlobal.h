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

#ifndef _PIINETWORKGLOBAL_H
#define _PIINETWORKGLOBAL_H

#include <PiiGlobal.h>

#ifdef PII_BUILD_CORE
#  define PII_BUILD_NETWORK
#  define PII_BUILDING_NETWORK 1
#  define PII_NETWORK_EXPORT PII_DECL_EXPORT
#else
#  define PII_BUILDING_NETWORK 0
#  define PII_NETWORK_EXPORT PII_DECL_IMPORT
#endif

#endif //_PIINETWORKGLOBAL_H
