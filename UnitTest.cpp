/*
 * gamelibTest.cpp: 本檔案儲遊unit test的test cases
 * Copyright (C) 2002-2008 Woei-Kae Chen <wkc@csie.ntut.edu.tw>
 *
 * This file is part of game, a free game development framework for windows.
 *
 * game is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * game is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * History:
 *   2005-09-01
 *      1. Created to implement Unit Test environment with CppUnit v1.10.2
 *      2. Run unit test with MfcUi.
 *      3. The runner runs the tests that are registered.
 */

#include "stdafx.h"

#include <cppunit/ui/Mfc/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>

void runTest()
{
	CppUnit::MfcUi::TestRunner runner;
	CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry();
	runner.addTest( registry.makeTest() );
	runner.run();
}
