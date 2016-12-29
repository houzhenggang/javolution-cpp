/*
 * Javolution - Java(TM) Solution for Real-Time and Embedded Systems
 * Copyright (C) 2012 - Javolution (http://javolution.org/)
 * All rights reserved.
 */
#include "java/lang/Boolean.hpp"

using namespace java::lang;

Boolean Boolean_API::newStaticInstance(Type::boolean value) { // Static.
    return new Boolean_API(value);
}
