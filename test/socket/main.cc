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

#include "TestPiiSocket.h"
#include <QtTest>

TestPiiSocket::TestPiiSocket() :
  a(""), b(""), e(""), h("")
{}

/*
  Capital letters represent proxies

   ,-- b     ,-- F
  a     ,-- D
   `-- C     `-- G -- h
        `-- e
 */
void TestPiiSocket::isConnected()
{
  QVERIFY(!a.isConnected());
  QVERIFY(!b.isConnected());
  QVERIFY(!e.isConnected());
  QVERIFY(!h.isConnected());

  a.connectInput(c.input());
  QVERIFY(!a.isConnected());
  a.connectInput(&b);
  QVERIFY(a.isConnected());
  QVERIFY(b.isConnected());
  a.disconnectInput(&b);
  QVERIFY(!a.isConnected());
  c.output()->connectInput(d.input());
  d.output()->connectInput(f.input());
  QVERIFY(!a.isConnected());
  d.output()->connectInput(g.input());
  QVERIFY(!a.isConnected());
  g.output()->connectInput(&h);
  QVERIFY(a.isConnected());
  QVERIFY(h.isConnected());
  a.connectInput(&b);
  QVERIFY(a.isConnected());
  c.output()->connectInput(&e);
  QVERIFY(e.isConnected());
  c.output()->disconnectInput(d.input());
  QVERIFY(a.isConnected());
  QVERIFY(!h.isConnected());
  c.output()->disconnectInput(&e);
  QVERIFY(a.isConnected());
  QVERIFY(!e.isConnected());
  a.disconnectInput(&b);
  QVERIFY(!a.isConnected());

  c.output()->connectInput(d.input());
  c.output()->connectInput(&e);
  a.connectInput(&b);
}

void TestPiiSocket::proxyLoop()
{
  // Try to make a loop
  g.output()->connectInput(c.input());
  QCOMPARE(g.output()->connectedInputs().size(), 1);
  QCOMPARE(g.output()->connectedInputs()[0],
           static_cast<PiiAbstractInputSocket*>(&h));
}

void TestPiiSocket::connectedInputs()
{
  QList<PiiAbstractInputSocket*> lstInputs = a.connectedInputs();
  QCOMPARE(lstInputs.size(), 2);
  QVERIFY(lstInputs.contains(&b));
  QVERIFY(lstInputs.contains(c.input()));

  lstInputs = PiiProxySocket::connectedInputs(c.input());
  QCOMPARE(lstInputs.size(), 2);
  QVERIFY(lstInputs.contains(&e));
  QVERIFY(lstInputs.contains(&h));
}

void TestPiiSocket::root()
{
  QCOMPARE(PiiProxySocket::root(g.output()), &a);
  QCOMPARE(PiiProxySocket::root(f.output()), &a);
  QCOMPARE(PiiProxySocket::root(c.output()), &a);
  QCOMPARE(PiiProxySocket::root(&a), &a);
}

QTEST_MAIN(TestPiiSocket)
